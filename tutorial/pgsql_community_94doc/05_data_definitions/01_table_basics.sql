/*  Chapter 5. Data Definition
    5.1. Table Basics

    psql -d mytestdb -U pgmihai
    \dt  --list all tables
    \df  --list all functions
    \i 01_table_basics.sql
*/

/*  1.  Number and order of columns is fixed and each column has a name;

    2.  No guarantees about the order of the rows in a table;
        Unless sorting is explicitly requested, the rows will appear in
        unspecified order;
        It is possible to have identical rows (duplicates) in a table;

    3.  Each column has a data type with semantics assigned to the stored data;
        A numeric type will not accept arbitrary text strings.
*/

DROP   TABLE IF EXISTS products;
CREATE TABLE products(product_no integer,
                      name       text,
                      price      numeric);
