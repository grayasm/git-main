/*  Cap.2 The SQL Language,
    2.9 Deletions

    Run with:
    psql -d mytestdb -U pgmihai
    \i 08_deletions.sql
    \?
    \qecho '\033[2J'
*/


/*  Suppose you are no longer interested in the weather of Hayward. Then you
    can do the following to delete the rows from the table:
*/
DELETE FROM weather WHERE city = 'Hayward';

/*
     city      | temp_lo | temp_hi | prcp |    date
---------------+---------+---------+------+------------
 San Francisco |      46 |      50 | 0.25 | 1994-11-27
 San Francisco |      41 |      55 |    0 | 1994-11-29
*/


/*  The system will not request confirmation before executing DELETE
*/
