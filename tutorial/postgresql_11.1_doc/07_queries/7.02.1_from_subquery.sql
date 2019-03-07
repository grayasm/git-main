/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause
    7.2.1.3 Subqueries

    psql -d mytestdb -U pgmihai
    \i 7.02.1_from_subquery.sql
    \?
    \qecho '\033[2J'
*/


/*      A subquery can be:
        > specifying a derived table
        > a VALUES list
*/

DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (id integer, name text, price numeric);
INSERT INTO products VALUES (1, 'Butter', 2.99), (2, 'Milk', 3.45),
                            (3, 'Bread', 1.19), (4, 'Honey', 5.55);


SELECT a.* FROM (SELECT * FROM products) AS a;
/*
 id |  name  | price
----+--------+-------
  1 | Butter |  2.99
  2 | Milk   |  3.45
  3 | Bread  |  1.19
  4 | Honey  |  5.55
(4 rows)
*/

SELECT * FROM (VALUES ('anne','smith'),('bob','johnes'),('joe','blow'))
        AS names(first,last);
/*
 first |  last
-------+--------
 anne  | smith
 bob   | johnes
 joe   | blow
(3 rows)
*/
