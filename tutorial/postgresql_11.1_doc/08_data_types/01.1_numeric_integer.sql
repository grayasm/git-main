/*  Cap.8   Data Types
    8.1     Numeric Types
    8.1.1   Integer Types

    psql -d mytestdb -U pgmihai
    \i 01_numeric_integer.sql
    \?
    \qecho '\033[2J'
*/

/*  Name      Alias   Size      Description             Range
   ---------+-------+---------+---------------------+--------------------
   smallint   int2    2 bytes   small-range integer     -32768 to +32767

   integer    int4    4 bytes   typical choice for      -2147483648 to
                                integer                 +2147483647

   bigint     int8    8 bytes   large-range integer     -9223372036854775808 to
                                                        +9223372036854775807
   ---------------------------------------------------------------------
   The smallint is used only if desk space is at a premium.
   The bigint is used when the range of the integer is insufficient.
   The integer is the common choice.

   The type names int2,int4 and int8 are extensions (not specified by SQL)
   which are also used by some other SQL database systems.
*/


DROP TABLE IF EXISTS integers CASCADE;
CREATE TABLE integers (name text, si smallint, bi bigint, ni integer);
INSERT INTO integers VALUES ('min', -32768, -9223372036854775808, -2147483648),
                            ('max', 32767, 9223372036854775807, 2147483647),
                            ('mid', 0, 0, 0);
SELECT * FROM integers;
/*
 name |   si   |          bi          |     ni
------+--------+----------------------+-------------
 min  | -32768 | -9223372036854775808 | -2147483648
 max  |  32767 |  9223372036854775807 |  2147483647
 mid  |      0 |                    0 |           0
(3 rows)
*/



DROP TABLE IF EXISTS integers_ext CASCADE;
CREATE TABLE integers_ext (name text, i2 int2, i8 int8, i4 int4);
INSERT INTO integers_ext VALUES
            ('min', -32768, -9223372036854775808, -2147483648),
            ('max', 32767, 9223372036854775807, 2147483647),
            ('mid', 0, 0, 0);
SELECT * FROM integers_ext;
/*
 name |   i2   |          i8          |     i4
------+--------+----------------------+-------------
 min  | -32768 | -9223372036854775808 | -2147483648
 max  |  32767 |  9223372036854775807 |  2147483647
 mid  |      0 |                    0 |           0
(3 rows)
*/
