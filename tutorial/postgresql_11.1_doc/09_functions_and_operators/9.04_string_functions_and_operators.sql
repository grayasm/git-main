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

    Function                    Description
    --------------------------+--------------------
    string || string            String concatenation
    string || non-string        String concatenation with one non-string input
    non-string || string        String concatenation with one non-string input
    bit_length(s)               Number of bits in string s
    char_length(s)              Number of characters in string s
    character_length(s)         Number of characters in string s
    lower(s)                    Convert string s to lower case
    octet_length(s)             Number of bytes in string s
    overlay(s1 placing s2 from x [for y]):      Replace substring
    position(s2 in s1)          Location of specified substring s2 in s1
    substring(s from x for y)   Extract substring from s at x having y length
    substring(s from pattern)   Extract substring matching POSIX regexp
    substring(s from pattern for escape):  Extract substring matching SQL regexp
    trim(leading | trailing | both characters from s):
                                Remove the longest string containing only
                                characters from the start | end | both ends of s
    trim(leading | trailing | both from s, characters): trim non-standard syntax
    upper(string)               Convert string to upper case
*/

SELECT 'Post' || 'greSQL';  -- PostgreSQL
SELECT 'Value: ' || 42;     -- Value: 42
SELECT bit_length('jose');  -- 32
SELECT char_length('jose'); --  4
SELECT lower('TOM');        -- tom
SELECT octet_length('jose');--  4
SELECT overlay('Txxxxas' placing 'hom' from 2 for 4); -- Thomas
SELECT position('om' in 'Thomas');                    -- 3
SELECT substring('Thomas' from 2 for 3);              -- hom
SELECT substring('Thomas' from '...$');               -- mas
SELECT substring('Thomas' from '%#"o_a#"_' for '#');  -- oma
SELECT trim(both 'xyz' from 'yxTomxx');               -- Tom
SELECT trim(both from 'yxTomxx', 'xyz');              -- Tom
SELECT upper('tom');                                  -- TOM


/*  Other String Functions

    Function   Description
    ----------+-----------
    ascii(s)   ASCII/UNICODE code of the first character of s.
    brtim(s , chars) Trims at both ends of s all characters in chars
    chr(int)   Returns the character with the given ASCII/UNICODE code
    concat(s1, x, s2, y, ..) Concatenate the text representation of the arguments
    concat_ws(sep text, str, 

*/
