/*  Cap.8   Data Types
    8.5     Date/Time Types
    8.5.3   Time Zones

    psql -d mytestdb -U pgmihai
    \i 10_date_time_zones.sql
*/

/*  PostgreSQL uses IANA (Olson) timezone database.
    Recommended to be used with "timestamp with time zone" and nothing else.
    Specify the timezone in 3 different ways:
        * full time zone: America/New_York  (all listed in pg_timezone_names)
        * abbreviation  : PST (all listed in pg_timezone_abbrevs)
        * POSIX-style   : STDoffset or STDoffsetDST
*/

DROP TABLE IF EXISTS tstampwtz CASCADE;
CREATE TABLE tstampwtz (id SERIAL, tswtz timestamp with time zone);


-- full timezones
\pset pager off
SELECT * FROM pg_timezone_names;
/*
                  name                  | abbrev | utc_offset | is_dst
----------------------------------------+--------+------------+--------
 CET                                    | CET    | 01:00:00   | f
 Zulu                                   | UTC    | 00:00:00   | f
 Europe/Madrid                          | CET    | 01:00:00   | f
 Europe/Berlin                          | CET    | 01:00:00   | f
 Europe/Bucharest                       | EET    | 02:00:00   | f
 CST6CDT                                | CST    | -06:00:00  | f
 EST5EDT                                | EST    | -05:00:00  | f
 US/Michigan                            | EST    | -05:00:00  | f
 US/Pacific                             | PST    | -08:00:00  | f
 US/Central                             | CST    | -06:00:00  | f
 US/Eastern                             | EST    | -05:00:00  | f
 Pacific/Samoa                          | SST    | -11:00:00  | f
 Pacific/Fiji                           | +12    | 12:00:00   | f
...
*/


SET TimeZone='GMT';
INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-24  02:30:30 Zulu'),
-- 2018 Sun, 25 Mar, 02:00 CET->CEST +1h (DST start)   UTC+2h
       ('2018-03-25  02:30:30 Zulu'),
       ('2018-03-25  02:30:30 Europe/Madrid'),      -- Hour-1, TZ-1
       ('2018-03-10  02:30:30 US/Michigan'),
-- 2018 Sun, 11 Mar, 02:00 EST->DST +1h (DST start)    UTC-05+01=UTC-04
       ('2018-03-11  02:30:30 US/Michigan'),
       ('2018-03-11  03:30:30 US/Michigan'),
       ('2018-03-11  04:30:30 US/Michigan'),
       ('2018-03-11  05:30:30 US/Michigan'),
       ('2018-03-11  06:30:30 US/Michigan'),
       ('2018-03-11  07:30:30 US/Michigan'),
       ('2018-03-11  08:30:30 US/Michigan'),
       ('2018-03-11  09:30:30 US/Michigan'),
       ('2018-03-11  10:30:30 US/Michigan');


SELECT * FROM tstampwtz;
/*
 id |            tswtz
----+------------------------------
  1 | Sat Mar 24 02:30:30 2018 GMT
  2 | Sun Mar 25 02:30:30 2018 GMT
  3 | Sun Mar 25 01:30:30 2018 GMT
  4 | Sat Mar 10 07:30:30 2018 GMT
  5 | Sun Mar 11 07:30:30 2018 GMT
(5 rows)
*/
