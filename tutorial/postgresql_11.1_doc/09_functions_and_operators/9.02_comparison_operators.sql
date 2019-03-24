/*  Cap.9   Functions and Operators
    9.2     Comparison Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.02_comparison_operators.sql
    \?
    \qecho '\033[2J'
*/

/*      Check the 3 cathegories here:
        1. Operators
        2. Predicates
        3. Functions
*/


/*      The usual comparison operators are available, as shown in Table 9.1
        Operator   Description
        ---------+------------------------
        <          less than
        >          greater than
        <=         less than or equal to
        >=         greater than or equal to
        =          equal
        <> or !=   not equal

        The != operator is converted to <> in the parser stage. It is not
        possible to implement != and <> operators that do different things.

        NULL = NULL is false. Use IS DINSTINCT (see below).
*/

DROP TABLE IF EXISTS comp_op_t CASCADE;

CREATE TABLE comp_op_t (a FLOAT(24));

INSERT INTO comp_op_t VALUES (1.000),
                             (2.002),
                             (3.003),
                             (4.004),
                             (5.005),
                             (NULL),
                             (6.006),
                             (7.007),
                             (8.008),
                             (9.009),
                             (10.00);

/*          FLOAT numbers are equal in tolerance.
            We start by showing what kind of values are stored in the table.
*/
SELECT a + 10 AS a_10 FROM comp_op_t;
/*

       a_10
------------------
               11
 12.0020000934601
 13.0030000209808
 14.0040001869202
 15.0050001144409

 16.0060000419617
 17.0069999694824
 18.0080003738403
 19.0089998245239
               20
(11 rows)
*/


SELECT a FROM comp_op_t WHERE a <= 5.005;
/*
   a
-------
     1
 2.002
 3.003
 4.004
(4 rows)      <-- where is 5.005 ?????
*/

SELECT a FROM comp_op_t WHERE a <> 5.005;
/*
   a
-------
     1
 2.002
 3.003
 4.004
 5.005        <-- why is 5.005 here ?????
 6.006
 7.007
 8.008
 9.009
    10
(10 rows)
*/

/*      Comparison Predicates
        Predicate                           Description
        ----------------------------------+-------------------------------------
        a BETWEEN x AND y                   between [x, y]
        a NOT BETWEEN x AND y               not between, e.g. outside [x, y]
        a BETWEEN SYMMETRIC x AND y         between, after soring the comparison values
        a NOT BETWEEN SYMMETRIC x AND y     not between, after sorting the comparison values
        a IS DISTINCT FROM b                not equal, treating null like ordinary value
        a IS NOT DISTINCT FROM b            equal, treating null like ordinary value
        expression IS NULL                  is null
        expression IS NOT NULL              is not null
        expression ISNULL                   is null (nonstandard syntax)
        expression NOTNULL                  is not null (nonstandard syntax)
        boolean_expression IS TRUE          is true
        boolean_expression IS NOT TRUE      is false or unknown
        boolean_expression IS FALSE         is false
        boolean_expression IS NOT FALSE     is true or unknown
        boolean_expression IS UNKNOWN       is unknown
        boolean_expression IS NOT UNKNOWN   is true or false

        Where expressions can be any of SELECT,INSERT,UPDATE,DELETE.
*/


/*      a BETWEEN x AND y */
SELECT a FROM comp_op_t WHERE a BETWEEN 8.008 AND 10.00;
/*
   a
-------
 8.008
 9.009
    10
(3 rows)
*/

/*      a NOT BETWEEN x AND y */
SELECT a FROM comp_op_t WHERE a NOT BETWEEN 3.003 AND 8.008;
/*
   a
-------
     1
 2.002
 8.008      <-- why is it included????
 9.009
    10
(5 rows)
*/


/*      a BETWEEN SYMMETRIC x AND y */
SELECT a FROM comp_op_t WHERE a BETWEEN SYMMETRIC 4.004 AND 6.006;
/*
   a
-------
 4.004
 5.005
(2 rows)    <-- where is 6.006 ????
*/

/*      a NOT BETWEEN SYMMETRIC x AND y */
SELECT a FROM comp_op_t WHERE a NOT BETWEEN SYMMETRIC 2.002 AND 8.008;
/*
   a
-------
     1
 8.008      <-- why is it included????
 9.009
    10
(4 rows)
*/


/*      a IS DISTINCT FROM b */
SELECT a FROM comp_op_t WHERE a IS DISTINCT FROM NULL;
/*
   a
-------
     1
 2.002
 3.003
 4.004
 5.005
 6.006
 7.007
 8.008
 9.009
    10
(10 rows)
*/


/*      a IS NOT DISTINCT FROM b */
SELECT a FROM comp_op_t WHERE a IS NOT DISTINCT FROM NULL;
/*
 a
---
            <-- there is a NULL here :)
(1 row)
*/

--NULL is not "equal to" NULL !!!!
SELECT a FROM comp_op_t WHERE a = NULL;
/*
 a
---
(0 rows)
*/


/*      expression IS NULL */
SELECT a_10 FROM (SELECT a, a+10 AS a_10 FROM comp_op_t) AS b WHERE a_10 IS NULL;
/*
 a_10
------

(1 row)
*/


/*      expression IS NOT NULL */
SELECT a_10 FROM (SELECT a, a+10 AS a_10 FROM comp_op_t) AS b WHERE a_10 IS NOT NULL;
/*
       a_10
------------------
               11
 12.0020000934601
 13.0030000209808
 14.0040001869202
 15.0050001144409
 16.0060000419617
 17.0069999694824
 18.0080003738403
 19.0089998245239
               20
(10 rows)
*/


/*      expression ISNULL */
SELECT a_10 FROM (SELECT a + 10 FROM comp_op_t) AS a_10 WHERE a_10 ISNULL;
/*
 a_10
------
 ()
(1 row)
*/

/*      expression NOTNULL */
SELECT a_10 FROM (SELECT a + 10 FROM comp_op_t) AS a_10 WHERE a_10 NOTNULL;
/*
        a_10
--------------------
 (11)
 (12.0020000934601)
 (13.0030000209808)
 (14.0040001869202)
 (15.0050001144409)
 (16.0060000419617)
 (17.0069999694824)
 (18.0080003738403)
 (19.0089998245239)
 (20)
(10 rows)
*/

/*      boolean_expression IS TRUE */
SELECT a, b FROM
       (SELECT a, (a<3 OR a>8)::BOOLEAN AS b FROM comp_op_t) AS c
       WHERE b IS TRUE;
/*
   a   | b
-------+---
     1 | t
 2.002 | t
 8.008 | t
 9.009 | t
    10 | t
(5 rows)
*/

/*      boolean_expression IS NOT TRUE */
SELECT a, b FROM
       (SELECT a, (a<5 OR a>6)::BOOLEAN as b FROM comp_op_t) AS c
       WHERE b IS NOT TRUE;
/*
   a   | b
-------+---
 5.005 | f
       |
(2 rows)
*/


/*      boolean_expression IS FALSE */
SELECT a, b FROM
       (SELECT a, (a<5 OR a>6)::BOOLEAN as b FROM comp_op_t) AS c
       WHERE b IS FALSE;
/*
   a   | b
-------+---
 5.005 | f
(1 row)
*/


/*      boolean_expression IS NOT FALSE */
SELECT a, b FROM
       (SELECT a, (a<2 OR a>9)::BOOLEAN as b FROM comp_op_t) AS c
       WHERE b IS NOT FALSE;
/*
   a   | b
-------+---
     1 | t
       |
 9.009 | t
    10 | t
(4 rows)
*/


/*      boolean_expression IS UNKNOWN */
SELECT a, b FROM
       (SELECT a, (a<2 OR a>9)::BOOLEAN as b FROM comp_op_t) AS c
       WHERE b IS UNKNOWN;
/*
 a | b
---+---
   |
(1 row)
*/


/*      boolean_expression IS NOT UNKNOWN */
SELECT a, b FROM
       (SELECT a, (a<2 OR a>9)::BOOLEAN as b FROM comp_op_t) AS c
       WHERE b IS NOT UNKNOWN;
/*
   a   | b
-------+---
     1 | t
 2.002 | f
 3.003 | f
 4.004 | f
 5.005 | f
 6.006 | f
 7.007 | f
 8.008 | f
 9.009 | t
    10 | t
(10 rows)
*/


/*      Comparison Functions
        Function                        Description
        ------------------------------+-----------------------------------------
        num_nonnulls(VARIADIC "any")    returns the number of non-null arguments
        num_nulls(VARIADIC "any")       returns the number of null arguments
        ------------------------------------------------------------------------
*/
SELECT a, num_nonnulls(a) FROM comp_op_t;
/*
   a   | num_nonnulls
-------+--------------
     1 |            1
 2.002 |            1
 3.003 |            1
 4.004 |            1
 5.005 |            1
       |            0
 6.006 |            1
 7.007 |            1
 8.008 |            1
 9.009 |            1
    10 |            1
(11 rows)
*/

SELECT a, num_nulls(a) FROM comp_op_t;
/*
   a   | num_nulls
-------+-----------
     1 |         0
 2.002 |         0
 3.003 |         0
 4.004 |         0
 5.005 |         0
       |         1
 6.006 |         0
 7.007 |         0
 8.008 |         0
 9.009 |         0
    10 |         0
(11 rows)
*/
