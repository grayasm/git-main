/*  Cap.8   Data Types
    8.5     Date/Time Types
    8.5.5   Interval Output

    psql -d mytestdb -U pgmihai
    \i 12_date_time_interval_output.sql
    \?
    \qecho '\033[2J'
*/


/*  See also 08_date_int_intput.sql
    We can set the interval output format in 2 ways:
    (1)
    locate postgresql.conf   # as root
    emacs /var/lib/pgsql/data/postgresql.conf

    intervalstyle = 'postgres'
    (2)
    SET IntervalStyle = 'postgres'

    Possible values are:
    sql_standard    : +6-5 +4 +3:02:01
    postgres        : 6 years 5 mons 4 days 03:02:01
    postgres_verbose: @ 6 years 5 mons 4 days 3 hours 2 mins 1 sec
    iso_8601        : P6Y5M4DT3H2M1S

    To see the current value type:
    SHOW IntervalStyle;
*/

DROP TABLE IF EXISTS intervalt CASCADE;
CREATE TABLE intervalt (id SERIAL, interv interval);
INSERT INTO intervalt (interv) VALUES
       ('@ 1 year 2 months 3 days 4 hours 5 minutes 6.12345 seconds'), --PostgreSQL
       ('@ 1-2 3 4:05:06.12345'),                                      --SQL
       ('P1Y2M3DT4H5M6.12345S'),                                       --ISO8601
       ('P0001-02-03T04:05:06.12345');                                 --ISO8601

SET IntervalStyle = 'sql_standard';
SELECT * FROM intervalt;
/*
 id |         interv
----+------------------------
  1 | +1-2 +3 +4:05:06.12345
  2 | +1-2 +3 +4:05:06.12345
  3 | +1-2 +3 +4:05:06.12345
  4 | +1-2 +3 +4:05:06.12345
(4 rows)
*/

SET IntervalStyle = 'postgres';
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

SET IntervalStyle = 'postgres_verbose';
SELECT * FROM intervalt;
/*
 id |                       interv
----+----------------------------------------------------
  1 | @ 1 year 2 mons 3 days 4 hours 5 mins 6.12345 secs
  2 | @ 1 year 2 mons 3 days 4 hours 5 mins 6.12345 secs
  3 | @ 1 year 2 mons 3 days 4 hours 5 mins 6.12345 secs
  4 | @ 1 year 2 mons 3 days 4 hours 5 mins 6.12345 secs
(4 rows)
*/

SET IntervalStyle = 'iso_8601';
SELECT * FROM intervalt;
/*
 id |        interv
----+----------------------
  1 | P1Y2M3DT4H5M6.12345S
  2 | P1Y2M3DT4H5M6.12345S
  3 | P1Y2M3DT4H5M6.12345S
  4 | P1Y2M3DT4H5M6.12345S
(4 rows)
*/
