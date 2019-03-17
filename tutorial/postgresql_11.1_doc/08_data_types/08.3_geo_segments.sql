/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.3   Line Segments

    psql -d mytestdb -U pgmihai
    \i 8.08.3_geo_segments.sql
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


/*  Line segments are represented by pairs of points that are the endpoints
    of the segment. Values of type lseg are specified using any of the
    following syntaxes:

    [ (x1, y1) , (x2, y2) ]
    ( (x1, y1) , (x2, y2) )
      (x1, y1) , (x2, y2)
       x1, y1  ,  x2, y2

    where (x1,y1) and (x2,y2) are two different points on the line.
*/


DROP TABLE IF EXISTS segments CASCADE;

CREATE TABLE segments (id SERIAL, line_ lseg);

INSERT INTO segments(line_) VALUES
       (CAST('[(2,0), (0,4)]'::text AS lseg)),
       (CAST('((2,0), (0,4))'::text AS lseg)),
       (CAST(' (2,0), (0,4) '::text AS lseg)),
       (CAST('  2,0 ,  0,4  '::text AS lseg));

SELECT * FROM segments;
/*
 id |     line_
----+---------------
  1 | [(2,0),(0,4)]
  2 | [(2,0),(0,4)]
  3 | [(2,0),(0,4)]
  4 | [(2,0),(0,4)]
(4 rows)
*/
