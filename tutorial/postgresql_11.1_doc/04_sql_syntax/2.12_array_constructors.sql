/*  Chapter 4.2. Value Expressions
    4.2.12. Array Constructors

    psql -d mytestdb -U pgmihai
    \i   2.12_array_constructors.sql
    \?
    \qecho '\033[2J'
*/


--  ARRAY[expression [, expression ..] ]
SELECT ARRAY [1, 2, 3 + 4];

/*
  array
---------
 {1,2,7}
*/


--  ARRAY constructor with the desired type;
SELECT ARRAY [1, 2, 22.7]::integer[];

/*
  array
----------
 {1,2,23}
*/


--  Multidimensional array with nesting array constructors. Inner ARRAY omitted.
SELECT ARRAY [ ARRAY [1, 2], ARRAY [3, 4] ];
SELECT ARRAY [[1, 2] , [3, 4]];

/*
     array
---------------
 {{1,2},{3,4}}
*/


/*  Since multidimensional array must be rectangular, inner constructors at the
    same level must produce sub-arrays of identical dimensions.
    Any cast applied to the outer ARRAY constructor propagates automatically to
    all the inner constructors.
    Multidimensional ARRAY constructors elements can be anything yielding an
    array of the proper kind, not only a sub-ARRAY construct. Example:
*/
DROP TABLE IF EXISTS arr CASCADE;

CREATE TABLE arr(f1 int[], f2 int[]);

INSERT INTO arr VALUES (ARRAY[[1,2], [3,4]], ARRAY[[5,6], [7,8]]);

SELECT ARRAY[f1, f2, '{{80,90},{110,120}}'::int[]] FROM arr;

/*
                       array
---------------------------------------------------
 {{{1,2},{3,4}},{{5,6},{7,8}},{{80,90},{110,120}}}
*/


/*  It's impossible to have an ARRAY with no type. You must explicitly cast
    an empty ARRAY to the desired type. Example:
*/
SELECT ARRAY[]::integer[];

/*
 array
-------
 {}
*/
