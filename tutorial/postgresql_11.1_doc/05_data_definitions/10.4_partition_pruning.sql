/*  Chapter 5. Data Definition
    5.10.4 Partition Pruning

    psql -d mytestdb -U pgmihai
    \i 5.10.4_partition_pruning.sql
    \?
    \qecho '\033[2J'
*/

/*      Partition pruning is a query optimization technique that improves
        performance for declarative paritioned tables.
        /var/lib/pgsql/11/data/postgresql.conf must have
        enable_partition_pruning=on
*/

DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
       city_id       INT  NOT NULL,
       logdate       DATE NOT NULL,
       peaktemp      INT,
       unitsales     INT
       )
       PARTITION BY RANGE (logdate);

/*      Each parition table must have non-overlapping bounds. */
CREATE TABLE measurement_y2006m02 PARTITION OF measurement
       FOR VALUES FROM ('2006-02-01') TO ('2006-03-01');

CREATE TABLE measurement_y2006m03 PARTITION OF measurement
       FOR VALUES FROM ('2006-03-01') TO ('2006-04-01');

CREATE TABLE measurement_y2006m04 PARTITION OF measurement
       FOR VALUES FROM ('2006-04-01') TO ('2006-05-01');


/*      Optional create the index of the key column on the partitioned table. */
CREATE INDEX ON measurement (logdate);

/*      Inserting data is done on the parent table. */
INSERT INTO measurement VALUES
       (1, '2006-02-12', 29.3, 213),
       (1, '2006-03-13', 24.5, 115),
       (1, '2006-04-14', 25.6, 108);

/*      Without partitioning pruning, the next query would scan each of the
        partitions of the measurement table. With pruning enabled, the planer
        will examine the definition of each partition and prove that the
        partition need to be scanned because it could not contain any rows
        meeting the query's WHERE clause.
*/
SET enable_partition_pruning = off; -- the default
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2006-04-01';
/*
                                                 QUERY PLAN
-------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=93.82..93.83 rows=1 width=8)
   ->  Append  (cost=8.93..89.20 rows=1851 width=0)
         ->  Bitmap Heap Scan on measurement_y2006m02  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m02_logdate_idx  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m03  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m03_logdate_idx  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
         ->  Bitmap Heap Scan on measurement_y2006m04  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m04_logdate_idx  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
(14 rows)
*/


SET enable_partition_pruning = on;
EXPLAIN SELECT count(*) FROM measurement WHERE logdate >= DATE '2006-04-01';
/*
                                                 QUERY PLAN
-------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=31.27..31.28 rows=1 width=8)
   ->  Append  (cost=8.93..29.73 rows=617 width=0)
         ->  Bitmap Heap Scan on measurement_y2006m04  (cost=8.93..26.65 rows=617 width=0)
               Recheck Cond: (logdate >= '2006-04-01'::date)
               ->  Bitmap Index Scan on measurement_y2006m04_logdate_idx  (cost=0.00..8.78 rows=617 width=0)
                     Index Cond: (logdate >= '2006-04-01'::date)
(6 rows)
*/
