/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.5 Changing a Column's Default Value

    psql -d mytestdb -U pgmihai
    \i   05.5_change_column_default_value.sql
    \?
    \qecho '\033[2J'
*/

/*      To set a new default for a column, use a commmand like: */
DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric   DEFAULT 9.99
        );

INSERT INTO products VALUES
        (1, 'left door'),
        (2, 'right door'),
        (3, 'front shield');

/*      Note that this doesn't affect any existing rows in the table, it just
        changes the default for future INSERT commands. */
ALTER TABLE products ALTER COLUMN price SET DEFAULT 7.77;
INSERT INTO products VALUES
        (4, 'back shield');

SELECT * FROM products;

/*
 product_no |     name     | price
------------+--------------+-------
          1 | left door    |  9.99
          2 | right door   |  9.99
          3 | front shield |  9.99
          4 | back shield  |  7.77
(4 rows)
*/
