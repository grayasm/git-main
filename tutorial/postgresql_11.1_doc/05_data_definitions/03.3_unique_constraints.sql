/*  Chapter 5. Data Definition
    5.3.3.     Unique Constraints

    psql -d mytestdb -U pgmihai
    \i 5.03.3_unique_constraints.sql
    \?
    \qecho '\033[2J'
*/


/*      Unique constraints ensure the column value is unique across all rows.*/
DROP TABLE IF EXISTS products;
CREATE TABLE products (
        product_no    integer   UNIQUE,
        name          text,
        price         numeric
        );
INSERT INTO products VALUES (1, 'first',  99.9);
INSERT INTO products VALUES (2, 'second', 33.3);
INSERT INTO products VALUES (1, 'third',  44,4);
/*
ERROR:  INSERT has more expressions than target columns
LINE 1: INSERT INTO products VALUES (1, 'third',  44,4);
*/
SELECT * FROM products;
/*
 product_no |  name  | price
------------+--------+-------
          1 | first  |  99.9
          2 | second |  33.3
(2 rows)
*/


/*      When a unique constraints refers to a group of columns, the columns are
        listed separated by commas: */
DROP TABLE products;
CREATE TABLE products (
        pname         text,
        palias        text,
        price         numeric,
        UNIQUE(pname, palias)
        );
INSERT INTO products VALUES ('lego', 'game', 99.9);
INSERT INTO products VALUES ('mario', 'tetris', 22.3);
INSERT INTO products VALUES ('lego', 'game', 99.3);
/*
ERROR:  duplicate key value violates unique constraint "products_pname_palias_key"
DETAIL:  Key (pname, palias)=(lego, game) already exists
*/
SELECT * FROM products;
/*
 pname | palias | price
-------+--------+-------
 lego  | game   |  99.9
 mario | tetris |  22.3
(2 rows)
*/
