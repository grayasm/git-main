/*  Chapter 5. Data Definition
    5.3.2.     Not-Null Constraints

    psql -d mytestdb -U pgmihai
    \i 04_notnull_constraints.sql
*/


/*  [Not-Null constraint forbids a NULL value coresp. to that column.]*/
DROP TABLE IF EXISTS products;
CREATE TABLE products (
        product_no    integer NOT NULL,
        name          text    NOT NULL,
        price         numeric
        );
INSERT INTO products VALUES (1,    'first',  99.9);
INSERT INTO products VALUES (NULL, 'second', 33.3);
/*
ERROR:  null value in column "product_no" violates not-null constraint
DETAIL:  Failing row contains (null, second, 33.3)
*/
SELECT * FROM products;
/*
 product_no | name  | price
------------+-------+-------
          1 | first |  99.9
(1 row)
*/



/*  [A column can have more than one costraint.]*/
DROP TABLE products;
CREATE TABLE products (
        product_no    integer   NOT NULL,
        name          text      NOT NULL,
        price         numeric   NOT NULL CHECK (price > 0)
        );
INSERT INTO products VALUES (1, 'first', 99.9);
INSERT INTO products VALUES (1, NULL,  -103.3);
/*
ERROR:  null value in column "name" violates not-null constraint
DETAIL:  Failing row contains (1, null, -103.3).
*/
SELECT * FROM products;
/*
 product_no | name  | price
------------+-------+-------
          1 | first |  99.9
(1 row)
*/
