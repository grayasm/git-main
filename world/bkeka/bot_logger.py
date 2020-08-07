import logging
import os

# By default, log to syslog. If _log_file is specified, log to that instead.
DEFAULT_LOG_DIRECTORY = "logs/"
SCRIPT_DIR = os.path.dirname(os.path.realpath(__name__))
DEFAULT_LOG_DIR_PATH = os.path.join(SCRIPT_DIR, DEFAULT_LOG_DIRECTORY)


def get_logger(name, log_file):
    """Function setup as many loggers as you want"""
    log_file_path = os.path.join(DEFAULT_LOG_DIR_PATH, log_file)
    formatter = logging.Formatter('%(asctime)s [%(levelname)s] %(module)s: %(message)s',
                                  datefmt='%m/%d/%Y %H:%M:%S')
    handler = logging.FileHandler(log_file_path)
    handler.setFormatter(formatter)
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    logger.addHandler(handler)
    return logger


def close_logger(logger, disable_logging):
    handlers = logger.handlers[:]
    for handler in handlers:
        filename = handler.baseFilename
        handler.close()
        logger.removeHandler(handler)
        # Remove file if logging is disabled
        if disable_logging is True and filename is not None and os.path.exists(filename):
            os.remove(filename)
