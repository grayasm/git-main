/*  Chapter 5. Data Definition
    5.9. Partitioning
    5.9.3. Managing partitions

    psql -d mytestdb -U pgmihai
    \i 27_managing_partitions.sql
*/


/*      It is common to want to remove old partitions of data and periodically
        add new partitions for new data. One of the most important advantages
        of paritioning is precisely that it allows this otherwise painful task
        to be executed nearly instantaneously by manipulating the partition
        structure, rather than physically moving large amounts of data around.

        > drop a partition
        > remove a parition from partitioned table, but preserve access to it
        > add a new partition
        > create a new table and add it later to the partitioned table
*/



/*      Create the master table. */
DROP TABLE IF EXISTS measurement CASCADE;
/*      Make sure all partitions are gone. */
DROP TABLE IF EXISTS measurement_y2010, measurement_y2011, measurement_y2012,
                     measurement_y2013, measurement_y2014, measurement_y2015,
                     measurement_y2016;

CREATE TABLE measurement (
        city_id        int not null,
        logdate        date not null,
        peaktemp       int,
        unitsales      int
        );

/*      Create 2 partitions only. The rest of them will be managed later. */
CREATE TABLE measurement_y2010 (
        CHECK (logdate >= DATE '2010-01-01' AND logdate < DATE '2011-01-01')
        )
        INHERITS (measurement);

CREATE TABLE measurement_y2011 (
        CHECK (logdate >= DATE '2011-01-01' AND logdate < DATE '2012-01-01')
        )
        INHERITS (measurement);

/*      We probably need indexes on key columns too. */
CREATE INDEX measurement_y2010_logdate ON measurement_y2010 (logdate);
CREATE INDEX measurement_y2011_logdate ON measurement_y2011 (logdate);

/*      We want our application to be able to say:
        INSERT INTO measurement ...
        and have the data redirected into the appropriate partition table.
        We do this with a simple trigger function.
*/
CREATE OR REPLACE FUNCTION measurement_insert_trigger()
RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.logdate >= DATE '2010-01-01' AND NEW.logdate < DATE '2011-01-01') THEN
       INSERT INTO measurement_y2010 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2011-01-01' AND NEW.logdate < DATE '2012-01-01') THEN
       INSERT INTO measurement_y2011 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2012-01-01' AND NEW.logdate < DATE '2013-01-01') THEN
       INSERT INTO measurement_y2012 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2013-01-01' AND NEW.logdate < DATE '2014-01-01') THEN
       INSERT INTO measurement_y2013 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2014-01-01' AND NEW.logdate < DATE '2015-01-01') THEN
       INSERT INTO measurement_y2014 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2015-01-01' AND NEW.logdate < DATE '2016-01-01') THEN
       INSERT INTO measurement_y2015 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2016-01-01' AND NEW.logdate < DATE '2017-01-01') THEN
       INSERT INTO measurement_y2016 VALUES (NEW.*);
    ELSE
       RAISE EXCEPTION 'Date out of range. Fix measurement_insert_trigger()';
    END IF;
    RETURN NULL;
END;
$$
LANGUAGE plpgsql;


/*      After creating the function we create a trigger which calls
        the trigger function.
*/
CREATE TRIGGER insert_measurement_trigger
BEFORE INSERT ON measurement
FOR EACH ROW EXECUTE PROCEDURE measurement_insert_trigger();


/*      Insert and display partitions data. */
INSERT INTO measurement
        VALUES(1001, '2010-01-02 16:00:00', 0, 2),
              (1001, '2010-07-09 10:00:00', 28, 20),
              (1001, '2011-04-08 16:00:00', 15, 15);

SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales 
---------+------------+----------+-----------
    1001 | 2010-01-02 |        0 |         2
    1001 | 2010-07-09 |       28 |        20
    1001 | 2011-04-08 |       15 |        15
(3 rows)
*/



/*      Drop the parition for 2010. */
DROP TABLE measurement_y2010;
SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales 
---------+------------+----------+-----------
    1001 | 2011-04-08 |       15 |        15
(1 row)
*/


/*      Remove the partition for 2011 from the partitioned table, but preserve
        access to it.
*/
ALTER TABLE measurement_y2011 NO INHERIT measurement;
SELECT * FROM measurement;
/*
 city_id | logdate | peaktemp | unitsales 
---------+---------+----------+-----------
(0 rows)
*/



/*      Add a new partition to handle new data.*/
CREATE TABLE measurement_y2012 (
        CHECK (logdate >= DATE '2012-01-01' AND logdate < DATE '2013-01-01')
        )
        INHERITS (measurement);
INSERT INTO measurement VALUES
        (1002, '2012-01-31', 0, 0),
        (1002, '2012-02-29', 5, 5),
        (1002, '2012-03-31', 8, 8),
        (1002, '2012-04-30', 12, 12);
SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales 
---------+------------+----------+-----------
    1002 | 2012-01-31 |        0 |         0
    1002 | 2012-02-29 |        5 |         5
    1002 | 2012-03-31 |        8 |         8
    1002 | 2012-04-30 |       12 |        12
(4 rows)
*/




/*      Create a new table outside the partition structure and make it a proper
        partition later.
*/
CREATE TABLE measurement_y2013
        (LIKE measurement INCLUDING DEFAULTS INCLUDING CONSTRAINTS);
ALTER TABLE measurement_y2013 ADD CONSTRAINT y2013
        CHECK (logdate >= DATE '2013-01-01' AND logdate < DATE '2014-01-01');

INSERT INTO measurement_y2013 VALUES
        (1003, '2013-05-31', 17, 17),
        (1003, '2013-06-30', 20, 80),
        (1003, '2013-07-31', 31, 100),
        (1003, '2013-08-31', 35, 300);

ALTER TABLE measurement_y2013 INHERIT measurement;
SELECT * FROM measurement;

/*
 city_id |  logdate   | peaktemp | unitsales 
---------+------------+----------+-----------
    1002 | 2012-01-31 |        0 |         0
    1002 | 2012-02-29 |        5 |         5
    1002 | 2012-03-31 |        8 |         8
    1002 | 2012-04-30 |       12 |        12
    1003 | 2013-05-31 |       17 |        17
    1003 | 2013-06-30 |       20 |        80
    1003 | 2013-07-31 |       31 |       100
    1003 | 2013-08-31 |       35 |       300
(8 rows)
*/

        
