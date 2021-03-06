/*  Cap.7   Queries
    7.7     VALUES lists

    psql -d mytestdb -U pgmihai
    \i   7.0_values_lists.sql
    \?
    \qecho '\033[2J'
*/


/*      VALUES provides a way to generate a "constant table" that can be used
        in a query without having to actually create and populate a table
        on-disk.  The syntax is:

        VALUES ( expression [, ...] ) [, ...]
*/


SELECT * FROM (VALUES (1, 'one'),(2, 'two'),(3, 'three')) AS t(num,letter);
/*
 num | letter
-----+--------
   1 | one
   2 | two
   3 | three
(3 rows)
*/
