/*  Cap.7   Queries
    7.8     WITH queries (CTE =  Common Table Expressions)
    7.8.1   SELECT in WITH

    psql -d mytestdb -U pgmihai
    \i 18_with.sql
    \?
    \qecho '\033[2J'
*/


/*      WITH combines auxiliary statements into a larger query.
        It defines temporary tables that exists for one query only.
        Each auxiliary statement can be a SELECT,INSERT,UPDATE or DELETE.
        The WITH statement is attached to a primary statement that can also be
        a SELECT,INSERT,UPDATE or DELETE.
*/


DROP TABLE IF EXISTS orders CASCADE;
CREATE TABLE orders(id          SERIAL PRIMARY KEY,
                    region      VARCHAR(255) NOT NULL,
                    product     VARCHAR(255) NOT NULL,
                    quantity    INTEGER,                -- product units
                    amount      NUMERIC                 -- product sales
                    );

INSERT INTO orders (region,product,quantity,amount) VALUES
('regio1', 'p1', 100, 1000), ('regio2', 'p1', 10, 100), ('regio3', 'p1', 1, 10),
('regio1', 'p2', 120, 1200), ('regio2', 'p2', 12, 120), ('regio3', 'p2', 2, 20),
('regio1', 'p3', 130, 1300), ('regio2', 'p3', 13, 130), ('regio3', 'p3', 3, 30),
('regio1', 'p4', 140, 1400), ('regio2', 'p4', 14, 140), ('regio3', 'p4', 4, 40),
('regio1', 'p5', 150, 1500), ('regio2', 'p5', 15, 150), ('regio3', 'p5', 5, 50),
('regio1', 'p6', 160, 1600), ('regio2', 'p6', 16, 150), ('regio3', 'p6', 6, 60),
('regio1', 'p7', 170, 1700), ('regio2', 'p7', 17, 160), ('regio3', 'p7', 7, 70),
('regio1', 'p8', 180, 1800), ('regio2', 'p8', 18, 170), ('regio3', 'p8', 8, 80),
('regio1', 'p9', 190, 1900), ('regio2', 'p9', 19, 180), ('regio3', 'p9', 9, 90);



-- display per-product sales totals in only the top sales regions
-- each SELECT is dependent on previous SELECT
WITH regional_sales AS (
                    SELECT region, SUM(amount) AS total_sales
                    FROM orders
                    GROUP BY region),
     top_regions AS (
                    SELECT region
                    FROM regional_sales
                    WHERE total_sales > (SELECT SUM(total_sales)/10
                                         FROM regional_sales))
     SELECT region,
            product,
            SUM(quantity) AS product_units,
            SUM(amount)   AS product_sales
     FROM   orders
     WHERE  region IN (SELECT region FROM top_regions)
     GROUP BY region, product;


/*
 region | product | product_units | product_sales
--------+---------+---------------+---------------
 regio1 | p8      |           180 |          1800
 regio1 | p5      |           150 |          1500
 regio1 | p1      |           100 |          1000
 regio1 | p6      |           160 |          1600
 regio1 | p9      |           190 |          1900
 regio1 | p7      |           170 |          1700
 regio1 | p2      |           120 |          1200
 regio1 | p3      |           130 |          1300
 regio1 | p4      |           140 |          1400
(9 rows)
        Add ORDER BY product; to get the ordering;
*/
