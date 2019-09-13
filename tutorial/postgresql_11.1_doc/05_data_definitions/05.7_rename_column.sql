/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.7 Renaming a Column

    psql -d mytestdb -U pgmihai
    \i   05.7_rename_column.sql
    \?
    \qecho '\033[2J'
*/

/*      To rename a table: */
DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

ALTER TABLE products RENAME COLUMN product_no TO product_number;

INSERT INTO products VALUES
        (1, 'left door', 99.999),
        (2, 'right door', 99.999),
        (3, 'front shield', 49.999),
        (4, 'back shield', 100.999);

SELECT * FROM products;

/*
 product_number |     name     |  price
----------------+--------------+---------
              1 | left door    |  99.999
              2 | right door   |  99.999
              3 | front shield |  49.999
              4 | back shield  | 100.999
(4 rows)
*/
