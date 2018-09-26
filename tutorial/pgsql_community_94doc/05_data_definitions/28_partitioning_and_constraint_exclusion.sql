/*  Chapter 5. Data Definition
    5.9. Partitioning
    5.9.4. Partitioning and constraint exclusion

    psql -d mytestdb -U pgmihai
    \i 27_partitioning_and_constraint_exclusion.sql
*/


/*      Constraint exclusion is a query optimization technique that improves
        performance for parititioned tables.

        SET constraint_exclusion = on;
        SELECT count(*) FROM measurement WHERE logdate >= DATE '2010-01-01';

        > with constraint exclusion 'off', the query would scan each parition.
        > with constraint exclusion 'on' , the planner will examine the
          constraints of each partition to prove that it need NOT to be scanned
          because it could not contain any rows meeting the WHERE clause.
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


/*      Create the trigger function. */
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


/*      Create the trigger. */
CREATE TRIGGER insert_measurement_trigger
BEFORE INSERT ON measurement
FOR EACH ROW EXECUTE PROCEDURE measurement_insert_trigger();


/*      Insert data. */
INSERT INTO measurement VALUES
        (1001, '2017-01-31', 01, 01),
        (1001, '2017-02-28', 02, 02),
        (1001, '2017-03-31', 03, 03),
        (1001, '2017-04-30', 04, 04),
        (1001, '2017-05-31', 05, 05),
        (1001, '2017-06-30', 06, 06),
        (1001, '2017-07-31', 07, 07),
        (1001, '2017-08-31', 08, 08),
        (1001, '2017-09-30', 09, 09),
        (1001, '2017-10-31', 10, 10),
        (1001, '2017-11-30', 11, 11),
        (1001, '2017-12-31', 12, 12),
        (1001, '2018-01-31', 01, 01),
        (1001, '2018-02-28', 02, 02),
        (1001, '2018-03-31', 03, 03),
        (1001, '2018-04-30', 04, 04),
        (1001, '2018-05-31', 05, 05),
        (1001, '2018-06-30', 06, 06),
        (1001, '2018-07-31', 07, 07),
        (1001, '2018-08-31', 08, 08),
        (1001, '2018-09-30', 09, 09),
        (1001, '2018-10-31', 10, 10),
        (1001, '2018-11-30', 11, 11),
        (1001, '2018-12-31', 12, 12);



SET constraint_exclusion = on;
SELECT count(*) FROM measurement WHERE logdate >= DATE '2018-10-01';
/*
 count 
-------
     3
(1 row)
*/



/*      You can use EXPLAIN to see if the plan is optimized or not. */
SET constraint_exclusion = off;
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2018-10-01';
/*
                                         QUERY PLAN                                         
--------------------------------------------------------------------------------------------
 Aggregate  (cost=67.20..67.21 rows=1 width=0)
   ->  Append  (cost=0.00..64.25 rows=1181 width=0)
         ->  Seq Scan on measurement  (cost=0.00..0.00 rows=1 width=0)
               Filter: (logdate >= '2018-10-01'::date)
         ->  Seq Scan on measurement_y2017 measurement  (cost=0.00..32.12 rows=590 width=0)
               Filter: (logdate >= '2018-10-01'::date)
         ->  Seq Scan on measurement_y2018 measurement  (cost=0.00..32.12 rows=590 width=0)
               Filter: (logdate >= '2018-10-01'::date)
(8 rows)
*/

SET constraint_exclusion = on;
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2018-10-01';
/*
                                         QUERY PLAN                                         
--------------------------------------------------------------------------------------------
 Aggregate  (cost=33.60..33.61 rows=1 width=0)
   ->  Append  (cost=0.00..32.12 rows=591 width=0)
         ->  Seq Scan on measurement  (cost=0.00..0.00 rows=1 width=0)
               Filter: (logdate >= '2018-10-01'::date)
         ->  Seq Scan on measurement_y2018 measurement  (cost=0.00..32.12 rows=590 width=0)
               Filter: (logdate >= '2018-10-01'::date)
(6 rows)
*/
