/*  Chapter 5. Data Definition
    5.10. Partitioning
    5.10.3 Implementation Using Inheritance

    psql -d mytestdb -U pgmihai
    \i 5.10.3_inheritance_paritioning.sql
    \?
    \qecho '\033[2J'
*/


/*      While the built-in declarative partitioning is suitable for most common
        use cases, there are some circumstances where a more flexible approach
        may be useful. Partitioning using table inheritance allows for several
        features not supported by declarative partitioning, such as:

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


SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales
---------+------------+----------+-----------
       1 | 2006-02-12 |       29 |       213
       1 | 2006-03-13 |       25 |       115
       1 | 2006-04-14 |       26 |       108
(3 rows)
*/


/*      To remove old data quickly, simply drop the child table that is no
        longer necessary.
*/
DROP TABLE measurement_y2006m02;


/*      To remove child table from the inheritance hierarcy table but retain
        access to it as a table in its own right.
        Similar was with the declarative partitioning, we can run pg_dump,
        create reports and what not on this table on its own.
*/
ALTER TABLE measurement_y2006m03 NO INHERIT measurement;
DROP TABLE measurement_y2006m03;


/*      Alternatively, one may want to create and populate the new child table
        before adding it to the table hierarchy. This could allow data to be
        loaded, checked and transformed before being made visible to queries
        on the parent table.
*/
DROP TABLE IF EXISTS measurement_y2006m05 CASCADE;
CREATE TABLE measurement_y2006m05 (
       LIKE measurement INCLUDING DEFAULTS INCLUDING CONSTRAINTS);

ALTER TABLE measurement_y2006m05 ADD CONSTRAINT y2006m05
      CHECK (logdate >= DATE '2006-05-01' AND logdate < DATE '2006-06-01');

INSERT INTO measurement_y2006m05 VALUES
       (1, '2006-05-10', 22.5, 30),
       (1, '2006-05-20', 30.2, 121);

ALTER TABLE measurement_y2006m05 INHERIT measurement;

\dt
/*
                List of relations
 Schema |         Name         | Type  |  Owner
--------+----------------------+-------+---------
 public | measurement          | table | pgmihai
 public | measurement_y2006m04 | table | pgmihai
 public | measurement_y2006m05 | table | pgmihai
(3 rows)
*/

SELECT * FROM measurement;
/*
 city_id |  logdate   | peaktemp | unitsales
---------+------------+----------+-----------
       1 | 2006-04-14 |       26 |       108
       1 | 2006-05-10 |       23 |        30
       1 | 2006-05-20 |       30 |       121
(3 rows)
*/
