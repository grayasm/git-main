/*  Cap.6   Data Manipulation
    6.4     Returning Data From Modified Rows

    psql -d mytestdb -U pgmihai
    \i   4_returning_data.sql
    \?
    \qecho '\033[2J'
*/

/*      When 2 or more concurent threads/processes/queries change the same rows
        of a table it is no longer possible to know reliably which rows have
        been changed by each query. The RETURNING clause helps in this situation.

        The INSERT,UPDATE and DELETE commands all have an optional RETURNING
        clause that supports this. Use of RETURNING avoids performing an extra
        database query to collect the data, and is especially valuable when it
        would otherwise be difficult to identify the modified rows reliably.
*/

DROP TABLE IF EXISTS users CASCADE;

CREATE TABLE users (
       firstname   TEXT,
       lastname    TEXT,
       age         INTEGER,
       salary      FLOAT,
       id          SERIAL PRIMARY KEY
       );

INSERT INTO users (firstname, lastname, age, salary) VALUES
       ('Joe',       'Cool',    22, 1120.00),
       ('Fannie',    'Kelley',  21, 1110.00),
       ('Rebecca',   'Clarke',  25, 1210.00),
       ('Khadija',   'Johnson', 26, 1280.00),
       ('Chantelle', 'Hoffman', 27, 1380.00)
       RETURNING id;
/*
 id
----
  1
  2
  3
  4
  5
(5 rows)
*/


UPDATE users SET salary = salary * 1.05
       WHERE age < 25
       RETURNING firstname, lastname, age, salary as new_salary;
/*
 firstname | lastname | age | new_salary
-----------+----------+-----+------------
 Joe       | Cool     |  22 |       1176
 Fannie    | Kelley   |  21 |     1165.5
(2 rows)
*/


DELETE FROM users
       WHERE salary > 1300
       RETURNING *;
/*
 firstname | lastname | age | salary | id
-----------+----------+-----+--------+----
 Chantelle | Hoffman  |  27 |   1380 |  5
(1 row)
*/
