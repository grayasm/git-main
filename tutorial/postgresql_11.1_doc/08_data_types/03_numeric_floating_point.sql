/*  Cap.8   Data Types
    8.1     Numeric Types
    8.1.3   Floating-Point Types

    psql -d mytestdb -U pgmihai
    \i 03_numeric_floating_point.sql
    \?
    \qecho '\033[2J'
*/


/*  Name               Size      Description               Range
   -----------------+---------+--------------------+-------------------------
    real              4 bytes   variable-precision,  6 decimal digits precision
                                inexact              range 1E-37 to 1E+37

    double precision  8 bytes   variable-precision   15 decimal digits precision
                                inexact              range 1E-307 to 1E+308

    float(24)         4 bytes   same as real         mantissa has 24 bits
    float(53)         8 bytes   same as d.prec.      mantissa has 53 bits
   ---------------------------------------------------------------------------

    These types are implementations of IEEE Standard 754 for Binary Floating-
    Point Arithmetic (single and double precision, respectively), to the extent
    that the underlying processor, operating system, and compiler support it.

    If you require exact storage and calculations use 'numeric' type.
    These types support special values: Infinity, -Infinity, NaN.

    float(p) as real             is in the range [float(1), float(24)]
    float(p) as double precision is in the range [float(25),float(53)]
    float is IEEE conformant. On non-IEEE platform it might be off a little.
*/

\x

SELECT '1.123456789123456789'::float,
       '1.123456789123456789'::double precision,
       '1.123456789123456789'::float(1),
       '1.123456789123456789'::float(2),
       '1.123456789123456789'::float(24),
       '1.123456789123456789'::float(48);

/*
Expanded display is on.
...
-[ RECORD 1 ]------------
float8 | 1.12345678912346
float8 | 1.12345678912346
float4 | 1.12346
float4 | 1.12346
float4 | 1.12346
float8 | 1.12345678912346
*/

DROP TABLE IF EXISTS floatingp CASCADE;
CREATE TABLE floatingp (db double precision,
                        f1 float(1));

INSERT INTO floatingp VALUES (22.0/7.0, 22.0 / 7.0);

SELECT * FROM floatingp;
/*
-[ RECORD 1 ]--------
db | 3.14285714285714
f1 | 3.14286

Expanded display is off.
*/

\x
