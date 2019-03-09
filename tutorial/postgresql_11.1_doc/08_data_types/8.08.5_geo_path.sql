/*  Cap.8   Data Types
    8.8.    Geometry Types
    8.8.2   Lines

    psql -d mytestdb -U pgmihai
    \i 19_geo_line.sql
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


/*  Paths are represented by lists of connected points. Paths can be open,
    where the first and last points in the list are considered not connected,
    or closed, where the first and last points are considered connected.

    Values of the type path are specified using any of hte following syntaxes:

    [ (x1, y1) , ... , (xn, yn) ]
    ( (x1, y1) , ... , (xn, yn) )
      (x1, y1) , ... , (xn, yn)
      (x1, y1  , ... ,  xn, yn)
       x1, y1  , ... ,  xn, yn

   where the points are the end points of the line segments comprising the path.
   Square brackets [] indicate an open path, while parantheses () indicate a
   closed path. When the outermost parantheses are omitted, a closed path is
   assumed.
*/

DROP TABLE IF EXISTS paths CASCADE;

CREATE TABLE paths (id SERIAL, path_ path);

INSERT INTO paths(path_) VALUES
       (CAST('[ (0, 0), (5, 0), (5, 10), (0, 10)         ]'::text AS path)),
       (CAST('( (0, 0), (5, 0), (5, 10), (0, 10), (0, 0) )'::text AS path)),
       (CAST('  (0, 0), (5, 0), (5, 10), (0, 10), (0, 0)  '::text AS path)),
       (CAST('  (0, 0 ,  5, 0 ,  5, 10 ,  0, 10 ,  0, 0)  '::text AS path)),
       (CAST('   0, 0 ,  5, 0 ,  5, 10 ,  0, 10 ,  0, 0   '::text AS path));

SELECT * FROM paths;
