/*  Chapter 4.2. Value Expressions
    4.2.14. Expression Evaluation Rules

    psql -d mytestdb -U pgmihai
    \dt  --list all tables
    \df  --list all functions
    \i 20_expression_evaluation_rules.sql
*/

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (x float, y float);
INSERT INTO my_table VALUES (1, 5), (1, 6), (1, 7), (0, 8), (0, 9);

/*  1.  The order of evaluation of subexpressions is not defined.
*/
SELECT x, y FROM my_table WHERE x > 0 AND y/x > 1.5;  -- untrustworthy
SELECT x, y FROM my_table WHERE CASE WHEN x > 0 THEN y/x > 1.5 ELSE false END; -- ok


/*  2.  a CASE cannot prevent evaluation of an aggregate expression contained
        within it, because aggregate expressions are compuated before other
        expressions in a SELECT list or HAVING clause.
*/
SELECT  CASE WHEN min(x) > 0
             THEN avg(y / x)
        END
        FROM my_table;
/* psql:19_expression_eval_rules.sql:27: ERROR:  division by zero */
