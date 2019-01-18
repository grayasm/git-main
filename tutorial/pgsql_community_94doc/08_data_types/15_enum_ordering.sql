/*  Cap.8   Data Types
    8.7     Enumerated Types
    8.7.2.  Ordering

    psql -d mytestdb -U pgmihai
    \i 15_enum_ordering.sql

    help:  \?
    clear: \qecho '\033[2J'
*/


/*  The ordering of the values in an enum type is the order in which the values
    were listed when the type was created.
    All standard comparison operators and related aggregate functions are
    supported for enums.
*/

DROP TABLE IF EXISTS person CASCADE;

CREATE TYPE mood_t AS ENUM ('sad', 'ok', 'happy');

CREATE TABLE person (name TEXT, mood mood_t);

INSERT INTO person VALUES
       ('Larry', 'sad'),
       ('Curly', 'ok'),
       ('Moe',   'happy');

SELECT * FROM person WHERE mood > 'sad';
/*
 name  | mood
-------+-------
 Curly | ok
 Moe   | happy
(2 rows)
*/
SELECT * FROM person WHERE mood > 'sad' ORDER BY mood;
/*
 name  | mood
-------+-------
 Curly | ok
 Moe   | happy
(2 rows)
*/
SELECT * FROM person WHERE mood = (SELECT MIN(mood) FROM person);
/*
 name  | mood
-------+------
 Larry | sad
(1 row)
*/
