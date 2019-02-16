/*  Chapter 4.1 Lexical Structure
    4.1.1 Identifiers and keywords

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.1.1_identifiers_and_keywords.sql
    \?
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS MY_TABLE;
CREATE TABLE MY_TABLE (a int);
INSERT INTO MY_TABLE VALUES (1);
INSERT INTO MY_TABLE VALUES (2);

--key words and unquoted identifiers are case insensitive
UPDATE MY_TABLE SET A = A + 1;  -- normal form
uPDaTE my_TabLE SeT a = a + 2;  -- unusual, but also correct


-- quoted identifiers are case sensitive and can contain any character except \0
DROP TABLE MY_TABLE;
CREATE TABLE MY_TABLE (U&"d \0061 t \+000061" varchar(80)); -- d a t a
INSERT INTO MY_TABLE VALUES ('a string');
SELECT * FROM MY_TABLE;
/*
 d a t a
----------
 a string
*/

-- if a different backslash is desired, it can be specified using UESCAPE clause
DROP TABLE MY_TABLE;
CREATE TABLE MY_TABLE (U&"d!0061t!+000061" UESCAPE '!'  varchar(80)); --data
INSERT INTO MY_TABLE VALUES ('+50.668,+30,448');
SELECT * FROM MY_TABLE;
/*
      data
-----------------
 +50.668,+30,448
*/


-- clean up
DROP TABLE MY_TABLE;
