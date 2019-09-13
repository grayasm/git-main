/*  Chapter 5. Data Definition
    5.3.5. Foreign Keys

    psql -d mytestdb -U pgmihai
    \i   03.5_foreign_keys.sql
    \?
    \qecho '\033[2J'
*/


/*      A foreign key constraint specifies that the values in a column (or a
        group of columns) must match the values appearing in some row of another
        table. We say this maintains the referential integrity between two
        related tables.
*/
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS orders CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );
CREATE TABLE orders (
        order_id      integer   PRIMARY KEY,
        product_no    integer   REFERENCES products (product_no),
        quantity      integer
        );

INSERT INTO products VALUES (333, 'shampoo', 2.99);
INSERT INTO orders VALUES (1, 333, 3);
INSERT INTO orders VALUES (2, 330, 10);  -- error, 330 does not exist
/*
ERROR:  insert or update on table "orders" violates foreign key constraint "orders_product_no_fkey"
DETAIL:  Key (product_no)=(330) is not present in table "products".
*/



/*      We know that foreign keys disallow creation of orders that do not
        relate to any products. What if a product is removed after an order
        is created that references it?
        SQL allows few options:
        - disallow deleting a referenced product
        - delete the orders as well
        - something else?
*/
DROP TABLE products CASCADE;
DROP TABLE orders CASCADE;
DROP TABLE IF EXISTS order_items;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

CREATE TABLE orders (
        order_id      integer   PRIMARY KEY,
        address       text
        );

CREATE TABLE order_items (
        product_no    integer   REFERENCES products ON DELETE RESTRICT,
        order_id      integer   REFERENCES orders   ON DELETE CASCADE,
        quantity      integer,
        PRIMARY KEY (product_no, order_id)
        );

INSERT INTO products VALUES
        (333, 'shampoo', 2.99),
        (334, 'soap', 1.99);       -- 2 products

INSERT INTO orders VALUES
        (1, '1Way 13, Boston'),
        (2, '2Way 14, Boston');    -- 2 orders

INSERT INTO order_items VALUES
        (333, 1, 100),
        (334, 2, 100);             -- 100 units from both products

DELETE FROM products WHERE product_no = 333;
/*
ERROR:  update or delete on table "products" violates foreign key constraint "order_items_product_no_fkey" on table "order_items"
DETAIL:  Key (product_no)=(333) is still referenced from table "order_items".
*/

DELETE FROM orders WHERE order_id = 2;
SELECT * FROM orders;
/*
 order_id |     address
----------+-----------------
        1 | 1Way 13, Boston
(1 row)
*/
