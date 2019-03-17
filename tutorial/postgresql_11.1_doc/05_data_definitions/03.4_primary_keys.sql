/*  Chapter 5. Data Definition
    5.3.4. Primary Keys

    psql -d mytestdb -U pgmihai
    \i 5.03.4_primary_keys.sql
    \?
    \qecho '\033[2J'
*/


/*      A primary key constraint is simply a combination of a unique constraint
        and a not-null contraint. */

DROP TABLE IF EXISTS products;
CREATE TABLE products (
        product_no    integer   UNIQUE  NOT NULL,
        name          text,
        price         numeric
        );
INSERT INTO products VALUES
       (1, 'name', 99.9),
       (2, 'name', 99.9),
       (1, 'diff', 33.3);  -- violation of the constraint
/*
ERROR:  duplicate key value violates unique constraint "products_product_no_key"
DETAIL:  Key (product_no)=(1) already exists.
*/


/*      Use syntax PRIMARY  KEY  */
DROP TABLE products;
CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );
INSERT INTO products VALUES
       (1, 'name', 99.9),
       (2, 'name', 99.9),
       (1, 'diff', 33.3);  -- violation of the key
/*
ERROR:  duplicate key value violates unique constraint "products_pkey"
DETAIL:  Key (product_no)=(1) already exists.
*/
SELECT * FROM products;
/*
 product_no | name | price
------------+------+-------
(0 rows)
*/


/*      PRIMARY KEY can also constrain more than one column.  */
DROP TABLE products;
CREATE TABLE products (
        a    integer,
        b    integer,
        c    integer,
        PRIMARY KEY (a, c)
        );
