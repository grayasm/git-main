/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.7 Renaming a Column
	
	psql -d mytestdb -U pgmihai
    \i 16_rename_column.sql
*/

/*      To rename a table: */
DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

ALTER TABLE products RENAME TO items;

INSERT INTO items VALUES
        (1, 'left door', 99.999),
        (2, 'right door', 99.999),
        (3, 'front shield', 49.999),
		(4, 'back shield', 100.999);

SELECT * FROM items;

/*
 product_no |     name     |  price
------------+--------------+---------
          1 | left door    |  99.999
          2 | right door   |  99.999
          3 | front shield |  49.999
          4 | back shield  | 100.999
(4 rows)
*/
