/*  Chapter 4.2 Value Expressions
    4.2.2 Positional Parameters

    Run with:
    psql -d mytestdb -U pgmihai
    \i 08_positional_parameters.sql
    \?
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS users CASCADE; -- CASCADE will drop the function too.
CREATE TABLE users (name varchar, email varchar);
INSERT INTO users VALUES ('li yuan', 'li@email.ch');
INSERT INTO users VALUES ('troy',    't@me.com');


-- $number
-- is a positional parameter used in functions and prepared queries; ex:

CREATE FUNCTION get_users(user_name varchar, email_addr varchar)
    RETURNS SETOF users AS
    $BODY$
        SELECT *
        FROM users
        WHERE
            name = $1 AND email = $2
    $BODY$
    LANGUAGE sql VOLATILE
    COST 100
    ROWS 1000;



SELECT * from get_users('troy', 't@me.com');
