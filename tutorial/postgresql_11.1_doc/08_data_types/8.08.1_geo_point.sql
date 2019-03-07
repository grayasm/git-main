/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.1   Points

    psql -d mytestdb -U pgmihai
    \i 18_geo_point.sql
    \?
    \qecho '\033[2J'
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

/*  https://www.reddit.com/r/PostgreSQL/comments/ai7cid/pointx1y1pointx2y2_formula
    * and / works similar as with complex numbers
    (a+bi)(c+di) = ac + adi + bci + bdi^2 =
                 = ac + adi + bci - bd =
                 = ac - bd  + (ad + bc)i
    point(x1,y1) * point(x2,y2) = point(x1x2-y1y2, x1y2+y1x2);

    (a+bi)/(c+di)= (a+bi)(c-di)/(c+di)(c-di) =
                 = (ac - adi + cbi - bdi^2)/(c^2 - cdi + cdi -d^2i^2)=
                 = (ac - adi + cbi + bd)/(c^2 +d^2) =
                 = (ac + bd)/(c^2 + d^2) + (cb - ad)i/(c^2 + d^2);
    point(x1,y1) / point(x2,y2) =
                 point((x1x2 + y1y2)/(x2x2 + y2y2), (x2y1-x1y2)/(x2x2 + y2y2));
*/
SELECT (point(2,3) * point(-2,-3));     -- (5,-12)
SELECT (point(2,3) / point(-2,-3));     -- (-1,0)


-- distance between 2 points
SELECT (point(4,-2) <-> point(-2,-2));  -- 6
