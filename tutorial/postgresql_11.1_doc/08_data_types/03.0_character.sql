/*  Cap.8   Data Types
    8.3     Character Types

    psql -d mytestdb -U pgmihai
    \i   03.0_character.sql
    \?
    \qecho '\033[2J'
*/


/*
        Name                  Alias          Description
    ----------------------+--------------+----------------------------------
    character varying(n)     varchar(n)      variable-length with limit
    character(n)             char(n)         fixed-length, blank padded
    text                                     variable unlimited length
    ------------------------------------------------------------------------

    varchar(n) can store strings up to n characters (not bytes) in length.
    If bigger, string is truncated to n only for blank spaces, otherwise error.
    If shorter, string is padded with type character of blank spaces.
    If varchar is used without (n), the type accepts strings of any size.
    If varchar(n) is explicitly casted to char(n), truncation does not error out.

    char(n) will padd with spaces to the specified witdh n.
    Padded spaces will have an influence only in collations. See the example.
    char without (n) will store 1 character.

    text type stores strings of any length.
    -------------------------------------------------------------------------
    The blank-padded types will use increased storage, and a few extra CPU
    cyles to check the length when storing into a length-constrained column.
    In PostgreSQL character(n) performs slower than text or character varying.

    The storage for strings up to 126 bytes is actual string + 1 byte padding.
    The storage for strings > then 126 bytes is actual string + 4 bytes padding.
    Long strings are compressed by the database to take less disk space.
    Very long values are stored in background tables so that they do not
    interfere with rapid access to shorter column values.
    The longest possible character string that can be stored is about 1GB.
    The maximum value for n is less than 1GB, because of multibyte encodings.
*/

SELECT 'a'::CHAR(2) collate "C" < 'a\n'::CHAR(2); -- returns true

DROP TABLE IF EXISTS test1 CASCADE;
CREATE TABLE test1 (a character(4));
INSERT INTO test1 VALUES ('ok');
INSERT INTO test1 VALUES ('not ok');
-- ERROR:  value too long for type character(4)
SELECT a, char_length(a) FROM test1;

/*
  a   | char_length
------+-------------
 ok   |           2
(1 row)
*/

DROP TABLE IF EXISTS test2 CASCADE;
CREATE TABLE test2 (b varchar(5));
INSERT INTO test2 VALUES ('ok');
INSERT INTO test2 VALUES ('good      ');
INSERT INTO test2 VALUES ('too long');
-- ERROR:  value too long for type character varying(5)
INSERT INTO test2 VALUES ('too long'::varchar(5)); -- explicit truncation
SELECT b, char_length(b) FROM test2;

/*
   b   | char_length
-------+-------------
 ok    |           2
 good  |           5
 too l |           5
(3 rows)
*/
