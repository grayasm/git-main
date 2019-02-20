/*  Chapter 5. Data Definition
    5.10. Partitioning
    5.10.2 Declarative partitioning
    5.9.2. Implementing paritioning -- removed in 11.1

    psql -d mytestdb -U pgmihai
    \i 28_implementing_partitioning.sql
    \?
    \qecho '\033[2J'
*/

/*      Partitioning using table inheritance allows for several features not
        supported by declarative partitioning, such as:

        - child tables may have extra columns not present in the parent
        - it allows for multiple inheritance
        - declarative paritioning only supports range,list and hash paritioning
          whereas table inheritance allows data to be divided in a manner of the
          user's choosing
        - some operations require a stronger lock (ACCESS EXCLUSIVE) when using
          declarative partitioning than when using table inheritance for which
          a SHARE UPDATE EXCLUSIVE lock is enough
*/


/*      Create the master table. */
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
        city_id        int not null,
        logdate        date not null,
        peaktemp       int,
        unitsales      int
        );

/*      Create one partition for each year.
        Provide non-overlapping table constraints.
*/
CREATE TABLE measurement_y2017 (
        CHECK (logdate >= DATE '2017-01-01' AND logdate < DATE '2018-01-01')
        )
        INHERITS (measurement);

CREATE TABLE measurement_y2018 (
        CHECK (logdate >= DATE '2018-01-01' AND logdate < DATE '2019-01-01')
        )
        INHERITS (measurement);

/*      We probably need indexes on key columns too. */
CREATE INDEX measurement_y2017_logdate ON measurement_y2017 (logdate);
CREATE INDEX measurement_y2018_logdate ON measurement_y2018 (logdate);

/*      We want our application to be able to say:
        INSERT INTO measurement ...
        and have the data redirected into the appropriate partition table.
        We do this with a simple trigger function.
*/
CREATE OR REPLACE FUNCTION measurement_insert_trigger()
RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.logdate >= DATE '2017-01-01' AND NEW.logdate < DATE '2018-01-01') THEN
       INSERT INTO measurement_y2017 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2018-01-01' AND NEW.logdate < DATE '2019-01-01') THEN
       INSERT INTO measurement_y2018 VALUES (NEW.*);
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


/*      Insert and display some partitions data. */
INSERT INTO measurement
        VALUES(1001, '2017-01-02 16:00:00', 0, 2),
              (1001, '2017-07-09 10:00:00', 28, 20),
              (1001, '2018-04-08 16:00:00', 15, 15);

SELECT * FROM measurement;
