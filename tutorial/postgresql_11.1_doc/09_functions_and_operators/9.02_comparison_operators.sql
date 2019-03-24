/*  Cap.9   Functions and Operators
    9.2     Comparison Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.02_comparison_operators.sql
    \?
    \qecho '\033[2J'
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
*/

DROP TABLE IF EXISTS comp_op_t CASCADE;
CREATE TABLE comp_op_t (a FLOAT(24));
INSERT INTO comp_op_t VALUES (1.000),
                             (2.002),
                             (3.003),
                             (4.004),
                             (5.005),
                             (6.006),
                             (7.007),
                             (8.008),
                             (9.009),
                             (10.00);

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
        a BETWEEN x AND y                   between [x, y] inclusive
        a NOT BETWEEN x AND y               not between [x, y]
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
*/

SELECT a FROM comp_op_t WHERE a BETWEEN 8.008 AND 10.00;
/*
   a
-------
 8.008
 9.009
    10
(3 rows)
*/

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

SELECT a FROM comp_op_t WHERE a BETWEEN SYMMETRIC 4.004 AND 6.006;
/*
   a
-------
 4.004      <-- why is it included???
 5.005
(2 rows)
*/
