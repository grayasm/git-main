/*  Chapter 5. Data Definition
    5.9. Partitioning
    5.9.6. Caveats

    psql -d mytestdb -U pgmihai
    \i 30_caveats.sql
    \?
    \qecho '\033[2J'
*/


/*      There is no automatic way to verify that all of the CHECK constraints
        are mutually exclusive.

        The schemes shown here assume that the partition key column(s) of a
        row never change, or at least do not change enough to require it to
        move to another partition. An UPDATE that attempts to do that will
        fail because of the CHECK constraints.

        If you are using manual VACUUM or ANALYZE commands, don’t forget that
        you need to run them on each partition individually. A command like:
        ANALYZE measurement;
        will only process the master table.
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


/*      Create a trigger function for command INSERT INTO measurement ... */
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
INSERT INTO measurement VALUES
       (1001, '2017-12-29', 0, 0),
       (1001, '2018-01-01', 1, 1),
       (1001, '2018-01-29', 2, 2);

UPDATE measurement MY_TABLE SET A = A + 1;  -- normal form

SELECT * FROM measurement;
