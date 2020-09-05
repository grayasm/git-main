from subprocess import Popen, PIPE, check_output, TimeoutExpired
from time import sleep
from os import read
import re


class CyberghostvpnException(Exception):
    """Raised for errors with /usr/bin/cyberghostvpn"""
    pass


class Cyberghostvpn(object):
    def __init__(self):
        pass

    def get_cities(self, country):
        cmd = ("sudo cyberghostvpn --traffic --country-code %s --connection TCP" % country)
        proc = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = proc.communicate()
        if out == b'':
            msg = ('Error on command: %s' % cmd)
            raise CyberghostvpnException(msg)
        blines = out.split(b'\n')
        slines = []
        for bl in blines:
            sl = bl.decode("utf-8")
            slines.append(sl)
            # print(sl)

        # sudo cyberghostvpn --traffic --country-code US --connection TCP
        # +-----+---------------+----------+------+
        # | No. |      City     | Instance | Load |
        # +-----+---------------+----------+------+
        # |  1  |    Atlanta    |    56    | 65%  |
        # |  2  |    Chicago    |    56    | 64%  |
        # |  3  |     Dallas    |    47    | 62%  |
        # |  4  |   Las Vegas   |    44    | 60%  |
        # |  5  |  Los Angeles  |   143    | 67%  |
        # |  6  |     Miami     |    58    | 63%  |
        # |  7  |    New York   |   337    | 59%  |
        # |  8  |    Phoenix    |    32    | 58%  |
        # |  9  | San Francisco |    36    | 57%  |
        # |  10 |    Seattle    |    36    | 59%  |
        # |  11 |   Washington  |   121    | 75%  |
        # +-----+---------------+----------+------+
        cities = []
        for sl in slines:
            m = re.search('[\s]*\|[\s]*[0-9]+[\s]*\|[\s]*([\w\s]+)[\s]*\|', sl)
            if m is not None and len(m.groups()) > 0:
                city = m.groups()[0].strip()
                cities.append(city)
        return cities

    def get_servers(self, country, city):
        cmd = ("sudo cyberghostvpn --traffic --country-code %s --connection TCP --city '%s'" % (country, city))
        proc = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = proc.communicate()
        if out == b'':
            msg = ('Error on command: %s' % cmd)
            raise CyberghostvpnException(msg)
        blines = out.split(b'\n')
        slines = []
        for bl in blines:
            sl = bl.decode("utf-8")
            slines.append(sl)
            # print(sl)
        # sudo cyberghostvpn --traffic --country-code US --connection TCP --city 'San Francisco'
        # +-----+---------------+-----------------------+------+
        # | No. |      City     |        Instance       | Load |
        # +-----+---------------+-----------------------+------+
        # |  1  | San Francisco | sanfrancisco-s401-i05 | 76%  |
        # |  2  | San Francisco | sanfrancisco-s401-i06 | 82%  |
        # |  3  | San Francisco | sanfrancisco-s401-i12 | 76%  |
        # |  4  | San Francisco | sanfrancisco-s401-i11 | 88%  |
        # |  5  | San Francisco | sanfrancisco-s401-i10 | 33%  |
        # |  6  | San Francisco | sanfrancisco-s401-i09 | 39%  |
        # ..
        # |  36 | San Francisco | sanfrancisco-s403-i12 | 64%  |
        # +-----+---------------+-----------------------+------+

        servers = []
        for srv in slines:
            m = re.search('[\s]*\|[\s]*[0-9]+[\s]*\|[\s]*[\w\s]+[\s]*\|[\s]*([\w\- ]+)[\s]*\|', srv)
            if m is not None and len(m.groups()) > 0:
                server = m.groups()[0].strip()
                servers.append(server)
        return servers

    def connect(self, country, city, server):
        cmd = ("sudo cyberghostvpn --traffic --country-code %s --connection TCP --city '%s' --server '%s' --connect" %
               (country, city, server))
        print(cmd)
        proc = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = proc.communicate()
        if out == b'':
            msg = ('Error on command: %s' % cmd)
            raise CyberghostvpnException(msg)
        msg = "VPN connection established"
        if msg in str(out):
            return 0
        # Connection failed
        return -1

    def disconnect(self):
        cmd = ("sudo cyberghostvpn --stop")
        print(cmd)
        proc = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = proc.communicate()
        if out == b'':
            msg = ('Error on command: %s' % cmd)
            raise CyberghostvpnException(msg)
        return 0

    def status(self):
        cmd = ("sudo cyberghostvpn --status")
        proc = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = proc.communicate()
        if out == b'':
            msg = ('Error on command: %s' % cmd)
            raise CyberghostvpnException(msg)
        # "No VPN connections found."
        # "VPN connection found."
        msg = "No VPN connections found"
        if msg in str(out):
            return 0
        # Connection exists
        return 1


class CyberghostvpnManager(object):
    def __init__(self, country):
        # initialize
        self.country = country
        self.cyberghost = Cyberghostvpn()
        self.addresses = []
        self.current_server = -1
        # get the servers
        cities = self.cyberghost.get_cities(self.country)
        for city in cities:
            servers = self.cyberghost.get_servers(self.country, city)
            for server in servers:
                self.addresses.append((self.country, city, server))

    def switch_vpn(self):
        """Changes VPN ip"""
        # safety check
        if len(self.addresses) == 0:
            raise CyberghostvpnException("cyberghost cannot switch vpn: address list is empty!")
        self.current_server += 1
        # rewind and start with first server again
        if self.current_server >= len(self.addresses):
            self.current_server = 0
        # check if connection exists
        self.disconnect()
        # connect to new server
        address = self.addresses[self.current_server]
        if self.cyberghost.connect(address[0], address[1], address[2]) != 0:
            msg = ("CyberGhost connection failed for: %s, %s, %s" % (address[0], address[1], address[2]))
            raise CyberghostvpnException(msg)
        return 0

    def refresh(self):
        """Refresh server list"""
        self.disconnect()
        # reinitialize
        self.addresses = []
        self.current_server = -1
        # get the servers
        cities = self.cyberghost.get_cities(self.country)
        for city in cities:
            servers = self.cyberghost.get_servers(self.country, city)
            for server in servers:
                self.addresses.append((self.country, city, server))
        return 0

    def disconnect(self):
        """Close existing connection."""
        if self.cyberghost.status() != 0:
            self.cyberghost.disconnect()
        return 0
