/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause
    7.2.1.2 The Table and Column Aliases

    psql -d mytestdb -U pgmihai
    \i 04_from_alias.sql
*/


/*      A table 'alias'
        > is a temporary name (shortcut) of a table or a complex table reference
        > is valid only in the query where it is defined
        > the name it replaces cannot be used in the query afterwards
        
        FROM table_reference [AS] alias
*/

DROP TABLE IF EXISTS some_very_long_table_name, another_fairly_long_name CASCADE;
CREATE TABLE some_very_long_table_name (id integer, name text);
CREATE TABLE another_fairly_long_name (num integer, value text);

INSERT INTO some_very_long_table_name VALUES (1,'a'), (2,'b'), (3,'c');
INSERT INTO another_fairly_long_name VALUES (1,'x'), (3,'y'), (5,'z');

SELECT * FROM some_very_long_table_name AS a JOIN
              another_fairly_long_name AS b
              ON a.id = b.num;
/*
 id | name | num | value 
----+------+-----+-------
  1 | a    |   1 | x
  3 | c    |   3 | y
(2 rows)
*/

SELECT * FROM some_very_long_table_name AS mother JOIN
              some_very_long_table_name AS child
              ON mother.id = child.id;
/*
 id | name | id | name 
----+------+----+------
  1 | a    |  1 | a
  2 | b    |  2 | b
  3 | c    |  3 | c
(3 rows)
*/

SELECT * FROM some_very_long_table_name AS a (id_, name_) JOIN
              another_fairly_long_name AS b(id_, value_)
              ON a.id_ = b.id_;
/*
 id_ | name_ | id_ | value_ 
-----+-------+-----+--------
   1 | a     |   1 | x
   3 | c     |   3 | y
(2 rows)
*/

SELECT a.* FROM some_very_long_table_name AS a JOIN
                another_fairly_long_name AS b
                ON a.id = b.num;
/*
 id | name 
----+------
  1 | a
  3 | c
(2 rows)
*/


SELECT c.* FROM (some_very_long_table_name AS a JOIN
                 another_fairly_long_name AS b
                 ON a.id = b.num)
                 AS c;
/*
 id | name | num | value 
----+------+-----+-------
  1 | a    |   1 | x
  3 | c    |   3 | y
(2 rows)
*/
