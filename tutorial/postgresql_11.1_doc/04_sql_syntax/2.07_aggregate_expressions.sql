/*  Chapter 4.2 Value Expressions
    4.2.7 Aggregate Expressions

    psql -d mytestdb -U pgmihai
    \i   2.07_aggregate_expressions.sql
    \?
    \qecho '\033[2J'
*/

/*  Aggregate functions compute a single result from a set of input values.
    They are split in 3 categories:
    1) general purpose aggregate functions
    2) aggregate functions for statistics
    3) ordered-set aggregate functions
    4) hypothetical-set aggregate functions
*/

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (id int, name varchar, age int, address varchar, salary float);
INSERT INTO my_table VALUES(1, 'Paul' ,  32, 'California',  20000);
INSERT INTO my_table VALUES(2, 'Allen',  25, 'Texas',       15000);
INSERT INTO my_table VALUES(3, 'Teddy',  23, 'Norway',      20000);
INSERT INTO my_table VALUES(4, 'Mark' ,  25, 'Rich-Mond',   65000);
INSERT INTO my_table VALUES(5, 'David',  27, 'Texas',       85000);
INSERT INTO my_table VALUES(6, 'Kim'  ,  22, 'South-Hall',  45000);
INSERT INTO my_table VALUES(7, 'James',  24, 'Houston',     10000);



--  1) General purpose aggregate functions
SELECT avg(salary) FROM my_table;

/*
       avg
------------------
 37142.8571428571
 */


--  2) Aggregate functions for statistics
/* regr_count(Y, X)  ;number of input rows in which both expressions are nonnull
*/
DROP TABLE IF EXISTS sales CASCADE;
CREATE TABLE sales (year int, month int, emp_id int, product int, amount float);
INSERT INTO sales VALUES (2006, 1, 21, 1, 16034.84);
INSERT INTO sales VALUES (2006, 2, 21, 1, 16034.84);
INSERT INTO sales VALUES (2006, 3, 21, 1,     NULL);
INSERT INTO sales VALUES (2006, 4, 21, 2, 16034.84);
INSERT INTO sales VALUES (2006, 5, 21, 2, 16034.84);
INSERT INTO sales VALUES (2006, 6, 21, 2, 17055.83);
INSERT INTO sales VALUES (2006, 7, 21, 2,     NULL);

SELECT product, regr_count(amount, month) AS count FROM sales GROUP BY product;

--  3) Ordered-Set Aggregate Functions
--  4) Hypothetical-Set Aggregate Functions
