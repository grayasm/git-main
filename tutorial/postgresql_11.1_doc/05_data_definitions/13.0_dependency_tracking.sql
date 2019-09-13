/*  Chapter 5. Data Definition
    5.13. Dependency tracking.

    psql -d mytestdb -U pgmihai
    \i   13.0_dependency_tracking.sql
    \?
    \qecho '\033[2J'
*/



/*      To ensure the integrity of the entire database structure, PostgreSQL
        makes sure that you cannot drop objects that other objects still
        depend on.
*/
DROP TABLE IF EXISTS orders, products;

CREATE TABLE products (
        product_no      integer PRIMARY KEY,
        name            text,
        price           numeric);

CREATE TABLE orders (
        order_it        integer PRIMARY KEY,
        product_no      integer REFERENCES products (product_no),
        quantity        integer);

INSERT INTO products VALUES (1001, 'pasta de dinti colgate', 2.80);
INSERT INTO orders   VALUES (10, 1001, 20);
SELECT * FROM products;

/*      According to the SQL standard, specifying either RESTRICT or CASCADE
        is required. No database system actually enforces that rule, but
        whether the default behavior is RESTRICT or CASCADE varies across
        systems.
*/
DROP TABLE products RESTRICT;

/*
ERROR:  cannot drop table products because other objects depend on it
DETAIL:  constraint orders_product_no_fkey on table orders depends on table products
HINT:  Use DROP ... CASCADE to drop the dependent objects too.
*/
