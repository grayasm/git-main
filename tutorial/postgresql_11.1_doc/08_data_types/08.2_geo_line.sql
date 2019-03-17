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
    line     32 bytes      Infinite line                      {A,B,C}
    lseg     32 bytes      Finite line segment                ((x1,y1),(x2,y2))
    box      32 bytes      Rectangular box                    ((x1,y1),(x2,y2))
    path     16+16n bytes  Closed path (similar to polygon)   ((x1,y1),...)
    path     16+16n bytes  Open path                          [(x1,y1),...]
    polygon  40+16n bytes  Polyon (similar to closed path)    ((x1,y1),...)
    circle   24 bytes      Circle (center point and radius)   <(x,y),r>
    ----------------------------------------------------------------------------
*/

/*  Lines are represented by the linear equation Ax + By + C = 0
    where A and B are not both zero. Values of type line are input and output
    in the following form:
    {A,B,C} <-- not fully implemented in PostgreSQL 9.2.24 in CentOS7.5

    Alternatively, any of the following forms can be used for input:
    [ (x1, y1) , (x2, y2) ]
    ( (x1, y2) , (x2, y2) )
      (x1, y1) , (x2, y2)
       x1, y1  ,  x2, y2
*/

DROP TABLE IF EXISTS lines CASCADE;

CREATE TABLE lines (id SERIAL, line_ line);

INSERT INTO lines(line_) VALUES
       (CAST('{2,-1,3}'::text AS line)),   -- y = 2x + 3
       (CAST('{2,-2,3}'::text AS line)),   -- y =(2x + 3)/2
       (CAST('{2,-2,0}'::text AS line));   -- y = 2x

SELECT * FROM lines;
/*
 id |  line_
----+----------
  1 | {2,-1,3}
  2 | {2,-2,3}
  3 | {2,-2,0}
(3 rows)
*/

/*  For the alternative form see line segments sample. */
