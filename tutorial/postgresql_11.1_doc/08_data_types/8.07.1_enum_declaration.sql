/*  Cap.8   Data Types
    8.7     Enumerated Types
    8.7.1.  Declaration of Enumerated Types

    psql -d mytestdb -U pgmihai
    \i 14_enum_declaration.sql
    \?
    \qecho '\033[2J'
*/


/*  Enum types are created using the CREATE TYPE command.   */

DROP TABLE IF EXISTS person CASCADE;

CREATE TYPE mood_t AS ENUM ('sad', 'ok', 'happy');

CREATE TABLE person (name TEXT, mood mood_t);

INSERT INTO person VALUES
       ('Larry', 'sad'),
       ('Curly', 'ok'),
       ('Moe',   'happy');

SELECT * FROM enumt WHERE mood = 'happy';
/*
 name | mood
------+-------
 Moe  | happy
(1 row)
*/
