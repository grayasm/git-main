/*  Cap.6   Data Manipulation
    6.3     Deleting Data

    psql -d mytestdb -U pgmihai
    \i   3_deleting_data.sql
    \?
    \qecho '\033[2J'
*/


/*      To remove rows from a table use DELETE command:

        DELETE FROM t WHERE p > 0;
        DELETE FROM t;
*/


DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (
        product_no    integer,
        name          text,
        price         numeric
        );

INSERT INTO products VALUES
        (1, 'Bread', 0.99),
        (2, 'Milk', 1.99),
        (3, 'Butter', 2.99),
        (4, 'Caffee', 3.99),
        (5, 'Sugar', 4.99),
        (6, 'Cheese', 5.99);

DELETE FROM products WHERE price > 3.99;

DELETE FROM products;
