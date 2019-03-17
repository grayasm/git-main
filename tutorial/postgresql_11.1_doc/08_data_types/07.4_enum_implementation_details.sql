/*  Cap.8   Data Types
    8.7     Enumerated Types
    8.7.4.  Implementation Details

    psql -d mytestdb -U pgmihai
    \i 17_enum_implementation_details.sql
    \?
    \qecho '\033[2J'
*/


-- https://stackoverflow.com/questions/25811017/how-to-delete-an-enum-type-value-in-postgres
DROP TABLE IF EXISTS users CASCADE;
CREATE TYPE power_t AS ENUM ('classifier', 'moderator');
CREATE TABLE users (uid INTEGER, name TEXT, power power_t);
INSERT INTO users VALUES
       (1, 'Joe', 'moderator'),
       (10, 'Jim', 'classifier');

ALTER TYPE power_t ADD VALUE 'god';
INSERT INTO users VALUES (42, 'Martin', 'god');

-- opps, maybe that was a bad idea
CREATE TYPE power_t_new AS ENUM ('classifier', 'moderator');

-- Remove the values that won't be compatible with the new definition
DELETE FROM users WHERE power = 'god';

-- Conver to new type, casting via text representation
ALTER TABLE users
      ALTER COLUMN power TYPE power_t_new
      USING (power::text::power_t_new);

-- and swap the types
DROP TYPE power_t;
ALTER TYPE power_t_new RENAME TO power_t;

SELECT * FROM users;
/*
 uid | name |   power
-----+------+------------
   1 | Joe  | moderator
  10 | Jim  | classifier
(2 rows)
*/



/*  An enum value is 4 bytes on disk.
    The length of an enum value's textual label is limited by the NAMEDATALEN
    setting compiled into PostgreSQL which is 64 default, in standard builds.
    Preset option 'max_identifier_length (integer) is one less NAMEDATALEN.
*/

SHOW max_identifier_length;
/*
 max_identifier_length
-----------------------
 63
(1 row)
*/


/*  Enum labels are case sensitive, so 'happy' is not the same as 'HAPPY'.
    The translations from internal enum values to textual labels are kept in
    the system catalog pg_enum.
*/

SELECT * FROM pg_enum;
/*
 enumtypid | enumsortorder | enumlabel
-----------+---------------+------------
     16531 |             1 | sad
     16531 |             2 | ok
     16531 |             3 | happy
     16563 |             1 | happy
     16563 |             2 | very happy
     16563 |             3 | ecstatic
     16630 |             1 | classifier
     16630 |             2 | moderator
(8 rows)
*/
