/*  Chapter 4.2 Value Expressions
    4.2.5 Operator Invocations

    run sample with:
    psql -d mytestdb -U pgmihai
    \dt  --list tables
    \df  --list functions
    \i 11_operator_invocations.sql
*/


-- expression operator expression  ; binary infix operator
--            operator expression  ; unary prefix operator
-- expression operator             ; unary postfix operator

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (val1 int, val2 int);
INSERT INTO  my_table VALUES (10, 3);
INSERT INTO  my_table VALUES (11, 4);

SELECT val1,  val2,
       val1 = val2 AS equal,
       !!(val2)    AS factorial,    -- !! factorial, prefix notation
       (val2)!     AS factorial2    -- !  factorial, postfix notation
       FROM my_table;


/*
 val1 | val2 | equal | factorial | factorial2
------+------+-------+-----------+------------
   10 |    3 | f     |         6 |          6
   11 |    4 | f     |        24 |         24
*/
