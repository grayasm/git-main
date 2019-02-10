/*  Chapter 5. Data Definition
    5.2. Default Values

    psql -d mytestdb -U pgmihai
    \i 02_default_values.sql
    \?
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS my_table CASCADE;


/*     When a new row is added and no values are specified for some columns
       the default value is null value.

       A column can be asigned a default value; e.g. DEFAULT keyword.
*/
CREATE TABLE my_table (product integer,
                       name    text,
                       price   numeric    DEFAULT 9.99
                       );
INSERT INTO my_table VALUES (1, 'left door'),
                            (2, 'right door'),
                            (3, 'front shield'),
                            (4, 'back shield');

SELECT * FROM my_table;

/*
 product |     name     | price
---------+--------------+-------
       1 | left door    |  9.99
       2 | right door   |  9.99
       3 | front shield |  9.99
       4 | back shield  |  9.99
*/


/*      The default value can be an expression evaluated whenever the value is
        inserted.
*/
DROP TABLE my_table;
CREATE TABLE my_table (product_name  text,
                       product_no    SERIAL,
                       date_time     timestamp with time zone DEFAULT clock_timestamp());

INSERT INTO my_table (product_name) VALUES ('left door'),
                                           ('right door'),
                                           ('front shield'),
                                           ('back shield');
SELECT * FROM my_table;
/*
 product_name | product_no |           date_time
--------------+------------+-------------------------------
 left door    |          1 | 2018-05-27 11:21:25.452235+02
 right door   |          2 | 2018-05-27 11:21:25.452335+02
 front shield |          3 | 2018-05-27 11:21:25.45234+02
 back shield  |          4 | 2018-05-27 11:21:25.452344+02
(4 rows)
*/
