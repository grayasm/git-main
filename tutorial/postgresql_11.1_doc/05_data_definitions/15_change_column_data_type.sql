/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.6 Changing a Column's Data Type

    psql -d mytestdb -U pgmihai
    \i 15_change_column_data_type.sql
    \?
    \qecho '\033[2J'
*/

/*      To convert a column to a different data type, use a command like: */
DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

INSERT INTO products VALUES
        (1, 'left door', 99.999),
        (2, 'right door', 99.999),
        (3, 'front shield', 49.999);

/*      This will succeed only if each entry in the column can be converted
        to the new type by an implicit cast. If a more complex conversion is
        needed, you can add a USING clause that specifies how to compute
        the new values from the old.
*/
ALTER TABLE products ALTER COLUMN price TYPE numeric (10,2);

INSERT INTO products VALUES
        (4, 'back shield', 100.999);

SELECT * FROM products;

/*
 product_no |     name     | price
------------+--------------+--------
          1 | left door    | 100.00
          2 | right door   | 100.00
          3 | front shield |  50.00
          4 | back shield  | 101.00
(4 rows)
*/
