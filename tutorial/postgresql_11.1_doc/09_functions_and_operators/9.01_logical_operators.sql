/*  Cap.9   Functions and Operators
    9.1     Logical Operators

    psql -d mytestdb -U pgmihai
    \i   9.01_logical_operators.sql
    \?
    \qecho '\033[2J'
*/

/*      The usual logical operators are available: AND, OR, NOT.
        SQL uses a three-level logic system with: TRUE, FALSE and NULL
        which represents "unknown"
*/

DROP TABLE IF EXISTS logic_op_t CASCADE;

CREATE TABLE logic_op_t (a BOOLEAN, b BOOLEAN);

INSERT INTO logic_op_t VALUES (TRUE,  TRUE),
                              (TRUE,  FALSE),
                              (TRUE,  NULL),
                              (FALSE, FALSE),
                              (FALSE, NULL),
                              (NULL,  NULL);

SELECT a, b,
       a AND b AS a_AND_b,
       a OR  b AS a_OR_b
       FROM logic_op_t;

/*
 a | b | a_and_b | a_or_b
---+---+---------+--------
 t | t | t       | t
 t | f | f       | t
 t |   |         | t
 f | f | f       | f
 f |   | f       |
   |   |         |
(6 rows)
*/

SELECT a, NOT a AS NOT_a FROM logic_op_t;
/*
 a | not_a
---+-------
 t | f
 t | f
 t | f
 f | t
 f | t
   |
(6 rows)
*/
