/*  Cap.8   Data Types
    8.7     Enumerated Types
    8.7.3.  Type Safety

    psql -d mytestdb -U pgmihai
    \i 16_enum_type_safety.sql
    \?
    \qecho '\033[2J'
*/


/*  Each enumerated data type is separate and cannot be compared with other
    enumerated types. If you really need to do it, you can either write a
    custom operator or add explicit casts to the query.
*/
DROP TABLE IF EXISTS person, holidays CASCADE;

CREATE TYPE mood_t AS ENUM ('sad', 'ok', 'happy');
CREATE TYPE happy_t AS ENUM ('happy', 'very happy', 'ecstatic');

CREATE TABLE person (name TEXT, mood mood_t);
CREATE TABLE holidays (weeks INTEGER, happiness happy_t);

INSERT INTO person VALUES
       ('Larry', 'sad'),
       ('Curly', 'ok'),
       ('Moe',   'happy');

INSERT INTO holidays VALUES (4, 'happy');
INSERT INTO holidays VALUES (6, 'very happy');
INSERT INTO holidays VALUES (8, 'ecstatic');
INSERT INTO holidays VALUES (2, 'sad');
-- ERROR:  invalid input value for enum happy_t: "sad"

SELECT person.name, holidays.weeks FROM person, holidays
       WHERE person.mood = holidays.happiness;
-- ERROR:  operator does not exist: mood_t = happy_t

SELECT person.name, holidays.weeks FROM person, holidays
       WHERE person.mood::text = holidays.happiness::text;
/*
 name | weeks
------+-------
 Moe  |     4
(1 row)
*/
