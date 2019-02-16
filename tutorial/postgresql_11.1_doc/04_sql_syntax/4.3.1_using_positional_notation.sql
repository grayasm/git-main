/*  Chapter 4.3. Calling Functions
    4.3.1. Using Positional Notation

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.3.1_using_positional_notation.sql
    \?
    \df
    \qecho '\033[2J'
*/

DROP FUNCTION IF EXISTS concat_lower_or_upper (a text, b text, uppercase boolean);
CREATE FUNCTION concat_lower_or_upper (a text, b text, uppercase boolean DEFAULT false)
    RETURNS text
    AS
    $$
        SELECT  CASE
                WHEN $3 THEN upper($1 || ' ' || $2)
                ELSE LOWER ($1 || ' ' || $2)
                END;
    $$
    LANGUAGE SQL;


/*  This is the Positional Notation for parameters of a function call;
*/

SELECT concat_lower_or_upper ('Hello', 'World', true);
/*
 concat_lower_or_upper
-----------------------
 HELLO WORLD
*/


/*  This is the Positional Notation with last argument omitted, possible from
    right to left so long as they have defaults;
*/

SELECT concat_lower_or_upper ('Hello', 'World');
/*
 concat_lower_or_upper
-----------------------
 hello world
*/
