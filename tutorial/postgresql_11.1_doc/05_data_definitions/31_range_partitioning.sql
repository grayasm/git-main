/*  Chapter 5. Data Definition
    5.10. Partitioning
    5.10.2 Declarative Partitioning (PARTITION BY RANGE)

    psql -d mytestdb -U pgmihai
    \i 31_range_partitioning.sql
    \?
    \qecho '\033[2J'
*/


/*  http://pgdash.io/blog/partition-postgres-11.html

    1.  Update Moves Rows Across Partitions

        PostgreSQL 10 did not let you perform updates to rows that would result
        in the row ending up in a different partition.
        PostgreSQL 11 fixed it.
*/
DROP TABLE IF EXISTS measurement CASCADE;
CREATE TABLE measurement (
       logdate           DATE NOT NULL,
       peaktemp          INT,
       unitsales         INT
       )
       PARTITION BY RANGE (logdate);

CREATE TABLE measurement_y2016 PARTITION OF measurement
       FOR VALUES FROM ('2016-01-01') TO ('2017-01-01');
CREATE TABLE measurement_y2017 PARTITION OF measurement
       FOR VALUES FROM ('2017-01-01') TO ('2018-01-01');
INSERT INTO measurement(logdate, peaktemp, unitsales)
       VALUES ('2016-07-10',66,100);  -- goes into measurement_y2016 table

UPDATE measurement SET logdate = '2017-07-10' WHERE logdate = '2016-07-10';
--with v10 this would be an error
--ERROR: new row for relation "measurement_y2016" violates parition contraint

SELECT * FROM measurement_y2017;
/*
  logdate   | peaktemp | unitsales
------------+----------+-----------
 2017-07-10 |       66 |       100
(1 row)
*/


/*  2.  Create Default Paritions

        With v11 it is now possible to create a "default" parition, which can
        store rows that do not fall into any existing partition's range or list.
*/
CREATE TABLE measurement_default PARTITION OF measurement DEFAULT;
INSERT INTO measurement(logdate,peaktemp,unitsales)
       VALUES ('2018-07-10',66,100);
SELECT * FROM measurement;
/*
  logdate   | peaktemp | unitsales
------------+----------+-----------
 2017-07-10 |       66 |       100
 2018-07-10 |       66 |       100
(2 rows)
*/


/*  3.  Automatic Index Creation

        Indexes had to be created manually for each partition in v10.
        In v11, if you create an index on the parent table, Postgres will
        automatically crate indexes on all the child tables.
*/
CREATE INDEX salesindex ON measurement(unitsales);
\d measurement_y2016
/*
           Table "public.measurement_y2016"
  Column   |  Type   | Collation | Nullable | Default
-----------+---------+-----------+----------+---------
 logdate   | date    |           | not null |
 peaktemp  | integer |           |          |
 unitsales | integer |           |          |
Partition of: measurement FOR VALUES FROM ('2016-01-01') TO ('2017-01-01')
Indexes:
    "measurement_y2016_unitsales_idx" btree (unitsales)
*/


/*  4.  Foreign Key Support

        It was not possible to have a column in a partitioned table be a
        foreign key. But in v11, foreign keys are allowed.
*/
DROP TABLE IF EXISTS invoices CASCADE;
DROP TABLE IF EXISTS sale_ammounts_1 CASCADE;

CREATE TABLE invoices (
       invoice_id     INTEGER PRIMARY KEY
       );

CREATE TABLE sale_ammounts_1 (
       saledate       DATE NOT NULL,
       invoiceid      INTEGER REFERENCES invoices(invoice_id)
       )
       PARTITION BY RANGE(saledate);
