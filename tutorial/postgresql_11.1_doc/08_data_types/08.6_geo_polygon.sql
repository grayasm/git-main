/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.6   Polygons

    psql -d mytestdb -U pgmihai
    \i   08.6_geo_polygon.sql
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

/*  Polygons are represented by lists of points (the vertexes of the polygon).
    Polygons are very similar to CLOSED PATHS, but are stored differently and
    have their own set of support routines.

    Values of type polygon are specified using any of the following syntaxes:

    ( (x1, y1) , ... , (xn, yn) )
      (x1, y1) , ... , (xn, yn)
      (x1, y1  , ... ,  xn, yn)
       x1, y1  , ... ,  xn, yn

    where the points are the end points of the line segments comprising the
    boundary of the polygon.
    Polygons are output using the first syntax.
*/

DROP TABLE IF EXISTS polygons CASCADE;

CREATE TABLE polygons (id SERIAL, polygon_ polygon);

INSERT INTO polygons(polygon_) VALUES
       (CAST('((0,0), (5,0), (5,10), (0,10), (0,0))'::text AS polygon)),
       (CAST(' (0,0), (5,0), (5,10), (0,10), (0,0) '::text AS polygon)),
       (CAST(' (0,0,   5,0,   5,10,   0,10,   0,0) '::text AS polygon)),
       (CAST('  0,0,   5,0,   5,10,   0,10,   0,0  '::text AS polygon));

SELECT * FROM polygons;
/*
 id |             polygon_
----+-----------------------------------
  1 | ((0,0),(5,0),(5,10),(0,10),(0,0))
  2 | ((0,0),(5,0),(5,10),(0,10),(0,0))
  3 | ((0,0),(5,0),(5,10),(0,10),(0,0))
  4 | ((0,0),(5,0),(5,10),(0,10),(0,0))
(4 rows)
*/
