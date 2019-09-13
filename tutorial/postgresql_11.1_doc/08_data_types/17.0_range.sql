/*  Cap.8   Data Types
    8.17.   Range Types
    8.17.1  Built-in Range Types
    8.17.2  Examples
    8.17.3  Inclusive and Exclusive Bounds
    8.17.4  Infinite (Unbounded) Ranges
    8.17.5  Range Input/Output
    8.17.6  Constructing Ranges
    8.17.7  Discrete Range Types
    8.17.8  Defining New Range Types
    8.17.9  Indexing
    8.17.10 Constraints on Ranges

    # run as user=postgres , required for last part (extension btree_gist)
    psql -d mytestdb -U postgres
    \i   17.0_range.sql
    \?
    \qecho '\033[2J'
*/


SET ROLE pgmihai;

/*      PostgreSQL comes with the following built-in range types:

        int4range - range of integer
        int8range - range of bigint
        numrange  - range of numeric
        tsrange   - range of timestamp without time zone
        tstzrange - range of timestamp with time zone
        daterange - range of date
*/

DROP TABLE IF EXISTS reservation CASCADE;
CREATE TABLE reservation (room int, during tsrange);
INSERT INTO reservation VALUES (1108, '[2010-01-01 14:30, 2010-01-01 15:30)');

-- Containment
SELECT int4range (10, 20) @> 3;
/*
 ?column?
----------
 f
(1 row)
*/

-- Overlaps
SELECT numrange (11.1, 22.2) && numrange (20.0, 30.0);
/*
 ?column?
----------
 t
(1 row)
*/

-- Extract the upper bound
SELECT upper(int8range (15, 25));
/*
 upper
-------
    25
(1 row)
*/

-- Compute the intersection
SELECT int4range (10, 20) * int4range (15, 25);
/*
 ?column?
----------
 [15,20)
(1 row)
*/

-- Is the range empty?
SELECT isempty(numrange (1, 5));
/*
 isempty
---------
 f
(1 row)
*/


/*      Every non-empty range has two bound, the lower bound (LB) and the
        upper bound (UB). All points between these values are included in the
        range. An inclusive bound means that the LB/UB point itself is included
        in the range as well, while an exlusive bound means that the LB/UB point
        is not included in the range.
        Inclusive LB is '['  , inclusive UP is ']'
        Exclusive LB is '('  , exclusive UP is ')'
        The functions lower_inc and upper_inc test the inclusivity of LB/UP.

        When LB is missing, this is equivalent to considering that the lower
        bound is "minus infinity", and similar for "plus infinity". These
        infinity values are never values of the range's element type, and can
        never be part of the range.
        The functions lower_inf and upper_inf test for infinite lower and upper
        bounds of a range.

        The input for a range value must follow one of the following patterns:
        (lower-bound, upper-bound)
        (lower-bound, upper-bound]
        [lower-bound, upper-bound)
        [lower-bound, upper-bound]
        empty
*/

--includes 3, does not include 7, and does include all points in between
SELECT '[3,7)'::int4range;
/*
 int4range
-----------
 [3,7)
(1 row)
*/


-- does not include either 3 or 7, but include all points in between
SELECT '(3,7)'::int4range;
/*
 int4range
-----------
 [4,7)
(1 row)
*/

-- includes only the single point 4
SELECT '[4,4]'::int4range;
/*
 int4range
-----------
 [4,5)
(1 row)
*/

-- includes no points (and will be normalized to 'empty')
SELECT '[4,4)'::int4range;
/*
 int4range
-----------
 empty
(1 row)
*/


/*      Each range type has a constructor function with the same name as the
        range type. The constructor function accepts two or three arguments.
        The two-argument form constructs a range in standard form [LB inclusive,
        UP exclusive), while the three-argument form constructs a range with
        bounds of the form specified by the third argument, one of: () (] [) []
*/

SELECT numrange(1.0, 14.0, '(]');
/*
  numrange
------------
 (1.0,14.0]
(1 row)
*/

SELECT numrange(1.0, 14.0);
/*
  numrange
------------
 [1.0,14.0)
(1 row)
*/

SELECT int8range(1, 14, '(]');
/*
 int8range
-----------
 [2,15)
(1 row)
*/

SELECT numrange(NULL, 2.2);
/*
 numrange
----------
 (,2.2)
(1 row)
*/


/*      A discrete range is one whose element type has a well-defined "step",
        such as integer or date. In these types two elements can be said to be
        adjacent, when there are no valid values between them. This contrasts
        with continuous ranges, where it's always (or almost always) possible
        to identify other element values between two given values (numrange,
        tsrange, tstzrange).
*/

/*      Users can define their own range types. */

DROP TYPE IF EXISTS floatrange CASCADE;
CREATE TYPE floatrange AS RANGE (
       subtype         = float8,
       subtype_diff    = float8mi
       );

SELECT '[1.234, 5.678]'::floatrange;
/*
  floatrange
---------------
 [1.234,5.678]
(1 row)
*/


DROP FUNCTION IF EXISTS time_subtype_diff(x time, y time) CASCADE;
CREATE FUNCTION time_subtype_diff(x time, y time)
       RETURNS float8 AS
       'SELECT EXTRACT(EPOCH FROM ( x - y ))'
       LANGUAGE sql STRICT IMMUTABLE;

CREATE TYPE timerange AS RANGE (
       subtype = time,
       subtype_diff = time_subtype_diff
       );

SELECT '[11:10, 23:00]'::timerange;
/*
      timerange
---------------------
 [11:10:00,23:00:00]
(1 row)
*/


/*      GiST and SP-GiST indexes can be created for table columns of range types.
        For instance, to create a GiST index:
*/
CREATE INDEX reservation_idx ON reservation USING GIST (during);


/*      While UNIQUE is a natural constraint for scalar values, it is usually
        unsuitable for range types. Instead, an exclusion constraint is often
        more appropriate.
*/
DROP TABLE IF EXISTS reservation CASCADE;
CREATE TABLE reservation (
       during tsrange,
       EXCLUDE USING GIST(during WITH &&)
       );

-- the constraint will prevent any overlapping values from existing in the table
-- at the same time:
INSERT INTO reservation VALUES ('[2010-01-01 11:30, 2010-01-01 15:00)');
INSERT INTO reservation VALUES ('[2010-01-01 14:45, 2010-01-01 15:45)');
/*
ERROR:  conflicting key value violates exclusion constraint "reservation_during_excl"
DETAIL:  Key (during)=(["2010-01-01 14:45:00","2010-01-01 15:45:00"))
         conflicts with existing key (during)=(["2010-01-01 11:30:00", "2010-01-01 15:00:00")).
*/

/*      You can use a btree_gist extension to define exclusion constraints on
        plain scalar data types, which can then be combined with range
        exclusions for maximum flexibility.
*/
SET ROLE postgres; -- switch to Administrator (required by btree_gist)

DROP EXTENSION IF EXISTS btree_gist CASCADE;
CREATE EXTENSION btree_gist;

SET ROLE pgmihai; -- swith back to User

DROP TABLE IF EXISTS room_reservation CASCADE;

CREATE TABLE room_reservation (
       room TEXT,
       during tsrange,
       EXCLUDE USING GIST (room WITH =, during WITH &&)
       );

INSERT INTO room_reservation VALUES ('123A', '[2010-01-01 14:00, 2010-01-01 15:00)');
INSERT INTO room_reservation VALUES ('123A', '[2010-01-01 14:30, 2010-01-01 15:30)');
/*
ERROR:  conflicting key value violates exclusion constraint "room_reservation_room_during_excl"
DETAIL:  Key (room, during)=(123A, ["2010-01-01 14:30:00","2010-01-01 15:30:00")) 
         conflicts with existing key
             (room, during)=(123A, ["2010-01-01 14:00:00","2010-01-01 15:00:00")).
*/
INSERT INTO room_reservation VALUES ('123B', '[2010-01-01 14:30, 2010-01-01 15:30)');
SELECT * FROM room_reservation;
/*
 room |                    during
------+-----------------------------------------------
 123A | ["2010-01-01 14:00:00","2010-01-01 15:00:00")
 123B | ["2010-01-01 14:30:00","2010-01-01 15:30:00")
(2 rows)
*/
