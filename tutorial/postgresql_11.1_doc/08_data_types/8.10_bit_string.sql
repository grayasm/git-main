/*  Cap.8   Data Types
    8.10.   Bit String Types

    psql -d mytestdb -U pgmihai
    \i 8.10_bit_string.sql
    \?
    \qecho '\033[2J'
*/

/*
        Bit strings are strings of 1's and 0's. They can be used to store or
        visualize bit masks. There are two SQL bit types:

        bit(n) and
        bit varying(n),

        where n is a positive integer.
        bit(n) type data must match the length n exactly; it is an error to
        attempt to store shorter or longer bit strings.
        bit varying(n) data is of variable length up to the maximum length n;
        longer strings will be rejected. Writing bit without a length is
        equivalent to bit(1), while bit varying without a length specification
        means unlimited length.
*/


DROP TABLE IF EXISTS test CASCADE;
CREATE TABLE test (a BIT(3), b BIT VARYING(5));
INSERT INTO test VALUES (B'101', B'00');
INSERT INTO test VALUES (B'10', B'101');
--ERROR:
--bit string length 2 does not match type bit(3)
INSERT INTO test VALUES (B'10'::bit(3), B'101');
SELECT * FROM test;

/*
  a  |  b
-----+-----
 101 | 00
 100 | 101
(2 rows)
*/
