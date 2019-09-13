/*  Cap.8   Data Types
    8.11.   Text Search Types
    8.11.2  tsquery

    psql -d mytestdb -U pgmihai
    \i   11.2_text_search_tsquery.sql
    \?
    \qecho '\033[2J'
*/


/*      A tsquery values stores lexemes that are to be searched for, and can
        combine them using the Boolean operators AND,OR,NOT: & | ! as well as
        the phrase search operator <-> (FOLLOWED BY). There is also a variant
        <N> of the FOLLOWED BY operator, where N is an integer constant that
        specifies the distance between the 2 lexemes being search for.
        <-> is equivalent to <1>
*/

SELECT 'fat & rat'::tsquery;
/*
    tsquery
---------------
 'fat' & 'rat'
(1 row)
*/

SELECT 'fat & (rat | cat)'::tsquery;
/*
          tsquery
---------------------------
 'fat' & ( 'rat' | 'cat' )
(1 row)
*/

SELECT 'fat & rat & ! cat'::tsquery;
/*
        tsquery
------------------------
 'fat' & 'rat' & !'cat'
(1 row)
*/

SELECT 'fat:ab & cat'::tsquery;
/*
     tsquery
------------------
 'fat':AB & 'cat'
(1 row)
*/

SELECT 'super:*'::tsquery;
/*
  tsquery
-----------
 'super':*
(1 row)
*/

SELECT to_tsquery('Fat:ab & Cats');
/*
    to_tsquery
------------------
 'fat':AB & 'cat'
(1 row)
*/

SELECT to_tsvector('postgraduate') @@ to_tsquery('postgres:*');
/*
 ?column?
----------
 t
(1 row)
*/

SELECT to_tsvector('postgraduate'), to_tsquery('postgres:*');
/*
  to_tsvector  | to_tsquery
---------------+------------
 'postgradu':1 | 'postgr':*
(1 row)
*/
