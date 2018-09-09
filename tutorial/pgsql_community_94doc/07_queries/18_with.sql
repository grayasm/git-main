/*  Cap.7   Queries
    7.8     WITH queries (CTE =  Common Table Expressions)
    7.8.1   SELECT in WITH

    psql -d mytestdb -U pgmihai
    \i 18_with.sql
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
       ('Dealu Mare', 'Vin Alb',     10,   370.0), -- 37/L
       ('Dealu Mare', 'Vin Rosu',    20,   640.0), -- 32/L
       ('Dealu Mare', 'Vin Spumos',  30,  1620.0), -- 54/L
       ('Murfatlar',  'Vin Alb',     1,     54.0), -- 54/L
       ('Murfatlar',  'Vin Rosu',    21,  2310.0), -- 110/L
       ('Murfatlar',  'Vin Spumos',  41,  5535.0), -- 135/L
       ('Dragasani',  'Vin Alb',     5,    195.0), -- 39/L
       ('Dragasani',  'Vin Rosu',    35,  1505.0), -- 43/L
       ('Dragasani',  'Vin Spumos',  65,  4225.0), -- 65/L
       ('Cotnari',    'Vin Alb',     30,   750.0), -- 25/L
       ('Cotnari',    'Vin Rosu',    60,  3120.0), -- 52/L
       ('Cotnari',    'Vin Spumos',  90,  5310.0); -- 59/L


-- display per-product sales totals in only the top sales regions
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
   region   |  product   | product_units | product_sales 
------------+------------+---------------+---------------
 Cotnari    | Vin Rosu   |            60 |        3120.0
 Murfatlar  | Vin Alb    |             1 |          54.0
 Murfatlar  | Vin Spumos |            41 |        5535.0
 Dealu Mare | Vin Rosu   |            20 |         640.0
 Dealu Mare | Vin Spumos |            30 |        1620.0
 Dealu Mare | Vin Alb    |            10 |         370.0
 Murfatlar  | Vin Rosu   |            21 |        2310.0
 Cotnari    | Vin Alb    |            30 |         750.0
 Cotnari    | Vin Spumos |            90 |        5310.0
 Dragasani  | Vin Rosu   |            35 |        1505.0
 Dragasani  | Vin Alb    |             5 |         195.0
 Dragasani  | Vin Spumos |            65 |        4225.0
(12 rows)
*/


