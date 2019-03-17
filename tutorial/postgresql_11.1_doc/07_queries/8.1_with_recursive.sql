/*  Cap.7   Queries
    7.8.1   SELECT in WITH
            WITH RECURSIVE

    psql -d mytestdb -U pgmihai
    \i 7.08.1_with_recursive.sql
    \?
    \qecho '\033[2J'
*/

/*      http://www.postgresqltutorial.com/postgresql-recursive-query
        The syntax of a recursive CTE (Common Table Expression) is:

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


/*      A helpful trick for testing queries when you are not certain if they
        might loop is to place a LIMIT in the parent query.
        For example, this query would loop forever without the LIMIT :
*/
WITH RECURSIVE t(n) AS (
     SELECT 1
     UNION ALL
     SELECT n+1 FROM t
     )
     SELECT n FROM t LIMIT 3;
/*
 n
---
 1
 2
 3
(3 rows)
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



/*      https://www.fusionbox.com/blog/detail/graph-algorithms-in-a-database-recursive-ctes-and-topological-sort-with-postgres/620/

        Topological sort of a generic graph in SQL
        The example is a general directed graph, where each task vertex may
        have links to any number of other task vertices.

        (6)--->(5)--->(1)
                |\     |
                | \    |
                |  \   |
                v   v  v
        (3)--->(7)--> (2)
                 \     |
                  \    |
                   \   v
                    v (4)
*/
DROP TABLE IF EXISTS edges CASCADE;
CREATE TABLE edges (start_id INT, end_id INT);
INSERT INTO edges VALUES (6, 5),
                         (1, 2),
                         (5, 1),
                         (3, 7),
                         (5, 7),
                         (7, 2),
                         (7, 4),
                         (2, 4);

/*      This sort assumes there are no cycles (impossible to topologically sort
        the graph). It uses the edges rather than the nodes.
        SELECT DISTINCT avoids following the same path at the same depth twice.
        MAX(depth) gives the rank of a node, ASC from left to right.
*/
WITH RECURSIVE traverse(id, depth) AS (
     SELECT edges.start_id, 0
            FROM edges LEFT OUTER JOIN edges AS e2 ON edges.start_id = e2.end_id
            WHERE e2.end_id IS NULL
     UNION ALL
     SELECT DISTINCT edges.end_id, traverse.depth + 1
            FROM traverse INNER JOIN edges ON edges.start_id = traverse.id
     )
     SELECT id FROM traverse
     GROUP BY id
     ORDER BY MAX(depth);
/*
 id
----
  3
  6
  5
  7
  1
  2
  4
(7 rows)
*/



/*      The final step to topologically sorting a generic graph in SQL
        is cycle detection. The only way is to use Postgres's Array data type
        so that each row stores the full path taken to a vertex. That way we
        can terminate the path when we encounter a vertex that's already in our
        path history (which means we've found a cycle). We use a special column
        to set a cycle flag so that we'll know at the end that we hit a cycle
        somewhere.
*/
WITH RECURSIVE traverse(id, path, cycle) AS (
     SELECT edges.start_id, ARRAY[edges.start_id], false
            FROM edges LEFT OUTER JOIN edges AS e2 ON edges.start_id = e2.end_id
            WHERE e2.end_id IS NULL
     UNION ALL
     SELECT DISTINCT edges.end_id,
                     traverse.path || edges.end_id,
                     edges.end_id = ANY(traverse.path)
            FROM traverse INNER JOIN edges ON edges.start_id = traverse.id
            WHERE NOT cycle
     )
     SELECT traverse.id
     FROM traverse LEFT OUTER JOIN traverse AS any_cycles ON any_cycles.cycle = true
     WHERE any_cycles.cycle IS NULL
     GROUP BY traverse.id
     ORDER BY MAX(array_length(traverse.path, 1));
/*
 id
----
  6
  3
  5
  1
  7
  2
  4
(7 rows)
*/
