/*  Cap.8   Data Types
    8.2     Monetary Types

    psql -d mytestdb -U pgmihai
    \i   02.0_monetary.sql
    \?
    \qecho '\033[2J'
*/


/*  Name      Size      Description               Range
   ---------+---------+-----------------------+--------------------------
   money      8 bytes   currency ammount         -92233720368547758.08 to
                                                 +92233720368547758.07
   ----------------------------------------------------------------------

    The output is lc_monetary locale sensitive and by default it outputs
    its values in the US locale format: $1,200.00

    Internet wisdom at: https://postgrespro.com/list/thread-id/2286891
    "I personally find it pretty useless to be honest - especially because the
    currency symbol depends on the client. So if I store money value in the
    database, some clients see CHF, some see CZK, some see GBP and other might
    see EUR - all the same ammount. (I changed here symbols to ASCII)
    Which seems totally wrong because 10EUR is something completely different
    then 10CZK or 10GBP.
    Plus: inside a programming language (e.g. Java/JDBC) it's hard to work with
    the values because the database sends the values as string (it has to
    because of the currency symbol) but in reality it is a number - but you
    can't just convert the string to a number because of the symbol."
*/

DROP TABLE IF EXISTS finance CASCADE;
CREATE TABLE finance (
    id          SERIAL,
    name        CHAR(200),
    ammount     money
    );

INSERT INTO finance(name, ammount) VALUES ('Michael', 2470.00),
                                          ('Ammy',    1300.00),
                                          ('Julia',     50.00),
                                          ('Andrey',    10.00);
SELECT * FROM finance;
/*
 id |                name    |  ammount
----+------------------------+-----------
  1 | Michael                | $2,470.00
  2 | Ammy                   | $1,300.00
  3 | Julia                  |    $50.00
  4 | Andrey                 |    $10.00
(4 rows)
*/


/*  numeric, int and bigint can be casted directly to money.
    real and double precision must be cast to numeric first.
*/
SELECT '12.34'::float8::numeric::money;


/*  money value can be cast to numeric without loss of precision.
    Conversion to other types could potentially lose precision, and must be done
    in 2 stages:
*/
SELECT '52093.89'::money::numeric::float8;
