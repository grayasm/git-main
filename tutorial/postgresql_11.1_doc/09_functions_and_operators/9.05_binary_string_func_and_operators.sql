/*  Cap.9   Functions and Operators
    9.5     Binary String Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.05_binary_string_func_and_operators.sql
    \?
    \qecho '\033[2J'
*/


/*  Functions and Operators manipulating values of type bytea

    1. SQL Binary String Functions and Operators
    2. Other Binary String Functions
*/

/*  SQL Binary String Functions and Operators

    Function                        Description
    ------------------------------+--------------------
    string || string                String concatenation
    octet_length(bs)                Number of bytes in binary string

    overlay(bs placing bs from x for y):
                                    Replace substring
    position(bs2 in bs1)            Location of specified binary substring
    substring(bs from x for y)      Extract binary substring
    trim([both] bytes from bs1)     Trims bs1 at both ends with bytes
*/

SELECT '\\Post'::bytea || '\047gres\000'::bytea; -- \x5c506f7374276772657300
SELECT octet_length('jo\000se'::bytea); -- 5
SELECT overlay('Th\000omas'::bytea placing '\002\003'::bytea from 2 for 3); -- \x5402036d6173
SELECT position('\000om'::bytea in 'Th\000omas'::bytea); -- 3
SELECT substring('Th\000omas'::bytea from 2 for 3); -- \x68006f
SELECT trim('\000\001'::bytea from '\000Tom\001'::bytea); -- \x546f6d


/*  Other Binary String Functions

    Function                        Description
    ------------------------------+--------------------------------
    btrim(bs, bytes)                Trim bs at both ends with bytes
    decode(bs, format)              Decode binary data from bs using format
    encode(data, format)            Encode binary data into a textual
                                    representation. Supported formats are:
                                    base64, hex, escape.
    get_bit(bs, offset)             Extract bit from binary string
    get_byte(bs, offset)            Extract byte from binary string
    length(bs)                      Length of binary string
    md5(bs)                         Calculates the MD5 hash of the binary string
    set_bit(bs, offset, new)        Set bit in binary string
    set_byte(bs, offset, new)       Set byte in binary string
    sha224(bs   )                   SHA-224 hash
    sha256(bs)                      SHA-256 hash
    sha384(bs)                      SHA-384 hash
    sha512(bs)                      SHA-512 hash
*/

SELECT btrim('\000trim\001'::bytea, '\000\001'::bytea); -- \x7472696d
SELECT decode('123\000456', 'escape'); -- \x31323300343536
SELECT encode('123\000456'::bytea, 'escape'); -- 123\000456
SELECT get_bit('Th\000omas'::bytea, 45); -- 1
SELECT get_byte('Th\000omas'::bytea, 4); -- 109
SELECT length('jo\000se'::bytea); -- 5
SELECT md5('Th\000omas'::bytea); -- 8ab2d3c9689aaf18b4958c334c82d8b1
SELECT set_bit('Th\000omas'::bytea, 45, 0); -- \x5468006f6d4173
SELECT set_byte('Th\000omas'::bytea, 4, 64);-- \x5468006f406173
SELECT sha224('abc'); -- \x23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7
SELECT sha256('abc'); -- \xba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
SELECT sha384('abc'); -- \xcb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7
SELECT sha512('abc'); -- \xddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f
