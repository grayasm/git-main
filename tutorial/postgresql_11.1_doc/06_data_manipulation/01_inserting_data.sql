/*  Cap.6  Data Manipulation
    6.1.   Inserting Data

    psql -d mytestdb -U pgmihai
    \i 01_inserting_data.sql
    \?
    \qecho '\033[2J'
*/

/*      To create a new row, you can use one of the following:
        > INSERT, the short form
        > INSERT, with explicit columns
        > INSERT, with ommitted columns - using default values
        > INSERT, with ommitted columns - using DEFAULT
        > INSERT, with multiple rows
*/



DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer,
        name          text,
        price         numeric
        );

INSERT INTO products VALUES (1, 'Cheese', 9.99);
INSERT INTO products (product_no, name, price) VALUES (2, 'Cheese', 2.99);
INSERT INTO products (name, price, product_no) VALUES ('Cheese', 1.99, 3);
INSERT INTO products VALUES (4, 'Cheese');
INSERT INTO products (product_no, name, price) VALUES (5, 'Cheese', DEFAULT);
INSERT INTO products DEFAULT VALUES;
INSERT INTO products (product_no, name, price) VALUES
        (7, 'Cheese', 9.99),
        (8, 'Bread', 1.99),
        (9, 'Milk', 2.99);

SELECT * FROM products;
/*
 product_no |  name  | price
------------+--------+-------
          1 | Cheese |  9.99
          2 | Cheese |  2.99
          3 | Cheese |  1.99
          4 | Cheese |
          5 | Cheese |
            |        |
          7 | Cheese |  9.99
          8 | Bread  |  1.99
          9 | Milk   |  2.99
(9 rows)
*/
