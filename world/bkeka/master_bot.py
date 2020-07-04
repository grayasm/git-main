# For logger
import bot_logger as logging
# For slaves
from slaves.bakeca import BakecaSlave
# For misc
import configparser
import argparse
import os
import traceback
import util
import queue
from time import time
from time import sleep
import sys
# For threading
import concurrent.futures
# VPN tools
from vpn_tools import connect_to_vpn, close_vpn_connection

# Local directory of script
SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
# Default config dir if no config directory is specified
DEFAULT_CONFIG_FILE = 'default.cfg'
DEFAULT_CONFIG_PATH = os.path.join(SCRIPT_DIR, DEFAULT_CONFIG_FILE)
CONFIG_PATH = ""
# Max number of consecutive exceptions
EXCEPTION_THRESHOLD = 5
# Number of parallel slaves
SLAVES_NUMBER = 1
# Directory that contains all openvpn config files.
VPN_CONFIG_DIR = ""
# File that contains VPN credentials
VPN_CREDENTIALS_FILE = ""
# VPN switch time in seconds (default is 6 hours)
VPN_SWITCH_TIME = 21600
# Whether to use VPN or nah
USE_VPN = False
# Whether to use Headless Browsers or nah
IS_HEADLESS = True
# Whether to use a PROXY
USE_PROXY = False
PROXY_LIST_FILE = ""
# Whether to use Luminati Proxy Manager
USE_LPM = True
LPM_ADDRESS = ""

# Slave queues
slave_queue = queue.Queue()
slave_return_queue = queue.Queue()
logger = None


class MasterBotInternalException(Exception):
    """Raised for different internal errors"""
    pass


class ConfigParseException(Exception):
    """ Raised for different config parsing errors """
    pass


def init_parser():
    global CONFIG_PATH
    parser = argparse.ArgumentParser(description='Start master bot.')
    parser.add_argument('--config', dest='config_path', default=DEFAULT_CONFIG_PATH,
                        help='Path to the config directory for the script')
    args = parser.parse_args()
    CONFIG_PATH = args.config_path


def parse_config():
    global SLAVES_NUMBER, EXCEPTION_THRESHOLD, VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE
    global VPN_SWITCH_TIME, USE_VPN, IS_HEADLESS, USE_PROXY, PROXY_LIST_FILE, USE_LPM, LPM_ADDRESS
    config = configparser.ConfigParser()
    config.read(CONFIG_PATH)
    temp_use_vpn = ""

    # Parse default section
    if config.has_section('master'):
        if config.has_option('master', 'max_errors'):
            EXCEPTION_THRESHOLD = int(config['master']['max_errors'])
        if config.has_option('master', 'slaves_number'):
            SLAVES_NUMBER = int(config['master']['slaves_number'])
        if config.has_option('master', 'vpn_config_dir'):
            VPN_CONFIG_DIR = config['master']['vpn_config_dir']
        if config.has_option('master', 'vpn_credentials'):
            VPN_CREDENTIALS_FILE = config['master']['vpn_credentials']
        if config.has_option('master', 'vpn_switch_time'):
            VPN_SWITCH_TIME = int(config['master']['vpn_switch_time'])
        if config.has_option('master', 'use_vpn'):
            temp_use_vpn = config['master']['use_vpn']
        if config.has_option('master', 'headless_browsers'):
            temp_is_headless = config['master']['headless_browsers']
        if config.has_option('master', 'use_proxy'):
            temp_use_proxy = config['master']['use_proxy']
        if config.has_option('master', 'proxy_list'):
            PROXY_LIST_FILE = config['master']['proxy_list']
        if config.has_option('master', 'use_lpm'):
            temp_use_lpm = config['master']['use_lpm']
        if config.has_option('master', 'lpm_address'):
            LPM_ADDRESS = config['master']['lpm_address']
    config.remove_section('master')

    if temp_use_vpn.lower() == "true":
        USE_VPN = True
    if temp_is_headless.lower() == "false":
        IS_HEADLESS = False
    if temp_use_proxy.lower() == "true":
        USE_PROXY = True
    if temp_use_lpm.lower() == "true":
        USE_LPM = True

    for section in config.sections():
        slave_bot = {}
        for item in config.items(section):
            slave_bot[item[0]] = item[1]
        slave_queue.put(slave_bot)

    if slave_queue.empty():
        raise ConfigParseException(
            "Not enough slave configs"
        )


def get_slave(context):
    global IS_HEADLESS
    try:
        target_website = context['website']
    except KeyError:
        raise ConfigParseException(
            "Bad config sections : " + str(context)
        )

    # NOTE: If you add new script you must also add it here.
    if target_website == 'bakecaincontrii.com':
        return BakecaSlave(IS_HEADLESS, USE_PROXY, USE_LPM, LPM_ADDRESS)
    else:
        raise MasterBotInternalException(
            "No script for : " + target_website
        )


def start_all_slaves(thread_executor):
    threads_started = 0
    while threads_started < SLAVES_NUMBER:
        slave_context = slave_queue.get()
        slave_queue.put(slave_context)
        slave = get_slave(slave_context)
        thread_executor.submit(slave.start, slave_context, slave_return_queue)
        threads_started += 1


def switch_vpn_server(vpn_start_time):
    global VPN_SWITCH_TIME, USE_VPN, SLAVES_NUMBER
    global VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE
    slaves_finished = 1

    # Check if VPN time expired
    time_now = time()
    time_diff = time_now - vpn_start_time
    if time_diff < VPN_SWITCH_TIME or USE_VPN is False:
        return 1

    print("Switching VPN server")
    # Wait for all bots to finish before we switch vpn
    while (slaves_finished < SLAVES_NUMBER):
        slave_return_queue.get(block=True, timeout=600)
        slaves_finished = slaves_finished + 1

    # Now connect to different vpn
    if not connect_to_vpn(VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE):
        logger.info(
            "Failed to start VPN with config directory %s and credentials file %s."
            % (VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE))
        print("Failed to connect to VPN")
        return 0
    return 1


def vpn_connect():
    global USE_VPN, VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE
    rc = 0

    if USE_VPN:
        rc = connect_to_vpn(VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE)
        if not rc:
            logger.info(
                "Failed to start VPN with config directory %s and credentials file %s."
                % (VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE))
            print("Failed to connect to VPN")
            print("Continue without vpn")
            USE_VPN = False
            return 0
        else:
            print("Connected to VPN")
            return time()
    else:
        print("USE_VPN is \"False\". Starting without VPN.")
        return 0


def main():
    global logger, CONFIG_PATH, SLAVES_NUMBER
    vpn_start_time = 0
    rc = 0

    # Init logger
    logger = logging.get_logger(__file__, __file__ + ".log")

    # Parse script arguments
    init_parser()

    try:
        parse_config()
    except ConfigParseException as e:
        logger.exception("Error while parsing config file. %s" % CONFIG_PATH)
        return 1

    # Connect to VPN
    vpn_start_time = vpn_connect()
    logger.info("Done vpn_connect()")

    # Init thread pool executor
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=SLAVES_NUMBER)

    # Start first SLAVES_NUMBER threads
    start_all_slaves(executor)
    logger.info("Done starting first batch of slaves")

    # Now start slaves as slaves finish
    while True:
        try:
            logger.info("Waiting for a slave to finish")
            slave_return_queue.get(block=True, timeout=300)
            # Check if vpn timeout was reached and we have to switch the vpn
            if USE_VPN:
                rc = switch_vpn_server(vpn_start_time)
                if not rc:
                    logger.info("Failed to switch VPN server.")
                    return 0
                vpn_start_time = time()
                logger.info("Switched VPN server.")
                # Now start all slaves again.
                start_all_slaves(executor)
                # Reexecute loop
                continue

            slave_context = slave_queue.get()
            slave_queue.put(slave_context)
            slave = get_slave(slave_context)
            executor.submit(slave.start, slave_context, slave_return_queue)
            logger.info("Started slave with context %s", str(slave_context))
        except queue.Empty as e:
            logger.exception("Waited too long. Something is fucky.")
            break

    close_vpn_connection()
    return 1


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        close_vpn_connection()
    try:
        sys.exit(0)
    except SystemExit:
        os._exit(0)
