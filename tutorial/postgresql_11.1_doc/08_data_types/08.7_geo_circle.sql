/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.7   Circles

    psql -d mytestdb -U pgmihai
    \i   08.7_geo_circle.sql
    \?
    \qecho '\033[2J'
*/


/*  Geometric Types
    Name      Storage Size  Description Representation
    ------+-----------+--------+-----------------+-----------------------------
    point    16 bytes      Point on a plane                   (x,y)
    line     32 bytes      Infinite line, not fully implemented in 9.2
    lseg     32 bytes      Finite line segment                ((x1,y1),(x2,y2))
    box      32 bytes      Rectangular box                    ((x1,y1),(x2,y2))
    path     16+16n bytes  Closed path (similar to polygon)   ((x1,y1),...)
    path     16+16n bytes  Open path                          [(x1,y1),...]
    polygon  40+16n bytes  Polyon (similar to closed path)    ((x1,y1),...)
    circle   24 bytes      Circle (center point and radius)   <(x,y),r>
    ----------------------------------------------------------------------------
*/


/*  Circles are represented by a center point and radius.
    Values of type circle are specified using any of the following syntaxes:

    < (x, y) , r >
    ( (x, y) , r )
      (x, y) , r
       x, y  , r

    where (x, y) is the center point and r is the radius of the circle.
    Circles are output using the first syntax.
*/

DROP TABLE IF EXISTS circles CASCADE;

CREATE TABLE circles (id SERIAL, circle_ circle);

INSERT INTO circles (circle_) VALUES
       (CAST('< (10, 10), 14.142135624 >'::text AS circle)),
       (CAST('( (10, 10), 14.142135624 )'::text AS circle)),
--     (CAST('  (10, 10), 14.142135624  '::text AS circle)), --invalid syntax?
       (CAST('   10, 10 , 14.142135624  '::text AS circle));

SELECT * FROM circles;
/*
 id |        circle_
----+------------------------
  1 | <(10,10),14.142135624>
  2 | <(10,10),14.142135624>
  3 | <(10,10),14.142135624>
(3 rows)
*/
