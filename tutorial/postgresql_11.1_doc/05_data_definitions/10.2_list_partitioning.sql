/*  Chapter 5. Data Definition
    5.10. Partitioning
    5.10.2 Declarative Partitioning (PARTITION BY LIST)

    psql -d mytestdb -U pgmihai
    \i 5.10.2_list_partitioning.sql
    \?
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS collections CASCADE;

CREATE TABLE collections (
       key               SERIAL,
       ts                TIMESTAMP WITH TIME ZONE NOT NULL,
       input_id          INTEGER NOT NULL,
       value             NUMERIC
       )
       PARTITION BY LIST (input_id);

CREATE TABLE input_1 PARTITION OF collections(key,ts,input_id,value)
       FOR VALUES IN (1);

CREATE TABLE input_2 PARTITION OF collections(key,ts,input_id,value)
       FOR VALUES IN (2);

INSERT INTO collections(ts,input_id,value) VALUES
       ('2017-01-01 23:00:00'::timestamp, 1, 0.98),
       ('2017-02-01 23:00:00'::timestamp, 1, 1.23),
       ('2017-03-01 23:00:00'::timestamp, 2, 1.34);

SELECT * FROM input_2;
/*
 key |           ts           | input_id | value
-----+------------------------+----------+-------
   3 | 2017-03-01 23:00:00+01 |        2 |  1.34
(1 row)
*/


/*      PostgreSQL will even check for overlapping ranges. So if we forgot to
        change the VALUES postgres will give us an error.
*/
CREATE TABLE input_3 PARTITION OF collections (key,ts,input_id,value)
       FOR VALUES IN (2);
-- ERROR:  partition "input_3" would overlap partition "input_2"
