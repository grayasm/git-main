/*  Cap.7   Queries
    7.3     Select Lists
    7.3.3   DISTINCT

    psql -d mytestdb -U pgmihai
    \i 13_distinct.sql
*/


/*      http://www.postgresqltutorial.com/postgresql-select-distinct/

        The DISTINCT clause is used in the SELECT statement to remove duplicate
        rows from the result set. The DISTINCT clause keeps one row for each
        group of duplicates. The DISTINCT clause can be used on one or more
        columns of a table. */

DROP TABLE IF EXISTS t1 CASCADE;
CREATE TABLE t1 (id         SERIAL NOT NULL PRIMARY KEY,
                 bcolor     VARCHAR,
                 fcolor     VARCHAR);

INSERT INTO t1 (bcolor, fcolor) VALUES  ('red', 'red'),
                                        ('red', 'red'),
                                        ('red', NULL),
                                        (NULL, 'red'),
                                        ('red', 'green'),
                                        ('red', 'blue'),
                                        ('green', 'red'),
                                        ('green', 'blue'),
                                        ('green', 'green'),
                                        ('blue', 'red'),
                                        ('blue', 'green'),
                                        ('blue', 'blue');


-- DISTINCT on one column
SELECT DISTINCT bcolor FROM t1 ORDER BY bcolor;
/*
 bcolor 
--------
 blue
 green
 red
 
(4 rows)
*/

--DISTINCT on multiple columns
SELECT DISTINCT bcolor,fcolor FROM t1 ORDER BY bcolor,fcolor;
/*
 bcolor | fcolor 
--------+--------
 blue   | blue
 blue   | green
 blue   | red
 green  | blue
 green  | green
 green  | red
 red    | blue
 red    | green
 red    | red
 red    | 
        | red
(11 rows)
*/

-- DISTINCT ON ... ORDER BY ..., for each group of duplicates keeps the first row.
SELECT DISTINCT ON(bcolor) bcolor, fcolor FROM t1 ORDER BY bcolor,fcolor;
/*
 bcolor | fcolor 
--------+--------
 blue   | blue
 green  | blue
 red    | blue
        | red
(4 rows)
*/
