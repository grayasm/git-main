/*  Cap.2 The SQL Language,
    2.8 Updates

    psql -d mytestdb -U pgmihai
    \i   8_update.sql
    \?
    \qecho '\033[2J'
*/


/*  Suppose you discover the temperature readings are all off by 2 degrees
    after November 28. You can correct the data as follows:
*/
UPDATE weather
       SET temp_hi = temp_hi - 2, temp_lo = temp_lo - 2
       WHERE date > '1994-11-28';

/*
     city      | temp_lo | temp_hi | prcp |    date
---------------+---------+---------+------+------------
 San Francisco |      46 |      50 | 0.25 | 1994-11-27
 San Francisco |      41 |      55 |    0 | 1994-11-29
 Hayward       |      35 |      52 |      | 1994-11-29
*/
