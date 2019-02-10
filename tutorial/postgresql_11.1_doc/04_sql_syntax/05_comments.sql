/*  Chapter 4.1 Lexical Structure
    4.1.5 Comments

    Run with:
    psql -d mytestdb -U pgmihai
    \i 05_comments.sql
    \?
    \qecho '\033[2J'
*/


-- This is a standard SQL comment
DROP TABLE IF EXISTS my_table;

/*  Multiline comment
 *  with nesting: /* nested block comment */
 */
CREATE TABLE my_table (IntVal1 int);
INSERT INTO my_table VALUES (int '1234');
SELECT * FROM my_table;



-- clean up
DROP TABLE my_table;
