/*  Cap.8   Data Types
    8.5     Date/Time Types
    8.5.3   Time Zones

    psql -d mytestdb -U pgmihai
    \i 10_date_time_zones.sql
    \?
    \qecho '\033[2J'
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



-- full timezone
\pset pager off
SELECT * FROM pg_timezone_names;
/*
                  name                  | abbrev | utc_offset | is_dst
----------------------------------------+--------+------------+--------
 CET                                    | CET    | 01:00:00   | f
 Zulu                                   | UTC    | 00:00:00   | f
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
\pset pager on

SET TimeZone='GMT';
INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-10  02:30:30 US/Michigan'),         --Hour+5, TZ+5

-- 2018 Sun, 11 Mar, 02:00 EST->DST +1h (DST start)    UTC-05 -> UTC-04

       ('2018-03-11  02:30:30 US/Michigan'), /* there is no 2:30AM on this date
                                                and timezone, because the
                                                clock jumps from 2AM->3AM
                                                Hour+5, TZ+5   instead of +4
                                              */
       ('2018-03-11  03:30:30 US/Michigan'),         --Hour+4, TZ+4
       ('2018-03-11  04:30:30 US/Michigan'),         --Hour+4, TZ+4
       ('2018-03-11  05:30:30 US/Michigan');         --Hour+4, TZ+4

SELECT * FROM tstampwtz;
/*
 id |         tswtz
----+------------------------
  1 | 2018-03-10 07:30:30+00
  2 | 2018-03-11 07:30:30+00
  3 | 2018-03-11 07:30:30+00
  4 | 2018-03-11 08:30:30+00
  5 | 2018-03-11 09:30:30+00
(5 rows)
*/


-- abbreviation timezone
DELETE FROM tstampwtz;
SELECT CURRENT_TIMESTAMP;     -- 2019-01-16 13:22:06.227265+00
\pset pager off
SELECT * FROM pg_timezone_abbrevs;

/*
 abbrev | utc_offset | is_dst
--------+------------+--------
 CEST   | 02:00:00   | t
 CET    | 01:00:00   | f      -- CET until: 2019, Sun, 31 Mar, 02:00 CET->CEST
 EDT    | -04:00:00  | t
 EST    | -05:00:00  | f      -- EST until: 2019, Sun, 10 Mar, 02:00 EST->EDT
..
*/
\pset pager on

INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-10  02:30:30  EST'),    -- Hour+5, TZ+5

-- 2018 Sun, 11 Mar, 02:00 EST->DST +1h (DST start)    UTC-05 -> UTC-04

       ('2018-03-11  02:30:30  EST'),    /* there is no 2:30AM on this date
                                            and timezone, because the
                                            clock jumps from 2AM->3AM
                                            Hour+5, TZ+5   instead of +4
                                          */
       ('2018-03-11  03:30:30  EDT'),    -- Hour+4, TZ+4
       ('2018-03-11  04:30:30  EDT'),    -- Hour+4, TZ+4
       ('2018-03-11  05:30:30  EDT');    -- Hour+4, TZ+4

SELECT * FROM tstampwtz;
/*
 id |         tswtz
----+------------------------
  6 | 2018-03-10 07:30:30+00
  7 | 2018-03-11 07:30:30+00
  8 | 2018-03-11 07:30:30+00
  9 | 2018-03-11 08:30:30+00
 10 | 2018-03-11 09:30:30+00
(5 rows)
*/



-- POSIX style  (offset possitive values are east from UTC)
-- this will consider the Linux file /usr/share/zoneinfo/poxisrules
-- and not the                       /var/lib/pgsql/data/postgresql.conf
-- when using STDoffsetDST, offset is always for the STD, e.g. EST5DST
-- when using STDoffset, offset must change with DST, e.g. EST5 or EST4

DELETE FROM tstampwtz;
INSERT INTO tstampwtz (tswtz) VALUES
       ('2018-03-10  02:30:30  EST5EDT'),    -- Hour+5, TZ+5

-- 2018 Sun, 11 Mar, 02:00 EST->DST +1h (DST start)    UTC-05 -> UTC-04

       ('2018-03-11  02:30:30  EST5EDT'),    -- corrected for DST, H+5, TZ+5
       ('2018-03-11  03:30:30  EST5EDT'),    -- Hour+4, TZ+4
       ('2018-03-11  04:30:30  EST5EDT'),    -- Hour+4, TZ+4
       ('2018-03-11  05:30:30  EST5EDT');    -- Hour+4, TZ+4

SELECT * FROM tstampwtz;
/*
 id |         tswtz
----+------------------------
 11 | 2018-03-10 07:30:30+00
 12 | 2018-03-11 07:30:30+00
 13 | 2018-03-11 07:30:30+00
 14 | 2018-03-11 08:30:30+00
 15 | 2018-03-11 09:30:30+00
(5 rows)
*/
