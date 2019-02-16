/*  Chapter 4.2 Value Expressions
    4.2.1 Column References

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.2.01_column_references.sql
    \?
    \qecho '\033[2J'
*/


-- correlation.columnname
-- where correlation is the name of a table, or an alias for a table

DROP TABLE IF EXISTS my_table;
CREATE TABLE my_table (name varchar(80), age int, salary REAL);
INSERT INTO  my_table VALUES ('mike', 43, 43e+3);
INSERT INTO  my_table VALUES ('john', 41, 81e+3);


SELECT my_table.age, my_table.name, my_table.salary FROM my_table;

/*
 age | name | salary
-----+------+--------
  43 | mike |  43000
  41 | john |  81000
*/
