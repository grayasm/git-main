/*  Cap.8   Data Types
    8.5     Date/Time Types

    psql -d mytestdb -U pgmihai
    \i   05.1_date_time_input.sql
    \?
    \qecho '\033[2J'
*/


/*
  Name           Storage Size  Description          Low value   High value   Resolution
----------------+------------+--------------------+-----------+------------+----------
timestamp [(p)]      8 bytes   both date and time   4713 BC     294276 AD    1 microsecond
[without time zone]            (no time zone)                                  / 14 digits

timestamp [(p)]      8 bytes   both date and time   4713 BC     294276 AD    1 microsecond
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
/* For this data type we do something different:
   locate postgresql.conf , in data directory, open the file and set these:
   timezone="Europe/Berlin"
   log_timezone="Europe/Berlin"
   save and restart the service:
   systemctl restart postgresql.service

   or, set it in psql console with:
   SET timezone = 'Europe/Berlin';
*/
SELECT Now();
/*
              now
-------------------------------
 2019-01-06 13:24:32.295273+01           <-- The timezone is +01
(1 row)
*/

INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-24  02:30:30'),                       -- unchanged
-- 2018 Sun, 25 Mar, 02:00 CET->CEST +1h (DST start)   UTC+2h
       ('2018-03-25  02:30:30'),                       -- Hour+1, TZ+2, mad!!!
       ('2018-03-25  02:30:30+01'),                    -- Hour+1, TZ+1
       ('2018-03-25  02:30:30-02');                    -- Hour+4, TZ+4

SELECT * FROM tstampwtz;
/*
 id |         tswtz
----+------------------------
  1 | 2018-03-24 02:30:30+01
  2 | 2018-03-25 03:30:30+02
  3 | 2018-03-25 03:30:30+02
  4 | 2018-03-25 06:30:30+02
(4 rows)
*/


-- timestamp with time zone
/* Now we test with timezone set to 'GMT':
   open postgresql.conf and set these:
   timezone='GMT'
   log_timezone='GMT'
   save and restart the service:
   systemctl restart postgresql.service

   or, set it in psql console with:
   SET timezone = 'GMT';
*/
SELECT Now();
/*
              now
-------------------------------
 2019-01-06 12:42:02.810395+00            <-- The timezone is +00  (UTC)
(1 row)
*/
DELETE FROM tstampwtz;
INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-24  02:30:30'),                       -- unchanged
-- 2018 Sun, 25 Mar, 02:00 CET->CEST +1h (DST start)   UTC+2h
       ('2018-03-25  02:30:30'),                       -- unchanged
       ('2018-03-25  02:30:30+01'),                    -- Hour-1, TZ-1
       ('2018-03-25  02:30:30-02');                    -- Hour+2, TZ+2

SELECT * FROM tstampwtz;

/*
 id |         tswtz
----+------------------------
  5 | 2018-03-24 02:30:30+00
  6 | 2018-03-25 02:30:30+00
  7 | 2018-03-25 01:30:30+00
  8 | 2018-03-25 04:30:30+00
(4 rows)
*/


-- date
/* To test the date type we do the following:
   locate postgresql.conf , in data directory, open the file and set these:
   datestyle='iso, mdy'
   save and restart the service:
   systemctl restart postgresql.service

   DateStyle takes 2 values:
       1st) the default date/time output, e.g. ISO outputs YYYY-MM-DD
       2nd) the interpretation of ambiguous input, e.g. input is one of MDY forms

   Possible values are:
   ISO: ISO8601 style dates and times (YYYY-MM-DD HH:MM:SS). This is default.
   SQL: use Oracle/Ingres-style. This option is a historical accident.
   PostgreSQL: use the traditional PostgreSQL format.
   German: use DD.MM.YYYY
   European: use DD/MM/YYYY
   NonEuropean, US: use MM/DD/YYYY
*/
SHOW DateStyle;
/*
 DateStyle
-----------
 ISO, MDY
(1 row)
*/


INSERT INTO date0 (date_) VALUES
       ('1999-01-08'), -- ISO 8601; January 8 in any mode (recommended format)
  ('January 8, 1999'), -- unambiguous in any datestyle input mode
         ('1/8/1999'), -- January 8 in MDY mode; August 1 in DMY mode
        ('1/18/1999'), -- January 18 in MDY mode; rejected in other modes
         ('01/02/03'), -- January 2, 2003 in MDY mode
       ('1999-Jan-8'), -- January 8 in any mode
      ('Jan-08-1999'), -- January 8 in any mode
      ('08-Jan-1999'), -- January 8 in any mode
--      ('99-Jan-08'), -- January 8 in YMD mode, else error
        ('08-Jan-99'), -- January 8, except error in YMD mode
        ('Jan-08-99'), -- January 8 , except error in YMD mode
         ('19990108'), -- January 8, 1999 in any mode, ISO 8601
           ('990108'), -- January 8, 1999 in any mode, ISO 8601
         ('1999.008'), -- year and day or year
         ('J2451187'), -- Julian date
 ('January 8, 99 BC'); -- year 99 BC

SELECT * FROM date0;
/*
 id |     date_
----+---------------
  1 | 1999-01-08
  2 | 1999-01-08
  3 | 1999-01-08
  4 | 1999-01-18
  5 | 2003-01-02
  6 | 1999-01-08
  7 | 1999-01-08
  8 | 1999-01-08
  9 | 1999-01-08
 10 | 1999-01-08
 11 | 1999-01-08
 12 | 1999-01-08
 13 | 1999-01-08
 14 | 1999-01-08
 15 | 0099-01-08 BC
(15 rows)
*/


-- time without time zone
INSERT INTO timewotz (twotz) VALUES
       ('04:05:06.789'),             -- ISO 8601, ok
       ('04:05:06'),                 -- ISO 8601, ok
       ('04:05'),                    -- ISO 8601, ok
       ('040506'),                   -- ISO 8601, ok
       ('04:05 AM'),                 -- same as 04:05; AM does not affect value
       ('04:05 PM'),                 -- same as 16:05; input hour must be <= 12
-- not ok --
       ('04:05:06 PST'),             -- PST is ignored
       ('04:05:06.789+02'),          -- TZ is ignored
       ('1999-01-08 04:05:06');      -- The date is ignored

SELECT * FROM timewotz;
/*
 id |    twotz
----+--------------
  1 | 04:05:06.789
  2 | 04:05:06
  3 | 04:05:00
  4 | 04:05:06
  5 | 04:05:00
  6 | 16:05:00
  7 | 04:05:06
  8 | 04:05:06.789
  9 | 04:05:06
(9 rows)
*/


-- time with time zone
INSERT INTO timewtz (twtz) VALUES
       ('04:05:06.789-8'),  -- ISO 8601 offset for PST
       ('04:05:06-08:00'),  -- ISO 8601 offset for PST
       ('04:05-08:00'),     -- ISO 8601 offset for PST
       ('040506-08'),       -- ISO 8601
       ('04:05:06 PST'),    -- time zone specified by abbreviation
       ('2003-04-12 04:05:06 America/New_York'); -- TZ specified by full name

SELECT * FROM timewtz;
/*
 id |      twtz
----+-----------------
  1 | 04:05:06.789-08
  2 | 04:05:06-08
  3 | 04:05:00-08
  4 | 04:05:06-08
  5 | 04:05:06-08
  6 | 04:05:06-04
(6 rows)
*/


-- interval
/* see: http://www.postgresqltutorial.com/postgresql-interval/
   To test we need to have a look at interval input and output format.
   To set the output format, set IntervalStyle= in postgresql.conf

   locate postgresql.conf        # as root
   emacs /var/lib/pgsql/data/postgresql.conf

   intervalstyle = 'postgres'

   Possible values are:
   sql_standard    : +6-5 +4 +3:02:01
   postgres        : 6 years 5 mons 4 days 03:02:01
   postgres_verbose: @ 6 years 5 mons 4 days 3 hours 2 mins 1 sec
   iso_8601        : P6Y5M4DT3H2M1S
*/

-- input examples:
SELECT interval '2 months ago';
/*
 interval
----------
 P-2M
(1 row)
*/

SELECT interval '2 hours 20 minutes';
/*
 interval
----------
 PT2H20M
(1 row)
*/


SELECT Now();
/*
              now
-------------------------------
 2019-01-06 15:31:38.015682+00
(1 row)
*/

SELECT Now() - interval '1 year 3 hours 20 minutes' AS "3 hours 20 minutes ago of last year";
/*
 3 hours 20 minutes ago of last year
-------------------------------------
 2018-01-06 12:11:38.015824+00
(1 row)
*/


-- output examples:
SET intervalstyle = 'sql_standard';
SELECT interval '6 years 5 months 4 days 3 hours 2 minutes 1 second';
/*
     interval
------------------
 +6-5 +4 +3:02:01
(1 row)
*/

SET intervalstyle = 'postgres';
SELECT interval '6 years 5 months 4 days 3 hours 2 minutes 1 second';
/*
            interval
--------------------------------
 6 years 5 mons 4 days 03:02:01
(1 row)
*/

SET intervalstyle = 'postgres_verbose';
SELECT interval '6 years 5 months 4 days 3 hours 2 minutes 1 second';
/*
                   interval
----------------------------------------------
 @ 6 years 5 mons 4 days 3 hours 2 mins 1 sec
(1 row)
*/

SET intervalstyle = 'iso_8601';
SELECT interval '6 years 5 months 4 days 3 hours 2 minutes 1 second';
/*
    interval
----------------
 P6Y5M4DT3H2M1S
(1 row)
*/


-- interval operators
SET intervalstyle = 'postgres';
SELECT interval '2h 50m' + interval '10m'; -- 03:00:00
SELECT interval '2h 50m' - interval '50m'; -- 02:00:00
SELECT 600 * interval '1 minute';          -- 10:00:00

-- convert interval to string
SELECT TO_CHAR(interval '17h 20m 05s', 'HH24:MI:SS'); -- 17:20:05

-- extracting data from a postgresql interval
SELECT EXTRACT(MINUTE FROM interval '5 hours 21 minutes'); -- 21

-- adjusting interval values
SELECT justify_days(interval '30 days');   -- 1 mon
SELECT justify_hours(interval '24 hours'); -- 1 day
SELECT justify_interval(interval '1 year -1 hour'); -- 11 mons 29 days 23:00:00
