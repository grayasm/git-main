/*  Chapter 5. Data Definition
    5.10.3 Implementation Using Inheritance

    psql -d mytestdb -U pgmihai
    \i 5.10.3_using_rules_instead_of_trigger.sql
    \?
    \qecho '\033[2J'
*/

/*      A different approach to redirecting inserts into the appropriate
        partition table is to set up rules, instead of a trigger, on the
        master table.

        A rule has significantly more overhead than a trigger,
        but the overhead is paid once per query rather than once per row,
        so this method might be advantageous for bulk-insert situations.
        In most cases, however, the trigger method will offer better performance.

        Another disadvantage of the rule approach is that there is no simple way
        to force an error if the set of rules doesn’t cover the insertion date;
        the data will silently go into the master table instead.
*/


/*      Create the master table. */
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
        city_id        int not null,
        logdate        date not null,
        peaktemp       int,
        unitsales      int
        );

/*      Create 2 partitions. */
CREATE TABLE measurement_y2017 (
        CHECK (logdate >= DATE '2017-01-01' AND logdate < DATE '2018-01-01')
        )
        INHERITS (measurement);

CREATE TABLE measurement_y2018 (
        CHECK (logdate >= DATE '2018-01-01' AND logdate < DATE '2019-01-01')
        )
        INHERITS (measurement);


/*      Instead of a trigger, we will define a rule for each partition
        to redirect the insert command.
*/
CREATE RULE insert_y2017 AS
ON INSERT TO measurement WHERE
   (logdate >= DATE '2017-01-01' AND logdate < DATE '2018-01-01')
DO INSTEAD
   INSERT INTO measurement_y2017 VALUES (NEW.*);

CREATE RULE insert_y2018 AS
ON INSERT TO measurement WHERE
   (logdate >= DATE '2018-01-01' AND logdate < DATE '2019-01-01')
DO INSTEAD
   INSERT INTO measurement_y2018 VALUES (NEW.*);


/*      Insert and display some partitions data. */
INSERT INTO measurement
        VALUES(1001, '2017-01-02 16:00:00', 0, 2),
              (1001, '2017-07-09 10:00:00', 28, 20),
              (1001, '2018-04-08 16:00:00', 15, 15);

SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales
---------+------------+----------+-----------
    1001 | 2017-01-02 |        0 |         2
    1001 | 2017-07-09 |       28 |        20
    1001 | 2018-04-08 |       15 |        15
(3 rows)
*/
