/*  Chapter 5. Data Definition
    5.10.2. Declarative Partitioning

    psql -d mytestdb -U pgmihai
    \i 29_declarative_partitioning.sql
    \?
    \qecho '\033[2J'
*/


/*  Create the partitioned table (parent) using PARTITION BY clause.
    The partitioning method is RANGE and the partition key is logdate.
*/
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
       city_id       INT NOT NULL,
       logdate       DATE NOT NULL,
       peaktemp      INT,
       unitsales     INT )
       PARTITION BY RANGE (logdate);

/*  Each parition table must have non-overlapping bounds. */
CREATE TABLE measurement_y2006m02 PARTITION OF measurement
       FOR VALUES FROM ('2006-02-01') TO ('2006-03-01');

CREATE TABLE measurement_y2006m03 PARTITION OF measurement
       FOR VALUES FROM ('2006-03-01') TO ('2006-04-01');


/*  Create the index of the key column on the partitioned table. */
CREATE INDEX ON measurement (logdate);

/*  Inserting data is done on the parent table. */
INSERT INTO measurement VALUES
       (1, '2006-02-12', 29.3, 213),
       (1, '2006-03-13', 24.5, 115);
-- INSERT 0 2


/*  Data must be mapped to an existing partition or will cause an error. */
INSERT INTO measurement VALUES
       (2, '2008-09-13', 33.1, 500);
-- ERROR:  no partition of relation "measurement" found for row
