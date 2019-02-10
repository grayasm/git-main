/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.1 Adding a column

    psql -d mytestdb -U pgmihai
    \i 10_table_add_column.sql
    \?
    \qecho '\033[2J'
*/

/*      To add a column, use a command like: */
DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (
        product_no    integer   UNIQUE,
        name          text,
        price         numeric
        );
ALTER TABLE products ADD COLUMN description text CHECK (description <> '');

INSERT INTO products VALUES (1, 'first',  99.9, 'prod 1');
INSERT INTO products VALUES (2, 'second', 33.3, 'prod 2');
INSERT INTO products VALUES (3, 'third',  44.4, 'prod 3');
SELECT * FROM products;

/*
 product_no |  name  | price | description
------------+--------+-------+-------------
          1 | first  |  99.9 | prod 1
          2 | second |  33.3 | prod 2
          3 | third  |  44.4 | prod 3
(3 rows)
*/
