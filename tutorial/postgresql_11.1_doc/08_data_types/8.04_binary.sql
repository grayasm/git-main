/*  Cap.8   Data Types
    8.4     Binary Data Types

    psql -d mytestdb -U pgmihai
    \i 07_binary.sql
    \?
    \qecho '\033[2J'
*/


/*
      Name        Storage Size                   Description
    ------------+-----------------------------+------------------------------
      bytea       1 or 4 bytes plus              variable-length binary string
                  the actual binary string
    --------------------------------------------------------------------------

     Binary strings allow storing octets of value zero and other "non-printable"
     octets (outside range 32 to 126). Character string disallow zero octets,
     or any other octet values that are invalid according to the DB's selected
     character set encoding.
     Operations on binary strings process the actual bytes, whereas for
     character strings depends on locale settings.
     Binary strings are appropriate for storing data as "raw bytes".

*/

DROP TABLE IF EXISTS sbinary CASCADE;
CREATE TABLE sbinary
(
    id      SERIAL,
    bval    BYTEA
);


/*   8.4.1 bytea as Hex Format
           The binary string value is of the form: E'\\x......'
           The number of digits must be even (not odd): FF or FF00 or 00FF11
           The hexa digits can be either lower or upper case: ffee
           The whitespace is allowed between digit pairs only.
*/

INSERT INTO sbinary (bval) VALUES (E'\\x0123456789');       -- ok
INSERT INTO sbinary (bval) VALUES (E'\\x012');              -- error
-- ERROR:  invalid hexadecimal data: odd number of digits

INSERT INTO sbinary (bval) VALUES (E'\\x01 23 45 67 89');   -- ok
SELECT * FROM sbinary;
/*
 id |     bval
----+--------------
  1 | \x0123456789
  2 | \x0123456789
(2 rows)
*/



/*   8.4.2 bytea as Escape Format
           The binary string value is of the form: E'text in english...'
           The values that are not ASCII must be escaped in Octal: E'\\176' (~)
           The values that must be escaped: 0, 39('), 92(\), [0,31], [127,255]
           The whitespace this time is not discarded but saved as 20.
*/

INSERT INTO sbinary (bval) VALUES (E'english text'), -- \x656e676c6973682074657874
                                  (E'\\000a'),       -- \x0061       a=0x61
                                  (E'\\000a\\000a'), -- \x00610061
                                  (E'\\000 a'),      -- \x002061
                                  (E'\\176');        -- \x7e         ~=0x7e

SELECT * FROM sbinary WHERE id > 2;

/*
 id |            bval
----+----------------------------
  3 | \x656e676c6973682074657874
  4 | \x0061
  5 | \x00610061
  6 | \x002061
  7 | \x7e
(5 rows)
*/
