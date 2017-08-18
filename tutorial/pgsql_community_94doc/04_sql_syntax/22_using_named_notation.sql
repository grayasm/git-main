/*  Chapter 4.3. Calling Functions
	4.3.1. Using Named Notation
	
	psql -d mytestdb -U pgmihai
	\dt  --list all tables
	\df  --list all functions
	\i 22_using_named_notation.sql
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
		SELECT	CASE
				WHEN $3 THEN upper($1 || ' ' || $2)
				ELSE LOWER ($1 || ' ' || $2)
				END;
	$$
	LANGUAGE SQL;


--	This is normal function call. I added it for visibility.
SELECT concat_lower_or_upper(c1, c2, c3) FROM my_table;
/*
   concat_lower_or_upper
---------------------------
 0A LOWERCASE 0B LOWERCASE
 1a camelcase 1b camelcase
 2a uppercase 2b uppercase
*/


/*	In Named Notation, each argument's name is specified using := to separate it
	from the argument expression. Example:
*/
SELECT	concat_lower_or_upper (a := c1, b := c2, uppercase := c3)
		FROM my_table;
/*
   concat_lower_or_upper
---------------------------
 0A LOWERCASE 0B LOWERCASE
 1a camelcase 1b camelcase
 2a uppercase 2b uppercase
*/


/*	In Named Notation one advantage is that the arguments may be specified
	in any order. Example:
*/
SELECT	concat_lower_or_upper (uppercase := c3, b := c2, a := c1)
		FROM my_table;
/*
   concat_lower_or_upper
---------------------------
 0A LOWERCASE 0B LOWERCASE
 1a camelcase 1b camelcase
 2a uppercase 2b uppercase
*/
