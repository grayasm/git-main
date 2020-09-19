# For logger
import bot_logger
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
from datetime import datetime
import sys
# For threading
import concurrent.futures
# VPN tools
from vpn_tools import openvpn_connect, openvpn_close_connection
from cyberghost import CyberghostvpnManager, CyberghostvpnException

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
# Wheter to use Cyberghost app for linux /usr/bin/cyberghostvpn
USE_CYBERGHOSTVPN = False
CYBERGHOSTVPN_COUNTRY = ""
# Whether to use Headless Browsers or nah
IS_HEADLESS = False
# Whether to use a PROXY
USE_PROXY = False
PROXY_LIST_FILE = ""
# Whether to use Luminati Proxy Manager
USE_LPM = False
LPM_ADDRESS = ""
# Whether to disable logging. By default is 'false'
DISABLE_LOGGING = False
# Whether to stop posting in these time intervals.
STOP_TIME_INTERVAL = ""

# Slave queues
slave_queue = queue.Queue()
slave_return_queue = queue.Queue()
logger = None

# Cyberghost managing object
cyberghostmanager = None

# Return values valid for all bots
SLAVE_SUCCESS = 1
SLAVE_ERROR = 0
SLAVE_RETRY = -1


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
    global VPN_SWITCH_TIME, USE_VPN, IS_HEADLESS
    global USE_CYBERGHOSTVPN, CYBERGHOSTVPN_COUNTRY
    global USE_PROXY, PROXY_LIST_FILE, USE_LPM, LPM_ADDRESS
    global DISABLE_LOGGING, STOP_TIME_INTERVAL
    config = configparser.ConfigParser()
    config.read(CONFIG_PATH)
    temp_use_vpn = ""
    temp_use_cyberghostvpn = ""

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
        if config.has_option('master', 'use_cyberghostvpn'):
            temp_use_cyberghostvpn = config['master']['use_cyberghostvpn']
        if config.has_option('master', 'cyberghostvpn_country'):
            CYBERGHOSTVPN_COUNTRY = config['master']['cyberghostvpn_country']
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
        if config.has_option('master', 'disable_logging'):
            temp_disable_logging = config['master']['disable_logging']
        if config.has_option('master', 'stop_time_interval'):
            STOP_TIME_INTERVAL = config['master']['stop_time_interval']
    config.remove_section('master')

    # All must be False by default!
    if temp_use_vpn.lower() == "true":
        USE_VPN = True
    if temp_use_cyberghostvpn.lower() == "true":
        USE_CYBERGHOSTVPN = True
    if temp_is_headless.lower() == "true":
        IS_HEADLESS = True
    if temp_use_proxy.lower() == "true":
        USE_PROXY = True
    if temp_use_lpm.lower() == "true":
        USE_LPM = True
    if temp_disable_logging.lower() == "true":
        DISABLE_LOGGING = True

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
    global IS_HEADLESS, USE_PROXY, USE_LPM, LPM_ADDRESS, DISABLE_LOGGING
    try:
        target_website = context['website']
    except KeyError:
        raise ConfigParseException(
            "Bad config sections : " + str(context)
        )

    # NOTE: If you add new script you must also add it here.
    if target_website == 'bakecaincontrii.com':
        return BakecaSlave(IS_HEADLESS, USE_PROXY, USE_LPM, LPM_ADDRESS, DISABLE_LOGGING)
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


def switch_vpn_server(vpn_start_time, vpn_force_switch, vpn_force_stop):
    global VPN_SWITCH_TIME, USE_VPN, SLAVES_NUMBER
    global USE_CYBERGHOSTVPN, CYBERGHOSTVPN_COUNTRY
    global VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE
    global DISABLE_LOGGING
    global logger, cyberghostmanager
    slaves_finished = 1

    # Check if VPN time expired
    time_now = time()
    time_diff = time_now - vpn_start_time
    if USE_VPN is False and USE_CYBERGHOSTVPN is False:
        return 1
    if time_diff < VPN_SWITCH_TIME and vpn_force_switch is False and vpn_force_stop is False:
        return 1

    # Wait for all bots to finish before we switch vpn
    while slaves_finished < SLAVES_NUMBER:
        slave_return_queue.get(block=True, timeout=600)
        slaves_finished = slaves_finished + 1

    # Close connection and return
    if USE_VPN and vpn_force_stop:
        print("Stopping VPN server")
        openvpn_close_connection()
        return 1
    if USE_CYBERGHOSTVPN and vpn_force_stop:
        print("Stopping CYBERGHOST server")
        cyberghostmanager.disconnect()
        return 1

    if USE_VPN:
        print("Switching VPN server")
        # Now connect to different vpn
        if not openvpn_connect(VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE, DISABLE_LOGGING):
            msg = ("Failed to start VPN with config directory %s and credentials file %s."
                   % (VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE))
            logger.info(msg)
            print("Failed to connect to VPN")
            raise MasterBotInternalException("Failed to connect to VPN")
        return 1
    if USE_CYBERGHOSTVPN:
        print("Switching CYBERGHOST server")
        cyberghostmanager.switch_vpn()
        return 1


def vpn_connect():
    global USE_VPN, VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE, DISABLE_LOGGING
    global USE_CYBERGHOSTVPN, CYBERGHOSTVPN_COUNTRY
    global logger, cyberghostmanager
    rc = 0

    if USE_VPN:
        rc = openvpn_connect(VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE, DISABLE_LOGGING)
        if not rc:
            msg = ("Failed to start VPN with config directory %s and credentials file %s."
                   % (VPN_CONFIG_DIR, VPN_CREDENTIALS_FILE))
            logger.info(msg)
            print("Failed to connect to VPN")
            raise MasterBotInternalException("Failed to connect to VPN")
        else:
            print("Connected to VPN")
            return time()
    if USE_CYBERGHOSTVPN:
        cyberghostmanager.switch_vpn()
        return time()

    print("USE_VPN and USER_CYBERGHOSTVPN are \"False\". Starting without VPN.")
    return 0


def main():
    global logger, USE_VPN, CONFIG_PATH, SLAVES_NUMBER, DISABLE_LOGGING
    global cyberghostmanager, USE_CYBERGHOSTVPN, CYBERGHOSTVPN_COUNTRY
    vpn_start_time = 0
    rc = 0

    # Parse script arguments
    init_parser()
    try:
        parse_config()
    except ConfigParseException as e:
        print("Error while parsing config file. %s" % CONFIG_PATH)
        return 1

    # Init logger
    file_name, file_ext = os.path.splitext(os.path.basename(__file__))
    logger = bot_logger.get_logger(file_name + ".log", file_name + ".log")

    # Init cyberghostmanager
    if USE_CYBERGHOSTVPN and CYBERGHOSTVPN_COUNTRY:
        cyberghostmanager = CyberghostvpnManager(CYBERGHOSTVPN_COUNTRY)

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
            release_timeout = 360       # 6 minutes
            debug_timeout = 1800        # 30 minutes
            vpn_timeout = 300           # 5 minutes
            critical_timeout = 3600     # 1 hour
            slave_return_value = slave_return_queue.get(block=True, timeout=release_timeout)
            vpn_force_switch = slave_return_value is SLAVE_ERROR
            stop_posting = util.check_stop_time_interval(STOP_TIME_INTERVAL)

            if stop_posting:
                msg = ("---> Stop posting! Now:%s Interval:%s" % (datetime.now().strftime('%H:%M'), STOP_TIME_INTERVAL))
                print(msg)
                logger.info(msg)

            # Check if vpn timeout was reached and we have to switch the vpn
            if USE_VPN or USE_CYBERGHOSTVPN:
                rc = switch_vpn_server(vpn_start_time, vpn_force_switch, vpn_force_stop=stop_posting)
                if not rc:
                    logger.info("Failed to switch VPN server.")
                    return 0

                # Wait and reconnect to VPN if necessary!
                if stop_posting:
                    while stop_posting:
                        sleep(vpn_timeout)
                        stop_posting = util.check_stop_time_interval(STOP_TIME_INTERVAL)
                    # connect again
                    vpn_connect()

                vpn_start_time = time()
                logger.info("Switched VPN server.")
                # Now start all slaves again.
                start_all_slaves(executor)
                # Continue the loop
                continue

            # Check stop posting condition.
            if stop_posting:
                while stop_posting:
                    sleep(vpn_timeout)
                    stop_posting = util.check_stop_time_interval(STOP_TIME_INTERVAL)

            slave_context = slave_queue.get()
            slave_queue.put(slave_context)
            slave = get_slave(slave_context)
            executor.submit(slave.start, slave_context, slave_return_queue)
            logger.info("Started slave with context %s", str(slave_context))
        except queue.Empty as e:
            msg = ("Slave timeout exception: %s" % str(e))
            logger.exception(msg)
            time_diff = time() - vpn_start_time
            if time_diff > critical_timeout:
                msg = ("Slave timeout %d sec reached critical timeout %d sec" % (time_diff, critical_timeout))
                logger.info(msg)
                print(msg)
                break


    if USE_VPN:
        openvpn_close_connection()
    if USE_CYBERGHOSTVPN:
        cyberghostmanager.disconnect()

    # Make an exception and keep this log file
    bot_logger.close_logger(logger, disable_logging=False)
    return 1


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
    except MasterBotInternalException:
        print('Terminated with exception')
    except CyberghostvpnException as e:
        print('Cyberghost exception: %s' % str(e))
    except:  # catch all
        print('Unknown master_bot exception')
    finally:
        if USE_VPN:
            openvpn_close_connection()
        if USE_CYBERGHOSTVPN:
            cyberghostmanager.disconnect()

    try:
        sys.exit(0)
    except SystemExit:
        os._exit(0)
