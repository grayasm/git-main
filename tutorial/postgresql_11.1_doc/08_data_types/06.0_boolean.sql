/*  Cap.8   Data Types
    8.5     Boolean Type

    psql -d mytestdb -U pgmihai
    \i   06.0_boolean.sql
    \?
    \qecho '\033[2J'
*/


/*  PostgreSQL provides the standard SQL type boolean.
    It can have 3 states: "true", "false" and "unknown" or SQL null value.

    Valid literals for "true": TRUE, 't', 'true', 'y', 'yes', 'on', '1'
    Valid literals for "false": FALSE, 'f', 'false', 'n', 'no', 'off', '0'
*/

DROP TABLE IF EXISTS booleant CASCADE;
CREATE TABLE booleant (id SERIAL, bv boolean, tv TEXT);
INSERT INTO booleant (bv, tv) VALUES
       (TRUE,   'sic est'),
       ('t',    'sic est'),
       ('true', 'sic est'),
       ('y',    'sic est'),
       ('yes',  'sic est'),
       ('on',   'sic est'),
       ('1',    'sic est'),
       (FALSE,  'non est'),
       ('f',    'non est'),
       ('false','non est'),
       ('n',    'non est'),
       ('no',   'non est'),
       ('off',  'non est'),
       ('0',    'non est');
SELECT * FROM booleant WHERE bv;
/*
 id | bv |   tv
----+----+---------
  1 | t  | sic est
  2 | t  | sic est
  3 | t  | sic est
  4 | t  | sic est
  5 | t  | sic est
  6 | t  | sic est
  7 | t  | sic est
(7 rows)
*/

SELECT * FROM booleant WHERE bv = FALSE;
/*
 id | bv |   tv
----+----+---------
  8 | f  | non est
  9 | f  | non est
 10 | f  | non est
 11 | f  | non est
 12 | f  | non est
 13 | f  | non est
 14 | f  | non est
(7 rows)
*/
