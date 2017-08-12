/*  Chapter 4.2 Value Expressions
    4.2.4 Field Selection

    run sample with:
    psql -d mytestdb -U pgmihai
    \dt  --list tables
    \df  --list functions
    \i 10_field_selection.sql
*/


DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (name varchar, email varchar);
INSERT INTO my_table VALUES ('li yuan', 'li@email.ch');


/*  expression.fieldname

    If an expression yields a value of a composite type (row type), then
    a specific field of the row can be extracted by writing:

    mytable.mycolumn
    $1.somecolumn
    (rowfunction(a,b)).col3
*/

SELECT my_table.name, my_table.email FROM my_table;
