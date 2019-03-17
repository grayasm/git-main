/*  Chapter 4.2 Value Expressions
    4.2.4 Field Selection

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.2.04_field_selection.sql
    \?
    \qecho '\033[2J'
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
