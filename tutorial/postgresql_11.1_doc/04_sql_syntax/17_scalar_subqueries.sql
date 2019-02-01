/*  Chapter 4.2 Value Expressions
    4.2.11 Scalar Subqueries

    psql -d mytestdb -U pgmihai
    \dt  --list all tables
    \df  --list all functions
    \i 17_scalar_subqueries.sql
*/


/*  A scalar subquery is an ordinary SELECT query in parantheses that returns
    exacly one row with one column.
    It is an error to use a query that returns more than one row or more than
    one column as a scalar subquery.
    If the subquery returns no rows, there is no error. The scalar result is
    taken to be null.
*/
DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (cat varchar, subcat varchar, amount float);
INSERT INTO my_table VALUES ('I-33', 'I-33', 100),
                            ('I-33', 'I-33', 10),
                            ('I-33', 'I-33', 1),
                            ('J-x',  'x',    21.1),
                            ('J-y',  'y',    2.1);

SELECT cat, (SELECT max(amount) FROM my_table WHERE cat = subcat) FROM my_table;

/*
 cat  | max
------+-----
 I-33 | 100
 I-33 | 100
 I-33 | 100
 J-x  | 100
 J-y  | 100
*/
