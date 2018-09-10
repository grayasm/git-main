/*  Cap.7   Queries
    7.8.1   SELECT in WITH
            WITH RECURSIVE

    psql -d mytestdb -U pgmihai
    \i 19_with_recursive.sql
*/

/*      http://www.postgresqltutorial.com/postgresql-recursive-query
        The syntax of a recursive CTE is:

        WITH RECURSIVE cte_name (
             CTE_query_definition       -- non-recursive term
             UNION [ALL]
             CTE_query_definition       -- recursive term
             )
             SELECT * FROM cte_name;

        > non-recursive term: the base result set of the CTE structure.
        > recursive term    : one or more CTE queries joined with non-recursive
                              term through UNION or UNION ALL.
                              The recursive term references to the cte_name
        > termination check : the recursion stops when no rows are returned
                              from the previous iteration.
*/


-- query the sum of integers from 1 through 100
WITH RECURSIVE t(n) AS (
     VALUES(1)
     UNION ALL
           SELECT n+1 FROM t WHERE n < 100
     )
     SELECT SUM(n) FROM t;
/*
 sum  
------
 5050
(1 row)
*/


-- return all subordinates (direct or indirect) of the manager with id=2
DROP TABLE IF EXISTS employees CASCADE;
CREATE TABLE employees (employee_id  SERIAL PRIMARY KEY,
                        full_name    VARCHAR(255) NOT NULL,
                        manager_id   INTEGER);

INSERT INTO employees (employee_id, full_name, manager_id) VALUES
                      (1, 'Michael North', NULL),
                      (2, 'Megan Berry', 1),
                      (3, 'Sarah Berry', 1),
                      (4, 'Zoe Black', 1),
                      (5, 'Tim James', 1),
                      (6, 'Bella Tucker', 2),
                      (7, 'Ryan Metcalfe', 2),
                      (8, 'Max Mills', 2),
                      (9, 'Benjamin Glover', 2),
                      (10, 'Carolyn Henderson', 3),
                      (11, 'Nicola Kelly', 3),
                      (12, 'Alexandra Climo', 3),
                      (13, 'Dominic King', 3),
                      (14, 'Leonard Gray', 4),
                      (15, 'Eric Rampling', 4),
                      (16, 'Piers Paige', 7),
                      (17, 'Ryan Henderson', 7),
                      (18, 'Frank Tucker', 8),
                      (19, 'Nathan Ferguson', 8),
                      (20, 'Kevin Rampling', 8);

WITH RECURSIVE subordinates AS (
     SELECT employee_id, manager_id, full_name
            FROM employees
            WHERE employee_id = 2
     UNION
     SELECT e.employee_id, e.manager_id, e.full_name
            FROM employees e
            INNER JOIN subordinates s ON s.employee_id = e.manager_id
     )
     SELECT * FROM subordinates;
/*
 employee_id | manager_id |    full_name    
-------------+------------+-----------------
           2 |          1 | Megan Berry
           6 |          2 | Bella Tucker
           7 |          2 | Ryan Metcalfe
           8 |          2 | Max Mills
           9 |          2 | Benjamin Glover
          16 |          7 | Piers Paige
          17 |          7 | Ryan Henderson
          18 |          8 | Frank Tucker
          19 |          8 | Nathan Ferguson
          20 |          8 | Kevin Rampling
(10 rows)
*/
