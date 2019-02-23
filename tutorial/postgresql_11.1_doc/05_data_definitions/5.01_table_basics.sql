/*  Chapter 5. Data Definition
    5.1. Table Basics

    psql -d mytestdb -U pgmihai
    \i 5.01_table_basics.sql
    \?
    \qecho '\033[2J'
*/


/*     ` SQL does not guarantee the order of the rows in a table.
        When the table is read the rows will appear in unspecified order,
        unless sorted.
        Columns have types and semantics: cannot assign text to numerical type.
        An SQL Table can have maxim 250 up to 1600 columns, depending on their
        type.
*/
DROP TABLE IF EXISTS my_first_table;
DROP TABLE IF EXISTS products;

CREATE TABLE my_first_table (               -- not a meaningful name
       first_column  text,
       second_column integer
       );

CREATE TABLE products (                     -- more realistic
       product_no    integer,
       name          text,
       price         numeric
       );


-- If you no longer need the table, you can remove it with DROP TABLE.
DROP TABLE my_first_table;
DROP TABLE products;
