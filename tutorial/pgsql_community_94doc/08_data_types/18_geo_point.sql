/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.1   Points

    psql -d mytestdb -U pgmihai
    \i 18_geo_point.sql

    help:  \?
    clear: \qecho '\033[2J'
*/

/*  Geometric Types
    Name      Storage Size  Description Representation
    ------+-----------+--------+-----------------+-----------------------------
    point    16 bytes      Point on a plane                   (x,y)
    line     32 bytes      Infinite line                      {A,B,C}
    1seg     32 bytes      Finite line segment                ((x1,y1),(x2,y2))
    box      32 bytes      Rectangular box                    ((x1,y1),(x2,y2))
    path     16+16n bytes  Closed path (similar to polygon)   ((x1,y1),...)
    path     16+16n bytes  Open path                          [(x1,y1),...]
    polygon  40+16n bytes  Polyon (similar to closed path)    ((x1,y1),...)
    circle   24 bytes      Circle (center point and radius)   <(x,y),r>
    ----------------------------------------------------------------------------
*/

/*  Points are fundamental 2-dimensional building block for geometric types.
    Point type is specified using:
    (x, y)
     x, y
    where x, y are floting-point values.
*/
DROP TABLE IF EXISTS points CASCADE;

CREATE TABLE points (id SERIAL, pt point);

INSERT INTO points (pt) VALUES
       (point (1, 1)),
       (point (1.0000000000000099, 1.0000000000000099)); --maxim 14 digits

SELECT * FROM points;
/*
 id |                 pt
----+-------------------------------------
  1 | (1,1)
  2 | (1.00000000000001,1.00000000000001)
(2 rows)
*/


SELECT (point(1,1) + point(5,9));       -- (6,10)
SELECT (point(3,5) - point(1,1));       -- (2,4)

-- point(x1,y1) * point(x2,y2) = point(x1*x2-y1*y2, x1*y2+y1*x2);
SELECT (point(2,3) * point(-2,-3));     -- (5,-12)

-- point(x1,y1) / point(x2,y2) = don't know yet.
SELECT (point(2,3) / point(-2,-3));     -- (-1,0)

-- distance between 2 points
SELECT (point(4,-2) <-> point(-2,-2));  -- 6
