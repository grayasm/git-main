/*  Cap.8   Data Types
    8.9.    Network Address Types
    8.9.1   inet
    8.9.2   cidr
    8.9.3   inet vs cidr
    8.9.4   macaddr
    8.9.5   macadd8

    psql -d mytestdb -U pgmihai
    \i   09.0_network_address.sql
    \?
    \qecho '\033[2J'
*/


/*  PostgreSQL offers data types to store IPv4, IPv6, MAC addresses.
    It is better to use these types instead of plain text types to store
    network address, because these types offer input error checking and
    specialized operators functions.

    Name           Storage Size         Description
    -------------+--------------------+---------------------------------
    cidr           7 or 19 bytes        IPv4 and IPv6 networks (only)
    inet           7 or 19 bytes        IPv4 and IPv6 hosts and networks
    macaddr        6 bytes              MAC addresses
    macaddr8       8 bytes              MAC addresses (EUI-64 format)
    --------------------------------------------------------------------

    When sorting inet and cidr data types, IPv4 addresses will always sort
    before IPv6 addresses including IPv4 addresses encapsulated or mapped
    to IPv6 addresses, such as ::10.2.3.4  or ::ffff:10.4.3.2
*/

/*      inet

        The input format for inet is address/y where address is an IPv4 or IPv6
        address and y is the number of bits in the netmask. If the /y portion
        is missing the netmask is 32 for IPv4 and 128 for IPv6, so the value
        represents just a single host. On display, the /y portion is suppresed
        if the netmask specifies a single host.
*/
DROP TABLE IF EXISTS inet_t CASCADE;
CREATE TABLE inet_t (id SERIAL, inet_ inet);
INSERT INTO inet_t(inet_) VALUES ('192.168.0.1'),
                                 ('192.168.100.1');
SELECT * FROM inet_t;
/*
 id |     inet_
----+---------------
  1 | 192.168.0.1
  2 | 192.168.100.1
(2 rows)
*/


/*      cidr

        The cidr type holds IPv4 or IPv6 network specification, that follow
        Classless Internet Domain Routing conventions. The format for specifying
        networks is address/y where address is the network represented as IPv4
        or IPv6 address, and y is the number of bits in the netmask. Is is an
        error to specify a network address that has bits set to the right of
        the specified netmask.
*/
DROP TABLE IF EXISTS cidr_t CASCADE;
CREATE TABLE cidr_t (id SERIAL, cidr_ cidr);
INSERT INTO cidr_t (cidr_) VALUES ('192.168.100.128/25'),
                                  ('192.168/24'),
                                  ('192.168/25'),
                                  ('192.168.1'),
                                  ('192.168'),
                                  ('128.1'),
                                  ('128'),
                                  ('128.1.2'),
                                  ('10.1.2'),
                                  ('10.1'),
                                  ('10'),
                                  ('10.1.2.3/32'),
                                  ('2001:4f8:3:ba::/64'),
-- gives error                    ('2001:4f8:3:ba:2e0:81f-f:fe22:d1f1/128'),
                                  ('::ffff:1.2.3.0/120'),
                                  ('::ffff:1.2.3.0/128');
SELECT * FROM cidr_t;
/*
 id |       cidr_
----+--------------------
  1 | 192.168.100.128/25
  2 | 192.168.0.0/24
  3 | 192.168.0.0/25
  4 | 192.168.1.0/24
  5 | 192.168.0.0/24
  6 | 128.1.0.0/16
  7 | 128.0.0.0/16
  8 | 128.1.2.0/24
  9 | 10.1.2.0/24
 10 | 10.1.0.0/16
 11 | 10.0.0.0/8
 12 | 10.1.2.3/32
 13 | 2001:4f8:3:ba::/64
 14 | ::ffff:1.2.3.0/120
 15 | ::ffff:1.2.3.0/128
(15 rows)
*/


/*      macaddr

        The macaddr type stores MAC addresses, known for example from Ehternet
        card hardware addresses (although MAC addresses are used for other
        purposes as well). Input is accepted in the following formats:
*/
DROP TABLE IF EXISTS macaddr_t CASCADE;
CREATE TABLE macaddr_t (id SERIAL, macaddr_ macaddr);
INSERT INTO macaddr_t (macaddr_) VALUES ('08:00:2b:01:02:03'),
                                        ('08-00-2b-01-02-03'),
                                        ('08002b:010203'),
                                        ('08002b-010203'),
                                        ('0800.2b01.0203'),
                                        ('0800-2b01-0203'),
                                        ('08002b010203');
SELECT * FROM macaddr_t;
/*
 id |     macaddr_
----+-------------------
  1 | 08:00:2b:01:02:03
  2 | 08:00:2b:01:02:03
  3 | 08:00:2b:01:02:03
  4 | 08:00:2b:01:02:03
  5 | 08:00:2b:01:02:03
  6 | 08:00:2b:01:02:03
  7 | 08:00:2b:01:02:03
(7 rows)
*/


/*      macaddr8

        The macaddr8 type stores MAC addresses in EUI-64 format, known for
        example from Ethernet card hardware addresses. This type can accept
        both 6 and 8 byte length MAC addresses and stores them in 8 byte length
        format. (...) Generally speaking, any input which is comprised of pairs
        of hex digits (on byte boundaries), optionally separated consistently
        by one of : - or . is accepted.
*/
DROP TABLE IF EXISTS macaddr8_t CASCADE;
CREATE TABLE macaddr8_t (id SERIAL, macaddr8_ macaddr8);
INSERT INTO macaddr8_t(macaddr8_) VALUES ('08:00:2b:01:02:03:04:05'),
                                         ('08-00-2b-01-02-03-04-05'),
                                         ('08002b:0102030405'),
                                         ('08002b-0102030405'),
                                         ('0800.2b01.0203.0405'),
                                         ('0800-2b01-0203-0405'),
                                         ('08002b01:02030405'),
                                         ('08002b0102030405');
SELECT * FROM macaddr8_t;
/*
 id |        macaddr8_
----+-------------------------
  1 | 08:00:2b:01:02:03:04:05
  2 | 08:00:2b:01:02:03:04:05
  3 | 08:00:2b:01:02:03:04:05
  4 | 08:00:2b:01:02:03:04:05
  5 | 08:00:2b:01:02:03:04:05
  6 | 08:00:2b:01:02:03:04:05
  7 | 08:00:2b:01:02:03:04:05
  8 | 08:00:2b:01:02:03:04:05
(8 rows)
*/
