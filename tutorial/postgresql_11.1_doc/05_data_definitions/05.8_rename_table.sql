/*  Chapter 5. Data Definition
    5.5.8 Renaming a Table

    psql -d mytestdb -U pgmihai
    \i   05.8_rename_table.sql
    \?
    \qecho '\033[2J'
*/


/*      To rename a table: */
DROP TABLE IF EXISTS products, items CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

INSERT INTO products VALUES
        (1, 'left door', 9.99),
        (2, 'right door', 9.99),
        (3, 'front shield', 11.50);

ALTER TABLE products RENAME TO items;

SELECT * FROM items;
/*
 product_no |     name     | price
------------+--------------+-------
          1 | left door    |  9.99
          2 | right door   |  9.99
          3 | front shield | 11.50
(3 rows)
*/
