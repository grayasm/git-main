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

SELECT ascii('x'); --120
SELECT btrim('xyztrimyyx', 'xyz'); --trim
SELECT chr(65); -- A
SELECT concat('abcde', 2, NULL, 22); -- abcde222
SELECT concat_ws(',', 'abcde', 2, NULL, 22); --abcde,2,22
SELECT convert('text_in_utf8', 'UTF8', 'LATIN1'); -- \x746578745f696e5f75746638
SELECT convert_from('text_in_utf8', 'UTF8'); -- text_in_utf8
SELECT convert_to('some_text', 'UTF8'); -- \x736f6d655f74657874
SELECT decode('MTIzAAE=', 'base64'); -- \x3132330001
SELECT encode('123\000\001', 'base64'); -- MTIzAAE=
SELECT format('Hello %s, %1$s', 'World'); -- Hello World, World
SELECT initcap('hi THOMAS'); -- Hi Thomas
SELECT left('abcde', 2); -- ab
SELECT length('jose'); -- 4
SELECT length('jose', 'UTF8'); -- 4
SELECT lpad('hi', 5, 'xy'); -- xyxhi
SELECT ltrim('zzzytest', 'xyz'); --
SELECT md5('abc'); -- 900150983cd24fb0d6963f7d28e17f72
SELECT parse_ident('"SomeSchema".someTable'); -- {SomeSchema,sometable}
SELECT pg_client_encoding(); -- UTF8
SELECT quote_ident('Foo bar'); -- "Foo bar"
SELECT quote_literal(E'O\'Reilly'); -- 'O''Reilly'                  fix emacs'
SELECT quote_literal(42.5); -- '42.5'
SELECT quote_nullable(NULL); -- NULL
SELECT quote_nullable(42.5); -- '42.5'
SELECT regexp_match('foobarbequebaz', '(bar)(beque)'); -- {bar,beque}
SELECT regexp_matches('foobarbequebaz', 'ba.', 'g'); -- {bar} {baz} (2 rows)
SELECT regexp_replace('Thomas', '.[mN]a.', 'M'); -- ThM
SELECT regexp_split_to_array('hello world', '\s+'); -- {hello,world}
SELECT regexp_split_to_table('hello world', '\s+'); -- hello world (2 rows)
SELECT repeat('Pg', 4); -- PgPgPgPg
SELECT replace('abcdefabcdef', 'cd', 'XX'); -- abXXefabXXef
SELECT reverse('abcde'); -- edcba
SELECT right('abcde', 2); -- de
SELECT rpad('hi', 5, 'xy'); -- hixyx
SELECT rtrim('testxxzx', 'xyz'); -- test
SELECT split_part('abc~@~def~@~ghi', '~@~', 2); -- def
SELECT strpos('high', 'ig'); -- 2
SELECT substr('alphabet', 3, 2); -- ph
SELECT starts_with('alphabet', 'alph'); -- t   (aka true)
-- SELECT to_ascii('Karel'); error: encoding conversion from UTF8 to ASCII
--                                  not supported
SELECT to_hex(2147483647); -- 7fffffff
SELECT translate('12345', '143', 'ax'); -- a2x5


/*  Built-in Conversions
    My note: these methods are may accessible from 'C', as there is no match
             for any of these in SQL.

    Conversion Name     Source Encoding  Destination Encoding
    --------------------+---------------+---------------------
    ascii_to_mic          SQL_ASCII       MULE_INTERNAL
    ascii_to_utf8         SQL_ASCII       UTF8
    big5_to_euc_tw        BIG5            EUC_TW
    big5_to_mic           BIG5            MULE_INTERNAL
    big5_to_utf8          BIG5            UTF8
    euc_cn_to_mic         EUC_CN          MULE_INTERNAL
    euc_cn_to_utf8        EUC_CN          UTF8
    euc_jp_to_mic         EUC_JP          MULE_INTERNAL
    euc_jp_to_sjis        EUC_JP          SJIS
    euc_jp_to_utf8        EUC_JP          UTF8
    euc_kr_to_mic         EUC_KR          MULE_INTERNAL
    euc_kr_to_utf8        EUC_KR          UTF8
    euc_tw_to_big5        EUC_TW          BIG5
    euc_tw_to_mic         EUC_TW          MULE_INTERNAL
    euc_tw_to_utf8        EUC_TW          UTF8
    gb18030_to_utf8       GB18030         UTF8
    gbk_to_utf8           GBK             UTF8
    iso_8859_10_to_utf8   LATIN6          UTF8
    iso_8859_13_to_utf8   LATIN7          UTF8
    iso_8859_14_to_utf8   LATIN8          UTF8
    iso_8859_15_to_utf8   LATIN9          UTF8
    iso_8859_16_to_utf8   LATIN10         UTF8
    iso_8859_1_to_mic     LATIN1          MULE_INTERNAL
    iso_8859_1_to_utf8    LATIN1          UTF8
    iso_8859_2_to_mic     LATIN2          MULE_INTERNAL
    iso_8859_2_to_utf8    LATIN2          UTF8
    iso_8859_2_to_windows_1250    LATIN2          WIN1250
    iso_8859_3_to_mic     LATIN3          MULE_INTERNAL
    iso_8859_3_to_utf8    LATIN3          UTF8
    iso_8859_4_to_mic     LATIN4          MULE_INTERNAL
    iso_8859_4_to_utf8    LATIN4          UTF8
    iso_8859_5_to_koi8_r  ISO_8859_5      KOI8R
    iso_8859_5_to_mic     ISO_8859_5      MULE_INTERNAL
    iso_8859_5_to_utf8    ISO_8859_5      UTF8
    iso_8859_5_to_windows_1251    ISO_8859_5      WIN1251
    iso_8859_5_to_windows_866     ISO_8859_5      WIN866
    iso_8859_6_to_utf8    ISO_8859_6      UTF8
    iso_8859_7_to_utf8    ISO_8859_7      UTF8
    iso_8859_8_to_utf8    ISO_8859_8      UTF8
    iso_8859_9_to_utf8    LATIN5          UTF8
    johab_to_utf8         JOHAB           UTF8
    koi8_r_to_iso_8859_5  KOI8R           ISO_8859_5
    koi8_r_to_mic         KOI8R           MULE_INTERNAL
    koi8_r_to_utf8        KOI8R           UTF8
    koi8_r_to_windows_1251        KOI8R           WIN1251
    koi8_r_to_windows_866         KOI8R           WIN866
    koi8_u_to_utf8                KOI8U           UTF8
    mic_to_ascii          MULE_INTERNAL   SQL_ASCII
    mic_to_big5           MULE_INTERNAL   BIG5
    mic_to_euc_cn         MULE_INTERNAL   EUC_CN
    mic_to_euc_jp         MULE_INTERNAL   EUC_JP
    mic_to_euc_kr         MULE_INTERNAL   EUC_KR
    mic_to_euc_tw         MULE_INTERNAL   EUC_TW
    mic_to_iso_8859_1     MULE_INTERNAL   LATIN1
    mic_to_iso_8859_2     MULE_INTERNAL   LATIN2
    mic_to_iso_8859_3     MULE_INTERNAL   LATIN3
    mic_to_iso_8859_4     MULE_INTERNAL   LATIN4
    mic_to_iso_8859_5     MULE_INTERNAL   ISO_8859_5
    mic_to_koi8_r         MULE_INTERNAL   KOI8R
    mic_to_sjis           MULE_INTERNAL   SJIS
    mic_to_windows_1250   MULE_INTERNAL   WIN1250
    mic_to_windows_1251   MULE_INTERNAL   WIN1251
    mic_to_windows_866    MULE_INTERNAL   WIN866
    sjis_to_euc_jp        SJIS            EUC_JP
    sjis_to_mic           SJIS            MULE_INTERNAL
    sjis_to_utf8          SJIS            UTF8
    tcvn_to_utf8          WIN1258         UTF8
    uhc_to_utf8           UHC             UTF8
    utf8_to_ascii         UTF8            SQL_ASCII
    utf8_to_big5          UTF8            BIG5
    utf8_to_euc_cn        UTF8            EUC_CN
    utf8_to_euc_jp        UTF8            EUC_JP
    utf8_to_euc_kr        UTF8            EUC_KR
    utf8_to_euc_tw        UTF8            EUC_TW
    utf8_to_gb18030       UTF8            GB18030
    utf8_to_gbk           UTF8            GBK
    utf8_to_iso_8859_1    UTF8            LATIN1
    utf8_to_iso_8859_10   UTF8            LATIN6
    utf8_to_iso_8859_13   UTF8            LATIN7
    utf8_to_iso_8859_14   UTF8            LATIN8
    utf8_to_iso_8859_15   UTF8            LATIN9
    utf8_to_iso_8859_16   UTF8            LATIN10
    utf8_to_iso_8859_2    UTF8            LATIN2
    utf8_to_iso_8859_3    UTF8            LATIN3
    utf8_to_iso_8859_4    UTF8            LATIN4
    utf8_to_iso_8859_5    UTF8            ISO_8859_5
    utf8_to_iso_8859_6    UTF8            ISO_8859_6
    utf8_to_iso_8859_7    UTF8            ISO_8859_7
    utf8_to_iso_8859_8    UTF8            ISO_8859_8
    utf8_to_iso_8859_9    UTF8            LATIN5
    utf8_to_johab         UTF8            JOHAB
    utf8_to_koi8_r        UTF8            KOI8R
    utf8_to_koi8_u        UTF8            KOI8U
    utf8_to_sjis          UTF8            SJIS
    utf8_to_tcvn          UTF8            WIN1258
    utf8_to_uhc           UTF8            UHC
    utf8_to_windows_1250  UTF8            WIN1250
    utf8_to_windows_1251  UTF8            WIN1251
    utf8_to_windows_1252  UTF8            WIN1252
    utf8_to_windows_1253  UTF8            WIN1253
    utf8_to_windows_1254  UTF8            WIN1254
    utf8_to_windows_1255  UTF8            WIN1255
    utf8_to_windows_1256  UTF8            WIN1256
    utf8_to_windows_1257  UTF8            WIN1257
    utf8_to_windows_866   UTF8            WIN866
    utf8_to_windows_874   UTF8            WIN874
    windows_1250_to_iso_8859_2    WIN1250         LATIN2
    windows_1250_to_mic           WIN1250         MULE_INTERNAL
    windows_1250_to_utf8          WIN1250         UTF8
    windows_1251_to_iso_8859_5    WIN1251         ISO_8859_5
    windows_1251_to_koi8_r        WIN1251         KOI8R
    windows_1251_to_mic           WIN1251         MULE_INTERNAL
    windows_1251_to_utf8          WIN1251         UTF8
    windows_1251_to_windows_866   WIN1251         WIN866
    windows_1252_to_utf8          WIN1252         UTF8
    windows_1256_to_utf8          WIN1256         UTF8
    windows_866_to_iso_8859_5     WIN866          ISO_8859_5
    windows_866_to_koi8_r         WIN866          KOI8R
    windows_866_to_mic            WIN866          MULE_INTERNAL
    windows_866_to_utf8           WIN866          UTF8
    windows_866_to_windows_1251   WIN866          WIN
    windows_874_to_utf8           WIN874          UTF8
    euc_jis_2004_to_utf8          EUC_JIS_2004    UTF8
    utf8_to_euc_jis_2004          UTF8            EUC_JIS_2004
    shift_jis_2004_to_utf8        SHIFT_JIS_2004  UTF8
    utf8_to_shift_jis_2004        UTF8            SHIFT_JIS_2004
    euc_jis_2004_to_shift_jis_2004    EUC_JIS_2004      SHIFT_JIS_2004
    shift_jis_2004_to_euc_jis_2004    SHIFT_JIS_2004    EUC_JIS_2004
    --------------------+--------------------+------------------------
*/


/*  The format function
    --------------------
    The function format produces output formatted according to a format string
    in a style similar to the C function sprintf.

    format ( formatstr text [, formatarg "any" [, ...] ] )

    format specifiers: %[position][flags][width]type
*/


-- basic format conversions:
SELECT format('Hello %s', 'World'); -- Hello World
SELECT format('Testing %s, %s, %s, %%', 'one', 'two', 'three');
    -- Testing one, two, three, %

SELECT format('INSERT INTO %I VALUES (%L)', 'Foo bar', E'O\'Reilly');
    -- INSERT INTO "Foo bar" VALUES ('O''Reilly')             fix emacs'

SELECT format('INSERT INTO %I VALUES(%L)', 'locations', 'C:\Program Files');
    -- INSERT INTO locations VALUES(E'C:\\Program Files')


-- examples using the width field and the - flag:
SELECT format('|%10s|', 'foo');      -- |       foo|
SELECT format('|%-10s|', 'foo');     -- |foo       |
SELECT format('|%*s|', 10, 'foo');   -- |       foo|
SELECT format('|%*s|',-10, 'foo');   -- |foo       |
SELECT format('|%-*s|', 10, 'foo');  -- |foo       |
SELECT format('|%-*s|',-10, 'foo');  -- |foo       |


-- examples using the position field:
SELECT format('Testing %3$s, %2$s, %1$s', 'one', 'two', 'three'); -- Testing three, two, one
SELECT format('Testing %3$s, %2$s, %s', 'one', 'two', 'three');   -- Testing three, two, three
SELECT format('|%*2$s|', 'foo', 10, 'bar');  -- |       bar|
SELECT format('|%1$*2$s|', 'foo', 10, 'bar');-- |       foo|
