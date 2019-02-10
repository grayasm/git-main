/*  Chapter 4.2 Value Expressions
    4.2.9 Type Casts

    Run with:
    psql -d mytestdb -U pgmihai
    \i 15_type_casts.sql
    \?
    \qecho '\033[2J'
*/


/*  A type cast specifies a conversion from one data type to another.
    PostgreSQL accepts 2 syntaxes for type casts:

    CAST (expression AS type)
    expression::type
*/

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (val int, dtime date);

INSERT INTO my_table VALUES
       ( '100'::INTEGER,         '2015-01-01'::DATE),
       ( CAST('100' AS INTEGER), CAST('01-OCT-2015' AS DATE) );

SELECT * FROM my_table;

/*
 val |   dtime
-----+------------
 100 | 2015-01-01
 100 | 2015-10-01
*/
