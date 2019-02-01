/*  Chapter 4.2 Value Expressions
    4.2.6 Function Calls

    run sample with:
    psql -d mytestdb -U pgmihai
    \dt  --list tables
    \df  --list functions
    \i 12_function_calls.sql
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
