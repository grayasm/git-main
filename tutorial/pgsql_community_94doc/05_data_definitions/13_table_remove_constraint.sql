/*  Chapter 5. Data Definition
    5.5. Modifying Tables
    5.5.4 Removing a Constraint
	
	psql -d mytestdb -U pgmihai
    \i 13_table_remove_constraint.sql
*/

/*      To remove a constraint you need to know its name. If you gave it a name
        then that's easy. Otherwise the system assigned a generated name,
		which you need to find out - use \t tablename to inspect table details.
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

ALTER TABLE products ADD CONSTRAINT some_name UNIQUE (product_no);
ALTER TABLE products DROP CONSTRAINT some_name;

INSERT INTO products VALUES
        (333, 'shampoo', 2.99),
		(334, 'soap',    1.99),
		(335, 'brush',   4.15);

INSERT INTO orders VALUES
        (1, 333, 3),
		(2, 334, 10),
		(3, 335, 5);
		
SELECT * FROM products;

/*
 product_no |  name   | price
------------+---------+-------
        333 | shampoo |  2.99
        334 | soap    |  1.99
        335 | brush   |  4.15
(3 rows)
*/
