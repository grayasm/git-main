/*  Chapter 4.2 Value Expressions
    4.2.3 Subscripts

    Run with:
    psql -d mytestdb -U pgmihai
    \i 4.2.03_subscripts.sql
    \?
    \qecho '\033[2J'
*/


/*  subscripts are of the form:
            expressions[subscript]
            expressions[lower_subscript:upper_subscript]

    mytable.arraycolumn[4]
    mytable.two_d_column[17][34]
    $1[10:42]
    (arrayfunction(a,b))[42]
*/

DROP TABLE IF EXISTS bigt CASCADE;  -- drop table and dependencies

CREATE TABLE bigt (Int1  int,
                   Int2  int[2],
                   IntN  int[],
                   IntT2 int[][],
                   IntT3 int[][][]);

INSERT INTO bigt VALUES (10,
                         '{1, 2}',
                         '{1, 2, 3}',
                         '{{1, 2, 3}, {4, 5, 6}}',
                         '{{{1, 2}}, {{3, 4}}, {{5, 6}}}');


SELECT * FROM bigt WHERE IntN[1] != IntN[2];

/*
 int1 | int2  |  intn   |       intt2       |           intt3
------+-------+---------+-------------------+---------------------------
   10 | {1,2} | {1,2,3} | {{1,2,3},{4,5,6}} | {{{1,2}},{{3,4}},{{5,6}}}
*/
