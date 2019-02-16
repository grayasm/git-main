/*  Chapter 4.3. Calling Functions
    4.3.3. Using Mixed Notation

    psql -d mytestdb -U pgmihai
    \i 4.3.3_using_mixed_notation.sql
    \?
    \df
    \qecho '\033[2J'
*/

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (c1 text, c2 text, c3 boolean);
INSERT INTO my_table VALUES ('0a lowercase', '0b lowercase', true),
                            ('1a Camelcase', '1b Camelcase', false),
                            ('2A UPPERCASE', '2B UPPERCASE', false);


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


--  This is normal function call. I added it for visibility.
SELECT concat_lower_or_upper(c1, c2, c3) FROM my_table;
/*
   concat_lower_or_upper
---------------------------
 0A LOWERCASE 0B LOWERCASE
 1a camelcase 1b camelcase
 2a uppercase 2b uppercase
*/


/*  The Mixed Notation combines positional and named notation.
    However, named arguments CANNOT precede positional arguments (logic).
    Example:
*/
SELECT  concat_lower_or_upper (c1, c2, uppercase := true)
        FROM my_table;
/*
   concat_lower_or_upper
---------------------------
 0A LOWERCASE 0B LOWERCASE
 1A CAMELCASE 1B CAMELCASE
 2A UPPERCASE 2B UPPERCASE
*/
