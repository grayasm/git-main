/*  Cap.8   Data Types
    8.1     Numeric Types
    8.1.2   Arbitrary Precision Numbers

    psql -d mytestdb -U pgmihai
    \i   01.2_numeric_arbitrary_precision.sql
    \?
    \qecho '\033[2J'
*/


/*  Name      Size      Description                  Range
   ---------+---------+---------------------------+---------------------------
    decimal   variable  user-specified precision,    up to 131072 digits before
                        exact                        the decimal point;
                                                     up to 16383 digits after
                                                     the decimal point

    numeric   variable  user-specified precision,    up to 131072 digits before
                        exact                        the decimal point;
                                                     up to 16383 digits after
                                                     the decimal point
   ----------------------------------------------------------------------------
    It is recommended for storing monetary amounts for precision of calculation.
    It is very slow compared with integers and floating point types.
    Use the synatx:  NUMERIC(precision, scale)
                     NUMERIC(precision)
                     NUMERIC

    The numeric type allows the special value NaN.
    Any operation with NaN yields another NaN.
    NaN is not equal with NaN, or any other value.
    In sorting NaN values as equal, and greater than all non-NaN values.
*/

/*  http://www.postgresqltutorial.com/postgresql-numeric  */

DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (id serial PRIMARY KEY,
                       name VARCHAR NOT NULL,
                       price NUMERIC(5, 2));

INSERT INTO products (name, price) VALUES ('Phone', 500.215),
                                          ('Tablet', 500.214);
SELECT * FROM products;
/*
 id |  name  | price
----+--------+--------
  1 | Phone  | 500.22
  2 | Tablet | 500.21
(2 rows)
*/


INSERT INTO products (name, price) VALUES ('Phone', 123456.21);
/*
ERROR:  numeric field overflow
DETAIL:  A field with precision 5, scale 2 must round to an absolute value less than 10^3.
*/


UPDATE products SET price = 'NaN' WHERE id = 1;
SELECT * FROM products ORDER BY price ASC;
/*
 id |  name  | price
----+--------+--------
  2 | Tablet | 500.21
  1 | Phone  |    NaN
(2 rows)
*/
