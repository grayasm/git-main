/*  Chapter 4.2 Value Expressions
    4.2.6 Function Calls

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.2.06_function_calls.sql
    \?
    \dt  --list tables
    \df  --list functions
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS users CASCADE;
CREATE TABLE users (name varchar, email varchar, address varchar);
INSERT INTO users VALUES ('tom', 'tom@me.net', '610 Harriongton, Glenmont, OH');
INSERT INTO users VALUES ('jim', 'jim@me.net', '2-26 Brickel, Columbus, OH');

CREATE FUNCTION get_users (uname varchar)
       RETURNS users AS
       $$
           SELECT *
           FROM users
           WHERE name = uname
       $$
       LANGUAGE sql;


SELECT get_users('tom');

/*
                    get_users
--------------------------------------------------
 (tom,tom@me.net,"610 Harriongton, Glenmont, OH")
*/
