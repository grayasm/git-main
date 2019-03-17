/*  Cap.8   Data Types
    8.5     Date/Time Types
    8.5.2   Date/Time Output

    psql -d mytestdb -U pgmihai
    \i   05.2_date_time_output.sql
    \?
    \qecho '\033[2J'
*/


/*  This was already discussed in the previous sample: 08_date_time_intput.sql

    DateStyle variable is a pair of 2 values representing:
    DateStyle = 'ISO, MDY'
    (a) first: the date/time output format
    (b) second: the date/time input convention

 (a)Style Specification  Description              Example
    -------------------+------------------------+------------------------------
    ISO                  ISO 8601, SQL Standard   1997-12-17  07:37:16-08
    SQL                  traditional style        12/17/1997  07:37:16.00 PST
    Postgres             original style           Wed Dec 17  07:37:16 1997 PST
    German               regional style           17.12.1997  07:37:16.00 PST
    ---------------------------------------------------------------------------

 (b)datestyle Setting    Input Ordering           Example Output
    -------------------+------------------------+------------------------------
    SQL, DMY             day/month/year           17/12/1997 15:37:16.00 CET
    SQL, MDY             month/day/year           12/17/1997 07:37:16.00 PST
    Postgres, DMY        day/month/year           Wed 17 Dec 07:37:16 1997 PST
    ---------------------------------------------------------------------------
*/

DROP TABLE IF EXISTS tstampwotz CASCADE;
CREATE TABLE tstampwotz (id SERIAL, tswotz timestamp without time zone);

SET DateStyle = 'ISO, DMY';
INSERT INTO tstampwotz (tswotz) VALUES
       ('1/2/1999         10:12:30.12345'),  -- DMY
       ('01/02/99         10:12:30.12345'),  -- DMY
       ('01/02/1999       10:12:30.12345');  -- DMY
SELECT * FROM tstampwotz;
/*
 id |          tswotz
----+---------------------------
  1 | 1999-02-01 10:12:30.12345              -- ISO form: YYYY-MM--DD HH:MM:SS
  2 | 1999-02-01 10:12:30.12345
  3 | 1999-02-01 10:12:30.12345
(3 rows)
*/


SET DateStyle = 'SQL, MDY';
DELETE FROM tstampwotz;
INSERT INTO tstampwotz (tswotz) VALUES
       ('2/1/1999      10:12:30.12345'),     -- MDY
       ('02/01/99      10:12:30.12345'),     -- MDY
       ('02/01/1999    10:12:30.12345');     -- MDY
SELECT * FROM tstampwotz;
/*
 id |          tswotz
----+---------------------------
  4 | 02/01/1999 10:12:30.12345              -- SQL form: MM/DD/YYYY HH:MM:SS
  5 | 02/01/1999 10:12:30.12345
  6 | 02/01/1999 10:12:30.12345
(3 rows)
*/


SET DateStyle = 'Postgres, YMD';
DELETE FROM tstampwotz;
INSERT INTO tstampwotz (tswotz) VALUES
       ('1999/2/1      10:12:30.12345'),     -- YMD
       ('99/02/01      10:12:30.12345'),     -- YMD
       ('1999/02/01    10:12:30.12345');     -- YMD
SELECT * FROM tstampwotz;
/*
 id |             tswotz
----+--------------------------------
  7 | Mon Feb 01 10:12:30.12345 1999         -- Postgres form:
  8 | Mon Feb 01 10:12:30.12345 1999         -- DayOfWeek Mon Day HH:MM::SS YYYY
  9 | Mon Feb 01 10:12:30.12345 1999
(3 rows)
*/
