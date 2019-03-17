/*  Chapter 4.2. Value Expressions
    4.2.13. Row Constructors

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.2.13_row_constructors.sql
    \?
    \qecho '\033[2J'
*/


/*  ROW(expression [, expression ...])
    A row constructor is an expression that builds a row value (also called a
    composite value) using values for its members fields.
*/
SELECT ROW (1, 2.5, 'this is test');

/*
          row
------------------------
 (1,2.5,"this is test")
*/


/*  A ROW constructor can include the syntax rowvalue.*    which will be
    expanded to a list of the elements of the row value.
*/
DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (f1 int, f2 int);
INSERT INTO my_table VALUES (1, 2), (3, 4), (5, 6), (7, 8), (9, 10);

SELECT ROW(my_table.f1, my_table.f2, 42) FROM my_table;
/*
    row
-----------
 (1,2,42)
 (3,4,42)
 (5,6,42)
 (7,8,42)
 (9,10,42)
*/


/*  By default, the value create by ROW expression is of an anonymous record
    type. If necessary, it can be cast to a named composite type - either the
    row type of the table, or a composite type created with CREATE TYPE AS.
*/
DROP TYPE IF EXISTS row_type;
CREATE TYPE row_type AS (f1 int, f2 int, f3 int);
SELECT ROW(my_table.f1, my_table.f2, 42)::row_type AS row_name FROM my_table;

/*
 row_name
-----------
 (1,2,42)
 (3,4,42)
 (5,6,42)
 (7,8,42)
 (9,10,42)
*/
