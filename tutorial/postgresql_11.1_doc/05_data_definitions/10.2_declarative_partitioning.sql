/*  Chapter 5. Data Definition
    5.10.2. Declarative Partitioning

    psql -d mytestdb -U pgmihai
    \i   10.2_declarative_partitioning.sql
    \?
    \qecho '\033[2J'


    Declarative partitioning was introduced first with version 10.
    It does not need much coding compared with partitioning using inheritance.
    The parent table is refered to as "partitioned table".
    The partitioning method can be RANGE, LIST or HASH.
    The partitioning key is a list of one or more columns.
    The partitions do not require explicit constraints, only non-overlapping bounds.
    The partitions can be attached and detached.
    The partitions can be created on a TABLESPACE (see 22.6 Tablespaces)
    The partitions have exactly the same columns as the parent.
    Updating one raw in a partition can move it to another partition, therefore
    an exclusive lock is required for certain operations.
*/


/*  Create the partitioned table (parent) using PARTITION BY clause.
    The partitioning method is RANGE and the partition key is logdate.
*/
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
       city_id       INT  NOT NULL,
       logdate       DATE NOT NULL,
       peaktemp      INT,
       unitsales     INT
       )
       PARTITION BY RANGE (logdate);

/*  Each parition table must have non-overlapping bounds. */
CREATE TABLE measurement_y2006m02 PARTITION OF measurement
       FOR VALUES FROM ('2006-02-01') TO ('2006-03-01');

CREATE TABLE measurement_y2006m03 PARTITION OF measurement
       FOR VALUES FROM ('2006-03-01') TO ('2006-04-01');

CREATE TABLE measurement_y2006m04 PARTITION OF measurement
       FOR VALUES FROM ('2006-04-01') TO ('2006-05-01');


/*  Optional create the index of the key column on the partitioned table. */
CREATE INDEX ON measurement (logdate);

/*  Inserting data is done on the parent table. */
INSERT INTO measurement VALUES
       (1, '2006-02-12', 29.3, 213),
       (1, '2006-03-13', 24.5, 115),
       (1, '2006-04-14', 25.6, 108);
-- INSERT 0 2


\dt
/*
                List of relations
 Schema |         Name         | Type  |  Owner
--------+----------------------+-------+---------
 public | measurement          | table | pgmihai
 public | measurement_y2006m02 | table | pgmihai
 public | measurement_y2006m03 | table | pgmihai
 public | measurement_y2006m04 | table | pgmihai
(4 rows)
*/


/*  Data must be mapped to an existing partition or will cause an error. */
INSERT INTO measurement VALUES
       (2, '2006-09-13', 33.1, 500);
-- ERROR:  no partition of relation "measurement" found for row


/*  To implement sub-partitioning use: */
CREATE TABLE measurement_y2006m05 PARTITION OF measurement
       FOR VALUES FROM ('2006-05-01') TO ('2006-06-01')
       PARTITION BY RANGE (peaktemp);

INSERT INTO measurement VALUES
       (3, '2006-05-05', 25.5, 55);
-- ERROR:  no partition of relation "measuremen_y2006m05" found for row
-- because partitioning by peaktemp requires subpartitions with explicit bounds


/*  Removing partitions is faster than deleting rows.
    This command requires taking an ACCESS EXCLUSIVE lock on the parent table.
*/
DROP TABLE measurement_y2006m02;


/*  Preferable method is to remove partition (DETACH PARTITION) from the parent
    but retain access to it as a table in its own rigt.
    Can back it up (pg_dump) or COPY data or run reports etc, on the table.
*/
ALTER TABLE measurement DETACH PARTITION measurement_y2006m03;
DROP TABLE measurement_y2006m03;


/*  As an alternative, it is sometimes more convenient to create the table
    outside the partition structure, and make it a proper partition later.
*/
CREATE TABLE measurement_y2006m06 (
       LIKE measurement INCLUDING DEFAULTS INCLUDING CONSTRAINTS
       );

ALTER TABLE measurement_y2006m06
      ADD CONSTRAINT y2006m06
      CHECK (logdate >= DATE '2006-06-01' AND logdate < DATE '2006-07-01');

INSERT INTO measurement_y2006m06 VALUES
       (6, '2006-06-12', 28.5, 209),
       (6, '2006-06-13', 29.8, 212);

ALTER TABLE measurement ATTACH PARTITION measurement_y2006m06
      FOR VALUES FROM ('2006-06-01') TO ('2006-07-01');


\dt
/*
                List of relations
 Schema |         Name         | Type  |  Owner
--------+----------------------+-------+---------
 public | measurement          | table | pgmihai
 public | measurement_y2006m04 | table | pgmihai
 public | measurement_y2006m05 | table | pgmihai
 public | measurement_y2006m06 | table | pgmihai
(4 rows)
*/


SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales
---------+------------+----------+-----------
       1 | 2006-04-14 |       26 |       108
       6 | 2006-06-12 |       29 |       209
       6 | 2006-06-13 |       30 |       212
(3 rows)
*/
