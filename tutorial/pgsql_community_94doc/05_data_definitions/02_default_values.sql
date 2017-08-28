/*  Chapter 5. Data Definition
    5.2. Default Values

    psql -d mytestdb -U pgmihai
    \dt  --list all tables
    \df  --list all functions
    \i 02_default_values.sql
*/


DROP TABLE IF EXISTS my_table CASCADE;


/*  1.  When a new row is added and no values are specified for some columns
        the default value is null value.

    2.  A column can be asigned a default value; e.g. DEFAULT keyword.
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


/*  3.  The default value can be an expression evaluated whenever the value is
        inserted.
*/
DROP TABLE my_table;
CREATE TABLE my_table (product_name  text,
                       product_no    SERIAL,
                       date_time     clock_timestamp());

INSERT INTO my_table (product_name) VALUES ('left door'),
                                           ('right door'),
                                           ('front shield'),
                                           ('back shield');

SELECT * FROM my_table;
