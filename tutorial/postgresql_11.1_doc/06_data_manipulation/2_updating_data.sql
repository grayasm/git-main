/*  Cap.6   Data Manipulation
    6.2     Updating Data

    psql -d mytestdb -U pgmihai
    \i 6.2_updating_data.sql
    \?
    \qecho '\033[2J'
*/


/*      To update existing rows use the UPDATE command:
        UPDATE t SET p = 10 WHERE p = 5;

        UPDATE requires the following information:
        > table and column to update
        > new value of the column
        > which rows to update
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

UPDATE products SET price = 5 WHERE price = 4.99;
UPDATE products SET price = price + 1;
UPDATE products SET product_no = product_no + 100,
                    name = 'SUGAR',
                    price = price + 100
                WHERE name = 'Sugar';

SELECT * FROM products;
/*
 product_no |  name  | price
------------+--------+-------
          1 | Bread  |  1.99
          2 | Milk   |  2.99
          3 | Butter |  3.99
          4 | Caffee |  4.99
          6 | Cheese |  6.99
        105 | SUGAR  |   106
(6 rows)
*/
