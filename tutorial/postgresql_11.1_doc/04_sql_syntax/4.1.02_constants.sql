/*  Chapter 4.1 Lexical Structure
    4.1.2 Constants

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.1.02_constants.sql
    \?
    \qecho '\033[2J'
*/


-- String Constants are bounded by single quotes (')
DROP TABLE IF EXISTS my_table;
CREATE TABLE my_table (item varchar(80));
INSERT INTO my_table VALUES ('This is a string');  -- normal
INSERT INTO my_table VALUES ('Dianne''s horse');   -- single quote inside string
INSERT INTO my_table VALUES ('foo'
                             'bar');  -- two string constants concatenated
/*
       item
------------------
 This is a string
 Dianne's horse
 foobar
*/


-- String Contstants with C-style Escapes (extension to SQL)

/*  ex: \b (backspace)
        \f (form feed)
        \n (new line)
        \r (carriage return)
        \t (tab)
        \0, \00, \000 (0 = 0-7) (octal byte value)
        \xh, \xhh (h=0-9, A-F)  (hexadecimal byte value)
        \uxxxx, \Uxxxxxxxx (x=0-9, A-F)  (16 or 32-bit hexadecimal Unicode char)
*/
DELETE FROM my_table;
INSERT INTO my_table VALUES (E'\u0041\u006C\u0069\u006E\u0061 is \64\61');  -- escaped unicode and octal chars
INSERT INTO my_table VALUES (E'on \x30\x34\\\x30\x39\\\x31\x38 she will be 42'); -- escaped hexadecimal chars 
INSERT INTO my_table VALUES (E'she\'s what I\'m'); -- escape single quote, alternative to ''
/*
            item
----------------------------
 Alina is 41
 on 04\09\18 she will be 42
 she's what I'm
*/


-- String Constants with Unicode Escapes  (see: https://unicode-table.com/en)

DELETE FROM my_table;
INSERT INTO my_table VALUES (U&'european: \0041\0042\0043'); -- A,B,C
INSERT INTO my_table VALUES (u&'greek   : \0391\0394\03A9'); -- alpha,delta,omega
INSERT INTO my_table VALUES (U&'Cyrillic: !0424!0425!0426' UESCAPE '!'); -- Ef,Ha,Tse
/*
     item
---------------
 european: ABC
 greek   : ΑΔΩ
 Cyrillic: ФХЦ
*/


-- Dollar-quoted String Constants (extension to SQL)

DELETE FROM my_table;
INSERT INTO my_table VALUES ($TAG0$Dianne's horse's luck$TAG0$);
INSERT INTO my_table VALUES ($$Nothing\n\tto\n\t\tdeclare$$);
/*
            item
----------------------------
 Dianne's horse's luck
 Nothing\n\tto\n\t\tdeclare
*/


-- Bit-string Constants  (start with B or b and only 0 and 1 are allowed)

DELETE FROM my_table;
INSERT INTO my_table VALUES (b'00011111');
/*
            item
----------------------------
 00011111
*/


-- Numeric Constants

/*  ex: digits
        digits.[digits][e[+-]digits]
        [digits].digits[e[+-]digits]
        digitse[+-]digits

        with digits between 0 and 9.
*/
DROP TABLE my_table;
CREATE TABLE my_table (cint int, cfloat REAL);
INSERT INTO my_table VALUES (42, 3.5e+2);
/*
 cint | cfloat
------+--------
   42 |    350
*/


-- Constants of Other Types

/*  casting a string constant to another type with:
    type 'string'
    'string'::type
    CAST ( 'string' AS type )
*/
DELETE FROM my_table;
INSERT INTO my_table VALUES (int '29', REAL '3.9e+2');
INSERT INTO my_table VALUES ('28'::int, '3.8e-2'::REAL);
INSERT INTO my_table VALUES (CAST('27' AS int), CAST('-3.7e+2' AS REAL));
/*
 cint | cfloat
------+--------
   29 |    390
   28 |  0.038
   27 |   -370
*/

-- clean up, if not needed
DROP TABLE my_table;
