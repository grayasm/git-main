/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.4   Boxes

    psql -d mytestdb -U pgmihai
    \i   08.4_geo_box.sql
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

/*  Boxes are represented by pairs of points that are opposite corners of the
    box. Values of type box are specified using any of the following syntaxes:

    ( (x1, y1) , (x2, y2) )
      (x1, y1) , (x2, y2)
       x1, y1  ,  x2, y2

    where (x1,y1) and (x2,y2) are any two opposite corners of the box.
*/



DROP TABLE IF EXISTS boxes CASCADE;

CREATE TABLE boxes (id SERIAL, box_ box);

INSERT INTO boxes(box_) VALUES
       (CAST('((0,0), (10,10))'::text AS box)),
       (CAST(' (0,0), (10,10) '::text AS box)),
       (CAST('  0,0 ,  10,10  '::text AS box));

SELECT * FROM boxes;
/*
 id |     box_
----+---------------
  1 | (10,10),(0,0)
  2 | (10,10),(0,0)
  3 | (10,10),(0,0)
(3 rows)
*/
