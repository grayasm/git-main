import platform

from subprocess import Popen, PIPE
from time import sleep
from os import O_NONBLOCK, read, path, listdir
import bot_logger as logging
from random import shuffle

# Platform specific imports for openvpn process
# We need to set the stdout of the openvpn process to non blocking
# otherwise reading from the pipe output woud cause the whole thing
# to block
if platform.system().lower().startswith('win'):
    # Windows is 'phtupid' and doesn't know about fcntl
    import msvcrt
    from ctypes import windll, byref, wintypes, GetLastError, WinError
    from ctypes.wintypes import HANDLE, DWORD, POINTER, BOOL
    LPDWORD = POINTER(DWORD)
    PIPE_NOWAIT = wintypes.DWORD(0x00000001)
elif platform.system().lower().startswith('lin') or platform.system().lower().startswith('dar'):
    from fcntl import fcntl, F_GETFL, F_SETFL

SUCCESS_MESSAGE = "Initialization Sequence Completed"
OPENVPN_COMMAND = "openvpn"
VPN_SUCCESS = 1
VPN_ERROR = 0
MAX_RETRIES = 5

# Global variable for VPN subprocess
openvpn_process = None


class OpenVPNProcessExceptions(Exception):
    """Raised for different internal errors"""
    pass


def pipe_no_wait(process):
    """ pipefd is a integer as returned by os.pipe """
    if platform.system().lower().startswith('win'):
        pipefd = process.stdout.fileno()
        SetNamedPipeHandleState = windll.kernel32.SetNamedPipeHandleState
        SetNamedPipeHandleState.argtypes = [HANDLE, LPDWORD, LPDWORD, LPDWORD]
        SetNamedPipeHandleState.restype = BOOL

        h = msvcrt.get_osfhandle(pipefd)

        res = windll.kernel32.SetNamedPipeHandleState(h, byref(PIPE_NOWAIT), None, None)
        if res == 0:
            print(WinError())
            return False
        return True
    elif platform.system().lower().startswith('lin') or platform.system().lower().startswith('dar'):
        # set the O_NONBLOCK flag of openvpn_process.stdout file descriptor:
        flags = fcntl(process.stdout, F_GETFL)  # get current p.stdout flags
        fcntl(process.stdout, F_SETFL, flags | O_NONBLOCK)
        return True


def start_openvpn_subprocess(config_file, credentials_file):
    # Connect to vpn
    print("----->", config_file)
    process = Popen(['sudo', OPENVPN_COMMAND, config_file], stdout=PIPE, stderr=PIPE, shell=False)
    if not pipe_no_wait(process):
        raise OpenVPNProcessExceptions("Failed to set file descriptor non blocking")

    return process


def get_config_file(vpn_config_dir):
    vpn_config_files = [path.abspath(path.join(vpn_config_dir, x)) for x in listdir(vpn_config_dir)]
    for x in vpn_config_files:
        if x.endswith('.ovpn'):
            return x
    return None


def close_vpn_connection():
    global openvpn_process
    # kill() does not always closes tun0 device
    if openvpn_process is not None:
        openvpn_process.kill()
        openvpn_process = None
    # 'sudo killall openvpn' does something nasty to VPN provider connection
    process = Popen(['sudo', 'killall', OPENVPN_COMMAND], stdout=PIPE, stderr=PIPE, shell=False)
    if not pipe_no_wait(process):
        raise OpenVPNProcessExceptions("Failed to set file descriptor non blocking")


def connect_to_vpn(vpn_config_dir, vpn_credentials_file):
    logger = logging.get_logger(__name__ + '.log', __name__ + '.log')
    vpn_config_file = None
    init_success = False
    retry_no = 0
    global openvpn_process

    while retry_no < MAX_RETRIES:
        # Debug openvpn output
        vpn_output = ""
        # Close any previous openvpn connection
        close_vpn_connection()
        # Get config files path
        vpn_config_file = get_config_file(vpn_config_dir)

        logger.info(
            "Trying to connect to vpn with config '%s' and credentials '%s'."
            % (vpn_config_file, vpn_credentials_file))
        # Start vpn subprocess
        openvpn_process = start_openvpn_subprocess(vpn_config_file, vpn_credentials_file)
        # Let the openvpn process write output
        sleep(15)

        # get the output
        while True:
            try:
                vpn_output = read(openvpn_process.stdout.fileno(), 100000)
                logger.info(str(vpn_output))
                sleep(1)
                # If success message was read from output, everything is ok
                if SUCCESS_MESSAGE in str(vpn_output):
                    logger.info("Initialization Complete.")
                    return VPN_SUCCESS
                # If line is empty, the process exited
                if vpn_output == b'':
                    break
            except OSError:
                # the os throws an exception if there is no data
                logger.exception("Done reading data from OpenVPN process.")
                break

        retry_no = retry_no + 1
        # debug openvpn output
        # vpn_outlen = len(vpn_output)
    logger.info("Failed to start vpn")

    return VPN_ERROR
