/*  Cap.8   Data Types
    8.15.   Arrays
    8.15.1  Declaration of Array Types
    8.15.2  Array Value Input
    8.15.3  Accessing Arrays
    8.15.4  Modifying Arrays
    8.15.5  Searching in Arrays
    8.15.6  Array Input and Output Syntax

    psql -d mytestdb -U pgmihai
    \i 8.15_array.sql
    \?
    \qecho '\033[2J'
*/


/*      PostgreSQL allows columns of a table to be defined as variable-length
        multidimensional arrays. Arrays of any built-in or user-defined
        base type, enum type, composite type, range type or domain can be
        created.

        An array data is named by appending brackets [] to the data type.
        An alternative syntax, which conforms to the SQL standard by using
        the keyword ARRAY, can be used for one-dimensional array.

        To write an array value as a literal constant, enclose the element
        values within curly braces and separate them by comas.
        '{ val1, val2, ...}'
        Each val is either a constant of the array element type, or a subarray.
        An example of a two-dimensional, 3-by-3 array:
        '{{1,2,3} , {4,5,6} , {7,8,9}}'

        To access arbitrary rectangular slices of an array, or subarrays use
        lower-bound:upper-bound.
        e.g. schedule[1:2][1:1]
*/

DROP TABLE IF EXISTS sal_emp CASCADE;

CREATE TABLE sal_emp (
    name            TEXT,
    pay_by_quarter  INTEGER[], -- alternative: INTEGER ARRAY[4] or INTEGER ARRAY
    schedule        TEXT[][]   -- alternative: TEXT [10][300]
    );

INSERT INTO sal_emp VALUES
    ('Bill',
     '{10000, 10000, 10000, 10000}',
     '{{"meeting", "lunch"}, {"training", "presentation"}}');

INSERT INTO sal_emp VALUES
    ('Carol',
     '{20000, 25000, 25000, 25000}',
     '{{"breakfast", "consulting"}, {"meeting", "lunch"}}');


/*      Accessing Arrays */
SELECT name FROM sal_emp WHERE pay_by_quarter[1] <> pay_by_quarter[2];
/*
 name
-------
 Carol
(1 row)
*/

SELECT pay_by_quarter[3] FROM sal_emp;
/*
 pay_by_quarter
----------------
          10000
          25000
(2 rows)
*/

SELECT schedule[1:2][1:1] FROM sal_emp WHERE name = 'Bill';
/*
        schedule
------------------------
 {{meeting},{training}}
(1 row)
*/

SELECT schedule[1:2][2] FROM sal_emp WHERE name = 'Bill';
/*
                 schedule
-------------------------------------------
 {{meeting,lunch},{training,presentation}}
(1 row)
*/

SELECT schedule[:2][2:] FROM sal_emp WHERE name = 'Bill';
/*
         schedule
--------------------------
 {{lunch},{presentation}}
(1 row)
*/

SELECT schedule[:][1:1] FROM sal_emp WHERE name = 'Bill';
/*
        schedule
------------------------
 {{meeting},{training}}
(1 row)
*/


SELECT array_dims(schedule) FROM sal_emp WHERE name = 'Bill';
/*
 array_dims
------------
 [1:2][1:2]
(1 row)
*/

SELECT array_upper(schedule, 1) FROM sal_emp WHERE name = 'Carol';
/*
 array_upper
-------------
           2
(1 row)
*/

SELECT array_length(schedule, 1) FROM sal_emp WHERE name = 'Carol';
/*
 array_length
--------------
            2
(1 row)
*/

SELECT cardinality(schedule) FROM sal_emp WHERE name = 'Carol';
/*
 cardinality
-------------
           4
(1 row)
*/


/*      Modify Arrays */
UPDATE sal_emp SET pay_by_quarter = '{25000,25000,27000,27000}'
    WHERE name = 'Carol';

UPDATE sal_emp SET pay_by_quarter = ARRAY[25000,25000,27000,27000]
    WHERE name = 'Carol';

UPDATE sal_emp SET pay_by_quarter[4] = 15000 WHERE name = 'Bill';

UPDATE sal_emp SET pay_by_quarter[1:2] = '{27000,27000}' WHERE name = 'Carol';

-- create a new array by using concatenation operator ||
SELECT ARRAY[1,2] || ARRAY[3,4];
/*
 ?column?
-----------
 {1,2,3,4}
(1 row)
*/

SELECT ARRAY[5,6] || ARRAY[[1,2] , [3,4]];
/*
      ?column?
---------------------
 {{5,6},{1,2},{3,4}}
(1 row)
*/

SELECT array_dims(1 || '[0:1]={2,3}'::int[]);
/*
 array_dims
------------
 [0:2]
(1 row)
*/

SELECT array_dims(ARRAY[1,2] || 3);
/*
 array_dims
------------
 [1:3]
(1 row)
*/


SELECT array_dims(ARRAY[1,2] || ARRAY[3,4,5]);
/*
 array_dims
------------
 [1:5]
(1 row)
*/

SELECT array_dims(ARRAY[[1,2] , [3,4]] || ARRAY[[5,6] , [7,8] , [9,0]]);
/*
 array_dims
------------
 [1:5][1:2]
(1 row)
*/


SELECT array_dims(ARRAY[1,2] || ARRAY[[3,4] , [5,6]]);
/*
 array_dims
------------
 [1:3][1:2]
(1 row)
*/

SELECT array_prepend(1, ARRAY[2,3]);
/*
 array_prepend
---------------
 {1,2,3}
(1 row)
*/

SELECT array_append(ARRAY[1,2], 3);
/*
 array_append
--------------
 {1,2,3}
(1 row)
*/

SELECT array_cat(ARRAY[1,2], ARRAY[3,4]);
/*
 array_cat
-----------
 {1,2,3,4}
(1 row)
*/

SELECT array_cat(ARRAY[[1,2],[3,4]], ARRAY[5,6]);
/*
      array_cat
---------------------
 {{1,2},{3,4},{5,6}}
(1 row)
*/

SELECT array_cat(ARRAY[5,6], ARRAY[[1,2],[3,4]]);
/*
      array_cat
---------------------
 {{5,6},{1,2},{3,4}}
(1 row)
*/

SELECT ARRAY[1, 2] || '{3, 4}';
/*
 ?column?
-----------
 {1,2,3,4}
(1 row)
*/

SELECT ARRAY[1, 2] || '7';
-- ERROR:  malformed array literal: "7"

SELECT ARRAY[1, 2] || NULL;
/*
 ?column?
----------
 {1,2}
(1 row)
*/

SELECT array_append(ARRAY[1, 2], NULL);
/*
 array_append
--------------
 {1,2,NULL}
(1 row)
*/


/*      Searching in Arrays */
SELECT * FROM sal_emp WHERE pay_by_quarter[1] = 10000 OR
                            pay_by_quarter[2] = 10000 OR
                            pay_by_quarter[3] = 10000 OR
                            pay_by_quarter[4] = 10000;
/*
 name |      pay_by_quarter       |                 schedule
------+---------------------------+-------------------------------------------
 Bill | {10000,10000,10000,15000} | {{meeting,lunch},{training,presentation}}
(1 row)
*/

SELECT * FROM sal_emp WHERE 10000 = ANY(pay_by_quarter);
/*
 name |      pay_by_quarter       |                 schedule
------+---------------------------+-------------------------------------------
 Bill | {10000,10000,10000,15000} | {{meeting,lunch},{training,presentation}}
(1 row)
*/

SELECT * FROM
    (SELECT pay_by_quarter,
            generate_subscripts(pay_by_quarter, 1) AS s
     FROM sal_emp) AS foo
WHERE pay_by_quarter[s] = 10000;
/*
      pay_by_quarter       | s
---------------------------+---
 {10000,10000,10000,15000} | 1
 {10000,10000,10000,15000} | 2
 {10000,10000,10000,15000} | 3
(3 rows)
*/

SELECT * FROM sal_emp WHERE pay_by_quarter && ARRAY[10000];
/*
 name |      pay_by_quarter       |                 schedule
------+---------------------------+-------------------------------------------
 Bill | {10000,10000,10000,15000} | {{meeting,lunch},{training,presentation}}
(1 row)
*/

SELECT array_position(ARRAY['sun','mon','tue','wed','thu','fri','sat'], 'mon');
/*
 array_position
----------------
              2
(1 row)
*/

SELECT array_positions(ARRAY[1,4,3,1,3,4,2,1], 1);
/*
 array_positions
-----------------
 {1,4,8}
(1 row)
*/


/*      Array Input and Output Syntax */
SELECT f1[1][-2][3] AS e1, f1[1][-1][5] AS e2
    FROM (
        SELECT '[1:1][-2:-1][3:5]={{{1,2,3},{4,5,6}}}'::int[] as f1)
    AS ss;
/*
 e1 | e2
----+----
  1 |  6
(1 row)
*/
