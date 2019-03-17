/*  Chapter 5. Data Definition
    5.10.5. Paritioning and Constraint Exclusion

    psql -d mytestdb -U pgmihai
    \i   10.5_constraint_exclusion.sql
    \?
    \qecho '\033[2J'
*/


/*      Constraint exclusion is a query optimization technique similar to
        partition pruning. While it is primarily used for partitioning
        implemented using the legacy inheritance method, it can be used
        for all purposes, including with declarative partitioning.
        /var/lib/pgsql/11/data/postgresql.conf must have
        contraint_exclusion = partition;

        The default (and recommended) setting of contraint_exclusion is neither
        on nor off, but parition, which causes the technique to be applied
        only to queries that are likely to be working on inheritance
        partitioned tables. The on setting causes the planner to examine
        CHECK constraints in all queries.
*/


/*      Create the master table. */
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
        city_id        INT NOT NULL,
        logdate        DATE NOT NULL,
        peaktemp       INT,
        unitsales      INT
        );

/*      Create several child tables that each inherit from the master table.
        Normally these tables will not add any columns to the set inherited
        from the master.
*/
CREATE TABLE measurement_y2006m02 (
        CHECK (logdate >= DATE '2006-02-01' AND logdate < DATE '2006-03-01')
        )
        INHERITS (measurement);

CREATE TABLE measurement_y2006m03 (
        CHECK (logdate >= DATE '2006-03-01' AND logdate < DATE '2006-04-01')
        )
        INHERITS (measurement);

CREATE TABLE measurement_y2006m04 (
        CHECK (logdate >= DATE '2006-04-01' AND logdate < DATE '2006-05-01')
        )
        INHERITS (measurement);


/*      For each child table, create an index on the key column(s), as well as
        any other indexes you might want.
*/
CREATE INDEX measurement_y2006m02_logdate ON measurement_y2006m02 (logdate);
CREATE INDEX measurement_y2006m03_logdate ON measurement_y2006m03 (logdate);
CREATE INDEX measurement_y2006m04_logdate ON measurement_y2006m04 (logdate);


/*      We want our application to be able to say:
        INSERT INTO measurement ...
        and have the data be redirected into the appropriate child table.
        We can arrange that by attaching a suitable trigger function to the
        master table.
*/
CREATE OR REPLACE FUNCTION measurement_insert_trigger()
RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.logdate >= DATE '2006-02-01' AND NEW.logdate < DATE '2006-03-01') THEN
       INSERT INTO measurement_y2006m02 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2006-03-01' AND NEW.logdate < DATE '2006-04-01') THEN
       INSERT INTO measurement_y2006m03 VALUES (NEW.*);
    ELSIF (NEW.logdate >= DATE '2006-04-01' AND NEW.logdate < DATE '2006-05-01') THEN
       INSERT INTO measurement_y2006m04 VALUES (NEW.*);
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
INSERT INTO measurement VALUES
       (1, '2006-02-12', 29.3, 213),
       (1, '2006-03-13', 24.5, 115),
       (1, '2006-04-14', 25.6, 108);


SET constraint_exclusion=off;
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2006-04-01';
/*
                                               QUERY PLAN
---------------------------------------------------------------------------------------------------------
 Aggregate  (cost=93.83..93.84 rows=1 width=8)
   ->  Append  (cost=0.00..89.20 rows=1852 width=0)
         ->  Seq Scan on measurement  (cost=0.00..0.00 rows=1 width=0)
               Filter: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m02  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m02_logdate  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m03  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m03_logdate  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m04  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m04_logdate  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
(16 rows)
*/


SET constraint_exclusion=partition;
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2006-04-01';
/*
                                               QUERY PLAN
---------------------------------------------------------------------------------------------------------
 Aggregate  (cost=31.28..31.29 rows=1 width=8)
   ->  Append  (cost=0.00..29.74 rows=618 width=0)
         ->  Seq Scan on measurement  (cost=0.00..0.00 rows=1 width=0)
               Filter: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m04  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m04_logdate  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
(8 rows)
*/
