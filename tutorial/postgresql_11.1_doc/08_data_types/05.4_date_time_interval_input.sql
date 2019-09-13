/*  Cap.8   Data Types
    8.5     Date/Time Types
    8.5.4   Interval Input

    psql -d mytestdb -U pgmihai
    \i   05.4_date_time_interval_intput.sql
    \?
    \qecho '\033[2J'
*/


/*  interval can be written using the following syntax:
    [@] quantity unit [qunatity unit...] [direction]
     P  quantity unit [quantity unit...] [T [quantity unit...]]

    Abbreviation    Meaning
    Y               Years
    M               Months (after P and before T)
    W               Weeks
    D               Days
    H               Hours
    M               Minutes (after T)
    S               Seconds
*/

DROP TABLE IF EXISTS intervalt CASCADE;
CREATE TABLE intervalt (id SERIAL, interv interval);
INSERT INTO intervalt (interv) VALUES
       ('@ 1 year 2 months 3 days 4 hours 5 minutes 6.12345 seconds'), --PostgreSQL
       ('@ 1-2 3 4:05:06.12345'),                                      --SQL
       ('P1Y2M3DT4H5M6.12345S'),                                       --ISO8601
       ('P0001-02-03T04:05:06.12345');                                 --ISO8601

SELECT * FROM intervalt;
/*
 id |               interv
----+-------------------------------------
  1 | 1 year 2 mons 3 days 04:05:06.12345
  2 | 1 year 2 mons 3 days 04:05:06.12345
  3 | 1 year 2 mons 3 days 04:05:06.12345
  4 | 1 year 2 mons 3 days 04:05:06.12345
(4 rows)
*/
