/*  Cap.8   Data Types
    8.5     Date/Time Types

    psql -d mytestdb -U pgmihai
    \i 08_date_time_input.sql
*/


/*
  Name           Storage Size  Description          Low value   High value   Resolution
----------------+------------+--------------------+-----------+------------+----------
timestamp [(p)]      8 bytes   both date and time   4713 BC     294276 AD    1 microsecond
[without time zone]            (no time zone)                                  / 14 digits

timestamp [(p]       8 bytes   both date and time   4713 BC     294276 AD    1 microsecond
with time zone                 with time zone                                  / 14 digits


date                 4 bytes   date                 4713 BC     5874897 AD   1 day
                               (no time of day)

time [(p)]
[without time zone]  8 bytes   time of day          00:00:00    24:00:00     1 microsecond
                               (no date)                                       / 14 digits

time [(p)]
with time zone      12 bytes   times of day only,   00:00:00+1459            1 microsecond
                               with time zone                 24:00:00-1459    / 14 digits


interval [fields]   16 bytes   time interval      -178000000    178000000    1 microsecond
[(p)]                                              years        years          / 14 digits
*/

DROP TABLE IF EXISTS tstampwotz CASCADE;
DROP TABLE IF EXISTS tstampwtz  CASCADE;
DROP TABLE IF EXISTS date0      CASCADE;
DROP TABLE IF EXISTS timewotz   CASCADE;
DROP TABLE IF EXISTS timewtz    CASCADE;
DROP TABLE IF EXISTS interv0    CASCADE;

CREATE TABLE tstampwotz (id SERIAL, tswotz timestamp without time zone);
CREATE TABLE tstampwtz  (id SERIAL, tswtz  timestamp with time zone);
CREATE TABLE date0      (id SERIAL, date_  date);
CREATE TABLE timewotz   (id SERIAL, twotz  time without time zone);
CREATE TABLE timewtz    (id SERIAL, twtz   time with time zone);
CREATE TABLE interv0    (id SERIAL, interv interval);


-- timestamp without time zone
INSERT INTO tstampwotz (tswotz) VALUES
       ('1999-01-08 04:05:06'),           -- 04:05:06, no time zone OK
       ('1999-01-08 04:05:06 -8:00'),     -- 04:05:06, -8:00 is discarded !!
       ('January  8 04:05:06 1999 PST');  -- 04:05:06, PST is discarded   !!

SELECT * FROM tstampwotz;
/*
 id |       tswotz
----+---------------------
  1 | 1999-01-08 04:05:06
  2 | 1999-01-08 04:05:06
  3 | 1999-01-08 04:05:06
(3 rows)
*/


-- timestamp with time zone
INSERT INTO tstampwtz (tswtz) VALUES
       (TIMESTAMP WITH TIME ZONE '2004-10-19 10:23:54+02'),
       ('2005-10-19 10:23:54');
