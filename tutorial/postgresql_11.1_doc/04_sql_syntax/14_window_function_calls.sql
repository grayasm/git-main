/*  Chapter 4.2 Value Expressions
    4.2.8 Window Function Calls
	
	psql -d mytestdb -U pgmihai
	\dt  --list all tables
	\df  --list all functions
	\i 14_window_function_calls.sql
*/


/*  A 'window function' call represents the application of an aggregate-like
	function over some portion of the rows selected by a query. The window
	function is able to scan all the rows that would be part of the current
	row's group according to the grouping specification (PARTITION BY list)
	of the window function call. The syntax is:
	
	function_name ([expression [, expression ...]]) [FILTER (WHERE filter_clause)] OVER window_name;
	function_name ([expression [, expression ...]]) [FILTER (WHERE filter_clause)] OVER (window_definition);
	function_name (*) [FILTER (WHERE filter_clause)] OVER window_name;
	function_name (*) [FILTER (WHERE filter_clause)] OVER (window_definition);
	
	where window_definition has the syntax:
	[existing_window_name]
	[PARTITION BY expression [, ...]]
	[ORDER BY expression [ASC | DESC | USING operator] [NULLS {FIRST | LAST}] [,...]]
	[frame_clause]
	
	and the optional frame_clause can be one of:
	{RANGE | ROWS} frame_start
	{RANGE | ROWS} BETWEEN frame_start AND frame_end
	
	where frame_start and frame_end can be one of:
	UNBOUNDED PRECEDING
	value PRECEDING
	CURRENT ROW
	value FOLLOWING
	UNBOUNDED FOLLOWING
	
	A simplified version of a window function is like this:
	window_function(arg1, arg2, ..) OVER (PARTITION BY expression ORDER BY exp)
*/

-- we will create 2 tables named 'products' and 'product_groups' for the demo
DROP TABLE IF EXISTS products, product_groups CASCADE;

CREATE TABLE product_groups(group_id serial PRIMARY KEY,
							group_name varchar(255) NOT NULL
							);
							
CREATE TABLE products (product_id 	serial PRIMARY KEY,
					   product_name varchar(255) NOT NULL,
					   price decimal (11,2),
					   group_id int NOT NULL,
					   FOREIGN KEY(group_id) REFERENCES product_groups(group_id)
					   );

INSERT INTO product_groups (group_name) VALUES  ('Smartphone'),
												('Laptop'),
												('Tablet');
INSERT INTO products (product_name, group_id, price) VALUES
	('Microsoft Lumia', 1, 200),
	('HTC One',         1, 400),
	('Nexus',           1, 500),
	('iPhone',          1, 900),
	('HP Elite',        2, 1200),
	('Lenovo Thinkpad', 2, 700),
	('Sony VAIO',       2, 700),
	('Dell Vostro',     2, 800),
	('iPad',            3, 700),
	('Kindle Fire',     3, 150),
	('Samsung Galaxy Tab', 3, 200);
	
-- Let's look first at an aggregate function, which is similar to a window fn.
SELECT avg(price) FROM products;
/*
         avg
----------------------
 586.3636363636363636
*/

-- Let's apply the aggregate function to subsets of rows (e.g. GROUP BY clause);
SELECT group_name, avg(price) FROM products
	INNER JOIN product_groups USING (group_id)
	GROUP BY group_name;

/*
 group_name |         avg
------------+----------------------
 Tablet     | 350
 Smartphone | 500
 Laptop     | 850
*/

-- But the avg(sqlexpr); aggregate function reduces the number of rows;
-- A window function calculates the average but does NOT reduce the number of rows;

SELECT product_name, price, group_name, avg(price) OVER (PARTITION BY group_name)
	FROM products
	INNER JOIN product_groups
	USING (group_id);

/*
    product_name    |  price  | group_name |         avg
--------------------+---------+------------+----------------------
 HP Elite           | 1200.00 | Laptop     | 850
 Lenovo Thinkpad    |  700.00 | Laptop     | 850
 Sony VAIO          |  700.00 | Laptop     | 850
 Dell Vostro        |  800.00 | Laptop     | 850
 Microsoft Lumia    |  200.00 | Smartphone | 500
 HTC One            |  400.00 | Smartphone | 500
 Nexus              |  500.00 | Smartphone | 500
 iPhone             |  900.00 | Smartphone | 500
 iPad               |  700.00 | Tablet     | 350
 Kindle Fire        |  150.00 | Tablet     | 350
 Samsung Galaxy Tab |  200.00 | Tablet     | 350
*/


/* ROW_NUMBER(); window fn. assigns a running serial number to rows in
				 each partition.
*/
SELECT product_name, group_name, price, 
	row_number() OVER (PARTITION BY group_name ORDER BY price)
	FROM products
	INNER JOIN product_groups USING (group_id);

/*
    product_name    | group_name |  price  | row_number
--------------------+------------+---------+------------
 Sony VAIO          | Laptop     |  700.00 |          1
 Lenovo Thinkpad    | Laptop     |  700.00 |          2
 Dell Vostro        | Laptop     |  800.00 |          3
 HP Elite           | Laptop     | 1200.00 |          4
 Microsoft Lumia    | Smartphone |  200.00 |          1
 HTC One            | Smartphone |  400.00 |          2
 Nexus              | Smartphone |  500.00 |          3
 iPhone             | Smartphone |  900.00 |          4
 Kindle Fire        | Tablet     |  150.00 |          1
 Samsung Galaxy Tab | Tablet     |  200.00 |          2
 iPad               | Tablet     |  700.00 |          3 
 */
	

/*  RANK(); window fn. assigns ranking within an ordered partition.
            If the values of the 2 rows are the same, the rank() fn. assigns
			the same rank, with the next ranking(s) skipped.
*/
SELECT product_name, group_name, price,
	rank() OVER (PARTITION BY group_name ORDER BY price)
	FROM products
	INNER JOIN product_groups USING (group_id);

/*
    product_name    | group_name |  price  | rank
--------------------+------------+---------+------
 Sony VAIO          | Laptop     |  700.00 |    1
 Lenovo Thinkpad    | Laptop     |  700.00 |    1
 Dell Vostro        | Laptop     |  800.00 |    3
 HP Elite           | Laptop     | 1200.00 |    4
 Microsoft Lumia    | Smartphone |  200.00 |    1
 HTC One            | Smartphone |  400.00 |    2
 Nexus              | Smartphone |  500.00 |    3
 iPhone             | Smartphone |  900.00 |    4
 Kindle Fire        | Tablet     |  150.00 |    1
 Samsung Galaxy Tab | Tablet     |  200.00 |    2
 iPad               | Tablet     |  700.00 |    3
*/
	

/*  DENSE_RANK(); window function assigns the ranking within an ordered
				  partition, but the ranks are consecutive. The same ranks
				  are assigned to multiple rows and no ranks are skipped.
*/
SELECT product_name, group_name, price,
	dense_rank() OVER (PARTITION BY group_name ORDER BY price)
	FROM products
	INNER JOIN product_groups USING (group_id);
	
/*
    product_name    | group_name |  price  | dense_rank
--------------------+------------+---------+------------
 Sony VAIO          | Laptop     |  700.00 |          1
 Lenovo Thinkpad    | Laptop     |  700.00 |          1
 Dell Vostro        | Laptop     |  800.00 |          2
 HP Elite           | Laptop     | 1200.00 |          3
 Microsoft Lumia    | Smartphone |  200.00 |          1
 HTC One            | Smartphone |  400.00 |          2
 Nexus              | Smartphone |  500.00 |          3
 iPhone             | Smartphone |  900.00 |          4
 Kindle Fire        | Tablet     |  150.00 |          1
 Samsung Galaxy Tab | Tablet     |  200.00 |          2
 iPad               | Tablet     |  700.00 |          3
*/ 
	
	
/*  FIRST_VALUE(); fn. returns teh first value from the first row of the ordered
                   set, whereas the LAST_VALUE() function returns the last value
				   from the last row of the result set.
*/
SELECT product_name, group_name, price,
	first_value(price) OVER (PARTITION BY group_name ORDER BY price)
	AS lowest_price_per_group
	FROM products
	INNER JOIN product_groups USING (group_id);
	
/*
    product_name    | group_name |  price  | lowest_price_per_group
--------------------+------------+---------+------------------------
 Sony VAIO          | Laptop     |  700.00 |                 700.00
 Lenovo Thinkpad    | Laptop     |  700.00 |                 700.00
 Dell Vostro        | Laptop     |  800.00 |                 700.00
 HP Elite           | Laptop     | 1200.00 |                 700.00
 Microsoft Lumia    | Smartphone |  200.00 |                 200.00
 HTC One            | Smartphone |  400.00 |                 200.00
 Nexus              | Smartphone |  500.00 |                 200.00
 iPhone             | Smartphone |  900.00 |                 200.00
 Kindle Fire        | Tablet     |  150.00 |                 150.00
 Samsung Galaxy Tab | Tablet     |  200.00 |                 150.00
 iPad               | Tablet     |  700.00 |                 150.00
*/

-- using LAST_VALUE(); for the highest price per product group;
SELECT product_name, group_name, price,
	last_value(price) OVER (PARTITION BY group_name
							ORDER BY price
							RANGE BETWEEN UNBOUNDED PRECEDING
							AND UNBOUNDED FOLLOWING)
	AS highest_price_per_group
	FROM products
	INNER JOIN product_groups USING (group_id);
	
/*
    product_name    | group_name |  price  | highest_price_per_group
--------------------+------------+---------+-------------------------
 Sony VAIO          | Laptop     |  700.00 |                 1200.00
 Lenovo Thinkpad    | Laptop     |  700.00 |                 1200.00
 Dell Vostro        | Laptop     |  800.00 |                 1200.00
 HP Elite           | Laptop     | 1200.00 |                 1200.00
 Microsoft Lumia    | Smartphone |  200.00 |                  900.00
 HTC One            | Smartphone |  400.00 |                  900.00
 Nexus              | Smartphone |  500.00 |                  900.00
 iPhone             | Smartphone |  900.00 |                  900.00
 Kindle Fire        | Tablet     |  150.00 |                  700.00
 Samsung Galaxy Tab | Tablet     |  200.00 |                  700.00
 iPad               | Tablet     |  700.00 |                  700.00
*/
