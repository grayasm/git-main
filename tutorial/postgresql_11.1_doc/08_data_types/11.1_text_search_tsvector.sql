/*  Cap.8   Data Types
    8.11.   Text Search Types
    8.11.1  tsvector

    psql -d mytestdb -U pgmihai
    \i 8.11.1_text_search_tsvector.sql
    \?
    \qecho '\033[2J'
*/


/*      The tsvector type represents a document in a form optimized for text
        search.
        A tsvector is a sorted list of distinct lexemes, which are words that
        have been normalized to merge different variants of the same word.
        Sorting and duplicate-elimination are done automatically during input.
*/

SELECT 'a fat cat sat on a mat and ate a fat rat'::tsvector;
/*
                      tsvector
----------------------------------------------------
 'a' 'and' 'ate' 'cat' 'fat' 'mat' 'on' 'rat' 'sat'
(1 row)
*/

SELECT $$the lexeme '    ' contains spaces$$::tsvector;
/*
                 tsvector
-------------------------------------------
 '    ' 'contains' 'lexeme' 'spaces' 'the'
(1 row)
*/

SELECT $$the lexeme 'Joe''s' contains a quote$$::tsvector;
/*
                    tsvector
------------------------------------------------
 'Joe''s' 'a' 'contains' 'lexeme' 'quote' 'the'
(1 row)
*/

SELECT 'a:1 fat:2 cat:3 sat:4 on:5 a:6 mat:7 and:8 ate:9 a:10
       fat:11 rat:12'::tsvector;
/*
                                   tsvector
-------------------------------------------------------------------------------
 'a':1,6,10 'and':8 'ate':9 'cat':3 'fat':2,11 'mat':7 'on':5 'rat':12 'sat':4
(1 row)
*/


SELECT 'a:1A fat:2B,4C cat:5D'::tsvector;  -- labeled with a weight
/*
          tsvector
----------------------------
 'a':1A 'cat':5 'fat':2B,4C
(1 row)
*/

SELECT 'The Fat Rats'::tsvector;
/*
      tsvector
--------------------
 'Fat' 'Rats' 'The'
(1 row)
*/


SELECT to_tsvector('english', 'The Fat Rats');
/*
   to_tsvector
-----------------
 'fat':2 'rat':3
(1 row)
*/
