/*  Chapter 4.1 Lexical Structure
    4.1.4 Special Characters

    run:
    psql -d mytestdb -U pgmihai  # give passworld
    \dt                          # to list all tables
    \i 04_special_characters.sql
*/


-- A dollar sign ($) followed by digits is a position parameter in a function
-- Parantheses (()) enforce precedence in group expressions
-- Brackets ([]) are used to select the elements of an array
-- Commas (,) separate the elements of a list
-- The semicolon (;) terminates and SQL command
-- The colon (:) slices and array
-- The asterisk (*) denotes all the fields of a table row
-- The period (.) is used in numeric constants and to separate schema,table and column names
