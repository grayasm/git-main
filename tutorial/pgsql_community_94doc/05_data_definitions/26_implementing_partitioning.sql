/*  Chapter 5. Data Definition
    5.9. Partitioning
    5.9.2. Implementing paritioning

    psql -d mytestdb -U pgmihai
    \i 26_implementing_partitioning.sql
*/

/*      Partitioning refers to splitting what is logically one large table into
        smaller physical pieces. Query performance can be improved dramatically
        when heavily accessed rows of the table are in a single partition or a
        small number of partitions. The partition reduces the index size making
        it more likely that the heavily-used parts of the indexes fit in memory.

        The benefits are worthwile when a table is very large, which is when
        the size of the table exceeds the physical memory of the database server.

        PostgreSQL supports paritioning via table inheritance. Each parition
        must be created as a child table of a SINGLE parent table. The parent
        table itself is normally empty; it exists just to represent the entire
        data set.
*/


/*      Create the master table. */
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
        city_id        int not null,
	    logdate        date not null,
		peaktemp  	   int,
		unitsales	   int
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
