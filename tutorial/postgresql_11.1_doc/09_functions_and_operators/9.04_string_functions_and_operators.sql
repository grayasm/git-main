/*  Cap.9   Functions and Operators
    9.4     String Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.04_string_functions_and_operators.sql
    \?
    \qecho '\033[2J'
*/


/*  The following functions and operators work on types:
    character, character varying and text.

    1. SQL String Functions and Operators
    2. Other String Functions
    3. Built-in Conversions
    4. The function 'format'
*/


/*  SQL String Functions and Operators

    Function                  Description
    ------------------------+--------------------
    string || string          String concatenation
    string || non-string      String concatenation with non-string
    non-string || string      (same)
    bit_length(s)             Number of bits in string
    char_length(s)            Number of characters in string
    character_length(s)       (same)
    lower(s)                  Convert string to lower case
    octet_length(s)           Number of bytes in string
    overlay(s1 placing s2 from x for y): Replace substring
    position(s2 in s1)        Location of specified substring
    substring(s from x for y): Extract substring
    
