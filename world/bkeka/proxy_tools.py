import re
import os.path

# TODO: this class does NOT work with private proxies from Luminati
class Proxy(object):
    def __init__(self, file_in, file_out_ok, file_out_nok):
        self.__file_in = file_in
        self.__file_out_ok = file_out_ok
        self.__file_out_nok = file_out_nok
        if not os.path.isfile(file_in):
            raise Exception("File " + file_in + " could not be found!")
        if not os.path.isfile(file_out_ok):
            f = open(file_out_ok, "a+")
            f.close()
        if not os.path.isfile(file_out_nok):
            f = open(file_out_nok, "a+")
            f.close()
        return None

    def __enter__(self):
        with open(self.__file_in, "r") as f:
            lines = f.readlines()
            for line in lines:
                aa = re.match(r"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\:(\d{1,5})$", line.strip())
                if aa:
                    if len(aa.groups()) == 2:
                        ip4 = aa.groups()[0]
                        port = aa.groups()[1]
                # if len(ip4) > 0 and port == "8080":
                if len(ip4) > 0:
                    self.__proxy_list.append(line.strip())
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        with open(self.__file_in, "w") as f:
            for aa in self.__proxy_list:
                f.write(aa + '\n')
        with open(self.__file_out_ok, "a") as f:
            for aa in self.__proxy_list_ok:
                f.write(aa + '\n')
        with open(self.__file_out_nok, "a") as f:
            for aa in self.__proxy_list_nok:
                f.write(aa + '\n')
        return None

    # It will always return the first address in the list of proxies.
    # To get the second address in the list you have to mark ok/not the current proxy.
    # For that use next(..)
    def get_address(self):
        if len(self.__proxy_list) > 0:
            return self.__proxy_list[0]
        return None

    # Mark with is_valid = true/false the current used address returned by get_address.
    # If the address is valid it will be added to the list with valid proxies.
    # If the address is not valid, it will be added to the list with invalid proxies.
    # The address will be removed afterwards from the input list.
    def set_valid(self, is_valid):
        if len(self.__proxy_list) == 0:
            raise Exception("Cannot call set_valid on empty __proxy_list!")
        if is_valid:
            self.__proxy_list_ok.append(self.__proxy_list[0])
        if not is_valid:
            self.__proxy_list_nok.append(self.__proxy_list[0])
        self.__proxy_list.pop(0)
        return None

    __file_in = None
    __file_out_ok = None
    __file_out_nok = None
    __proxy_list = []
    __proxy_list_ok = []
    __proxy_list_nok = []
