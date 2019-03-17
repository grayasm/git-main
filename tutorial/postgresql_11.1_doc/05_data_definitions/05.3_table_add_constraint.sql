/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.3 Adding a Constraint

    psql -d mytestdb -U pgmihai
    \i 5.05.3_table_add_constraint.sql
    \?
    \qecho '\033[2J'
*/

/*      To add a constraint, the table constraint syntax is used. */
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS orders CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );
CREATE TABLE orders (
        order_id      integer   PRIMARY KEY,
        product_no    integer   /*REFERENCES products (product_no)*/,
        quantity      integer
        );

ALTER TABLE products ADD CHECK (name <> '');
ALTER TABLE products ADD CONSTRAINT some_name UNIQUE (product_no);
ALTER TABLE orders   ADD CONSTRAINT othername FOREIGN KEY (product_no) REFERENCES products(product_no);


INSERT INTO products VALUES
        (333, 'shampoo', 2.99),
        (334, 'soap',    1.99),
        (335, 'brush',   4.15);

INSERT INTO orders VALUES
        (1, 333, 3),
        (2, 334, 10),
        (3, 335, 15);
SELECT * FROM products;

/*
 product_no |  name   | price
------------+---------+-------
        333 | shampoo |  2.99
        334 | soap    |  1.99
        335 | brush   |  4.15
(3 rows)
*/
