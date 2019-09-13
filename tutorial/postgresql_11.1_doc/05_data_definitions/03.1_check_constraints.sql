/*  Chapter 5. Data Definition
    5.3.1.  Check Constraints

    psql -d mytestdb -U pgmihai
    \i   03.1_check_constraints.sql
    \?
    \qecho '\033[2J'
*/



/*      Check if a column value is positive.*/
DROP TABLE IF EXISTS products;
CREATE TABLE products (
       product_no    integer,
       name          text,
       price         numeric    CHECK (price>0)
       );
INSERT INTO products VALUES
       (100, 'good product', 33.3),
       (101, 'good product', 33.5),
       (102, 'bad violated'  -3.3);  -- violates the constraint
/*
ERROR:  invalid input syntax for type numeric: "bad violated"
LINE 4:         (102, 'bad violated'  -3.3);
*/


/*      Give a constraint a separate name.*/
DROP TABLE products;
CREATE TABLE products (
       product_no    integer,
       name          text,
       price         numeric   CONSTRAINT positive_price CHECK (price > 0)
       );
INSERT INTO products VALUES
       (100, 'good product', 33.3),
       (101, 'good product', 33.5),
       (102, 'bad violated'  -3.3);  -- violates the constraint
/*
ERROR:  invalid input syntax for type numeric: "bad violated"
LINE 4:         (102, 'bad violated'  -3.3);
*/


/*      A check constraint can also refer to several columns.*/
DROP TABLE products;
CREATE TABLE products (
       product_no              integer,
       name                    text,
       price                   numeric   CHECK (price > 0),
       discounted_price        numeric   CHECK (discounted_price > 0),
       CHECK (price > discounted_price)
       );
INSERT INTO products VALUES (10, 'invalid', 10, 10);
/*
ERROR:  new row for relation "products" violates check constraint "products_check"
DETAIL:  Failing row contains (10, invalid, 10, 10).
*/


/*      Use a more flexible syntax.*/
DROP TABLE products;
CREATE TABLE products (
       product_no          integer,
       name                text,
       price               numeric   CHECK (price > 0),
       discounted_price    numeric,
       CHECK (discounted_price > 0 AND price > discounted_price)
       );
INSERT INTO products VALUES (10, 'invalid prod.', 29.99, 30.0);
/*
ERROR:  new row for relation "products" violates check constraint "products_check"
DETAIL:  Failing row contains (10, invalid prod., 29.99, 30.0).
*/
