/*  Cap.8   Data Types
    8.5     Date/Time Types

    psql -d mytestdb -U pgmihai
    \i 08_date_time_input.sql
*/


/*
  Name           Storage Size  Description  Low value   High value   Resolution
-------------------+---------+-------------+-----------+----------+----------
timestamp [(p)]      8 bytes   both date     4713 BC    294276 AD  1 microsecond
[without time zone]            and time (no                         / 14 digits
                               time zone)

timestamp [(p]       8 bytes   both date     4713 BC    294276 AD  1 microsecond
with time zone                 and time,                           / 14 digits
                               with time zone

date                 4 bytes   date (no      4713 BC    5874897 AD     1 day
                               time of day

time [(p)]
[without time zone]  8 bytes   time of day   00:00:00   24:00:00   1 microsecond
                               (no date)                           / 14 digits

time [(p)]
with time zone      12 bytes   times of day  00:00:00+1459         1 microsecond
                               only, with                          / 14 digits
                               time zone                24:00:00-1459

interval [fields]   16 bytes   time interval -178000000  178000000 1 microsecond
[(p)]                                        years       years     / 14 digits
*/


DROP TABLE IF EXISTS datetable CASCADE;
CREATE TABLE datetable (id      SERIAL,
                        timp    timestamp without time zone);
INSERT INTO datetable(timp) VALUES ('1999-01-08');
