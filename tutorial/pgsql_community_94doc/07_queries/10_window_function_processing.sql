/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.4   Window Function Processing

    psql -d mytestdb -U pgmihai
    \i 10_window_function_processing.sql
*/

/*      window_function(arg1,arg2,..) OVER (PARTITION BY expr ORDER BY expr);

        window_funtion: any built-in or user-defined aggregate function.
        PARTITION BY  : used to devide rows into groups or partitions.
        ORDER BY      : window function will process the rows in the order
                        specified by ORDER BY clause especially for the window
                        functions that are sensitive to the order such as
                        fist_value(), last_value(), nth_value().
*/

DROP TABLE IF EXISTS groups,products CASCADE;
CREATE TABLE groups (id         SERIAL PRIMARY KEY,
                     name       VARCHAR(255) NOT NULL);
                     
CREATE TABLE products (id       SERIAL PRIMARY KEY,
                       name     VARCHAR(255) NOT NULL,
                       price    DECIMAL,
                       id2      INT NOT NULL,
                       FOREIGN KEY(id2) REFERENCES groups(id));

INSERT INTO groups (name) VALUES ('handy'), ('laptop'), ('tablet');
INSERT INTO products (name, id2, price) VALUES ('Microsoft Lumia', 1, 200),
                                               ('HTC One',         1, 400),
                                               ('Nexus',           1, 500),
                                               ('iPhone',          1, 900), --avg=500
                                               ('HP Elite',        2, 1200),
                                               ('Lenovo Thinkpad', 2, 700),
                                               ('Sony VAIO',       2, 700),
                                               ('Dell Vostro',     2, 800), --avg=850
                                               ('iPad',            3, 700),
                                               ('Kindle Fire',     3, 150),
                                               ('Samsung Galaxy Tab',3,200);--avg=350



SELECT avg(price) FROM products;
/*
         avg          
----------------------
 586.3636363636363636
(1 row)
*/

SELECT name,avg(price) FROM products INNER JOIN groups USING (id) GROUP BY name;
