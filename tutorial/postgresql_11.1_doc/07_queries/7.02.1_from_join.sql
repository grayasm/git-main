/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.1   The FROM Clause
    7.2.1.1 Joined Tables

    psql -d mytestdb -U pgmihai
    \i 7.02.1_from_join.sql
    \?
    \qecho '\033[2J'
*/


/*      The general syntax of a join table is:
        t1 join_type t2 [ join_condition ]

        Join types:
        > t1 CROSS JOIN t2
        > t1 { [INNER] | {LEFT|RIGHT|FULL} [OUTER] } JOIN t2 ON boolean_expr
        > t1 { [INNER] | {LEFT|RIGHT|FULL} [OUTER] } JOIN t2 USING (join column list)
        > t1 NATURAL { [INNER] | {LEFT|RIGHT|FULL} [OUTER] } JOIN t2
*/


DROP TABLE IF EXISTS t1,t2 CASCADE;
CREATE TABLE t1 (num integer, name text);
CREATE TABLE t2 (num integer, value text);
INSERT INTO t1 VALUES (1,'a'), (2,'b'), (3,'c');
INSERT INTO t2 VALUES (1,'x'), (3,'y'), (5,'z');

SELECT * FROM t1 CROSS JOIN t2;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   1 | a    |   3 | y
   1 | a    |   5 | z
   2 | b    |   1 | x
   2 | b    |   3 | y
   2 | b    |   5 | z
   3 | c    |   1 | x
   3 | c    |   3 | y
   3 | c    |   5 | z
(9 rows)
*/

SELECT * FROM t1 INNER JOIN t2 ON t1.num = t2.num;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   3 | c    |   3 | y
(2 rows)
*/

SELECT * FROM t1 INNER JOIN t2 USING (num);
/*
 num | name | value
-----+------+-------
   1 | a    | x
   3 | c    | y
(2 rows)
*/

SELECT * FROM t1 NATURAL INNER JOIN t2;
/*
 num | name | value
-----+------+-------
   1 | a    | x
   3 | c    | y
(2 rows)
*/

SELECT * FROM t1 LEFT JOIN t2 ON t1.num = t2.num;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   2 | b    |     |
   3 | c    |   3 | y
(3 rows)
*/

SELECT * FROM t1 LEFT JOIN t2 USING (num);
/*
 num | name | value
-----+------+-------
   1 | a    | x
   2 | b    |
   3 | c    | y
(3 rows)
*/

SELECT * FROM t1 RIGHT JOIN t2 ON t1.num = t2.num;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   3 | c    |   3 | y
     |      |   5 | z
(3 rows)
*/

SELECT * FROM t1 FULL JOIN t2 ON t1.num = t2.num;
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   2 | b    |     |
   3 | c    |   3 | y
     |      |   5 | z
(4 rows)
*/

SELECT * FROM t1 LEFT JOIN t2 ON t1.num = t2.num AND t2.value = 'x';
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
   2 | b    |     |
   3 | c    |     |
(3 rows)
*/

SELECT * FROM t1 LEFT JOIN t2 ON t1.num = t2.num WHERE t2.value = 'x';
/*
 num | name | num | value
-----+------+-----+-------
   1 | a    |   1 | x
(1 row)
*/
