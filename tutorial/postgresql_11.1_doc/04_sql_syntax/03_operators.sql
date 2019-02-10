/*  Chapter 4.1 Lexical Structure
    4.1.3 Operators

    https://www.postgresql.org/docs/9.0/static/functions-logical.html

    Run with:
    psql -d mytestdb -U pgmihai
    \i 03_operators.sql
    \?
    \qecho '\033[2J'
*/


-- Logical Operators:  AND, OR, NOT

DROP TABLE IF EXISTS my_table;
CREATE TABLE my_table (a boolean, b boolean);
INSERT INTO my_table VALUES (TRUE,  TRUE);
INSERT INTO my_table VALUES (TRUE,  FALSE);
INSERT INTO my_table VALUES (TRUE,  NULL);
INSERT INTO my_table VALUES (FALSE, FALSE);
INSERT INTO my_table VALUES (FALSE, NULL);
INSERT INTO my_table VALUES (NULL,  NULL);

SELECT a AND b AS a_AND_b,
       a OR  b AS a_OR_b,
         NOT a AS NOT_a
       FROM my_table;
/*
 a_and_b | a_or_b | not_a
---------+--------+-------
 t       | t      | f
 f       | t      | f
         | t      | f
 f       | f      | t
 f       |        | t
         |        |
*/



/*  Comparison Operators:
      <, >, <=, >=, =, <>, !=
      BETWEEN, NOT BETWEEN, IS NULL, IS NOT NULL, ISNULL, NOTNULL
      IS DISTINCT FROM, IS NOT DISTINCT FROM,
      IS TRUE, IS NOT TRUE, IS FALSE, IS NOT FALSE, IS UNKNONW, IS NOT UNKNOWN
*/

DROP TABLE my_table;
CREATE TABLE my_table (IntVal1 int, IntVal2 int);
INSERT INTO my_table VALUES (10,  3);
INSERT INTO my_table VALUES ( 4, 11);

SELECT * FROM my_table WHERE IntVal1 < IntVal2;               --  4 | 11
SELECT * FROM my_table WHERE IntVal1 >= IntVal2;              -- 10 | 3
SELECT * FROM my_table WHERE IntVal1 != IntVal2;              -- 10 | 3, 4 | 11
SELECT * FROM my_table WHERE IntVal1 BETWEEN 3 AND 5;         --  4 | 11
SELECT * FROM my_table WHERE (IntVal1 = IntVal2) IS NOT TRUE; -- 10 | 3, 4 | 11


/*  Mathematical Operators
    Operator     Description            Example     Result
    +            addition
    -            subtraction
    *            multiplication
    /            division
    %            modulo                 5 % 4       1
    ^            exponent               2 ^ 3       8
    |/           square root            |/ 25       5
    ||/          cube root              ||/ 27      3
    !            factorial              5!          120
    !!           factorial (prefixed)   !! 5        120
    @            absolute value         @ -5        5
    &            bitwise AND            91 & 15     11
    |            bitwise OR             32 | 3      35
    #            bitwise XOR            17 # 5      20
    ~            bitwise NOT            ~ 1         -2
    <<           bitwise shift left     1 << 4      16
    >>           bitwise shift right    8 >> 2      2
*/
DROP TABLE my_table;
CREATE TABLE my_table (IntVal int);
INSERT INTO my_table VALUES (0);
UPDATE my_table SET IntVal =  5 ^ 3;                 -- 125
UPDATE my_table SET IntVal =  |/ 25;                 -- 5
UPDATE my_table SET IntVal = @ -1234;                -- 1234
UPDATE my_table SET Intval = 91 & 15;                -- 11
