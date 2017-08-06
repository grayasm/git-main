/*  Chapter 4.1 Lexical Structure
    4.1.5 Comments

    run with:
    psql -d mytestdb -U pgmihai         # give password
    \dt                                 # list all tables
    \i 05_comments.sql                  # run this script
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
