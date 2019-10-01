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
    string || non-string        String with non-string concatenation
    non-string || string        (same)
    bit_length(s)               Number of bits in string s
    char_length(s)              Number of characters in string s
    character_length(s)         Number of characters in string s
    lower(s)                    Convert string s to lower case
    octet_length(s)             Number of bytes in string s
    overlay(s1 placing s2 from x [for y]):
                                Remove in s1 from x, y characters and insert s2
    position(s2 in s1)          Location of s2 in s1 ('om' in 'Thomas' = 3)
    substring(s from x for y)   Extract substring from s at x having y length
    substring(s from pattern)   Extract substring matching POSIX regexp
    substring(s from pattern for escape):
                                Extract substring matching SQL regexp
    trim(leading | trailing | both characters from s):
                                Remove the longest string containing only
                                characters from the start | end | both ends of s
                                trim(both 'xyz' from 'yxTomxx') = Tom
    trim(leading | trailing | both from s, characters):
                                Trim non-standard syntax
                                trim(both from 'yxTomxx', 'xyz') = Tom
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

    Function              Description
    --------------------+-----------
    ascii(s)              ASCII code of the first character
    btrim(s, chars)       Remove chars from s at both ends
    chr(int)              ASCII character with the given code
    concat(s1,i1,..,sn)   Concatenate all arguments as 1 string 'abc',2='abc2'
    concat_ws(sep,s1,i1,..,sn):
                          Concatenate all s1,i1,etc arguments with a (sep)arator
                          ';',abc',22 = 'abc;22'

    convert(s, encoding1,encoding2):
                          Convert s from encoding1 into encoding2
    convert_from(s, encoding1):
                          Convert s from encoding1 into database encoding
    convert_to(s, encoding1):
                          Convert s from database encoding to encoding1

    decode(s, encode)     Convert s to binary encode format (base64,etc)
    encode(data, encode)  Encode data to string using encode (base64,hex,escape)
    format(fmt, ...)      Format a string similar to C sprintf
    initcap(s)            Converts to Camel Case 'hi THOMAS' = 'Hi Thomas'
    left(s, n)            Return first n characters in s 'abcde',2='ab'
    length(s)             Numer of characters in s 'jose'=4
    length(s, encoding1)  Numer of characters in s in the given encoding1 (UTF8)
    lpad(s, len, fill)    Fill up the s to length len by prepending fill.
    ltrim(s, chars)       Remove any chars from the start of s
    md5(s)                Return the MD5 hash of s
    parse_ident(s, bool)  Split s into an array of identifiers
                          '"SomeXMLSchema".someTable' = {SomeSchema,sometable}
    pg_client_encoding()  Return current client encoding name (SQL_ASCII)
    quote_ident(s)        Return s suitably quoted as an identifier for a query
    quote_literal(s)      Return s suitably quoted as a string literal for a query
    quote_nullable(s)     Return s suitably quoted as a string literal for a
                          query. If s is null it returns NULL.
    quote_nullable(v)     Return value as string literal 42.5 = '42.5' or NULL
                          if v is null.

    regexp_match(s, pattern, flags):
                          Return captured substring(s) resulting from the first
                          match fo a POSIX regular expression to s.
                          'foobarbequebaz','(bar)(beque)' = {bar,beque}

    regexp_matches(s, pattern, flags):
                          Similar as above, but it can return multiple rows.
                          'foobarbequebaz','ba.','g'={bar} {baz} (2 rows)

    regexp_replace(s, pattern, replacem, flags):
                          Replace substring(s) matching a POSIX regular expression.
                          'Thomas','.[mN]a.','M' = ThM

    regexp_split_to_array(s, pattern, flags):
                          Split s using a POSIX regular expression as the delimiter.
                          'hello world', '\s+' = {hello,world}

    regexp_split_to_table(s, pattern, flags):
                          Split s using a POSIX regular expression as the delimiter.
                          'hello world', '\s+' = hello world (2 rows)

    repeat(s, n)          Repeat s the specified n number of times
    replace(s, from, to)  Replace all occcurences in s of substring from with to
    reverse(s)            Return reversed s
    right(s, n)           Return the last n characters in s
    rpad(s, len, fill)    Fill up the s to length len by appending fill.
    rtrim(s, chars)       Remove any chars from the end of s

    split_part(s, delimiter, field):
                          Split s on delimiter and return the given field.
    strpos(s, s1)         Location of s1 in s  'high','ig' = 2
    substr(s, from, n)    Extract a substring from s: 'alphabet',3,s = ph
    starts_with(s,prefix) Returns true if s starts with prefix 'alpha','alp'=t
    to_ascii(s, encoding1):
                          Convert s from encoding1 to ASCII. Only supports
                          conversion from LATIN1,LATIN2,LATIN9,WIN1250

    to_hex(n)             Convert number n to hex 2147483647=7fffffff
    translate(s, from, to):
                          Any character in s that matches any in from is
                          replaced by corresponding in to. If from is longer as
                          to the matched character is removed from s.
                          '12345','143','ax' = a2x5
*/

