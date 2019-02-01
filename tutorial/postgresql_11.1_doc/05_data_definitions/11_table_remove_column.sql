/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.2 Removing a Column
	
	psql -d mytestdb -U pgmihai
    \i 10_table_remove_column.sql
*/

/*      To remove a column, use a command like: */
DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (
        product_no    integer   UNIQUE,
        name          text,
        price         numeric,
		description   text CHECK (description <> '')
        );
ALTER TABLE products DROP COLUMN description;

INSERT INTO products VALUES (1, 'first',  99.9);
INSERT INTO products VALUES (2, 'second', 33.3);
INSERT INTO products VALUES (3, 'third',  44.4);
SELECT * FROM products;

/*
 product_no |  name  | price
------------+--------+-------
          1 | first  |  99.9
          2 | second |  33.3
          3 | third  |  44.4
(3 rows)
*/
