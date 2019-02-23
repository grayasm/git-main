        Cap.7   Queries

  Overview          :   SELECT 3*4;
                        SELECT random();
                        SELECT a,b+c FROM t1;
  The FROM clause   :   SELECT * FROM t1,t2;  -->Cartesian product of t1,t2 rows                
  Joining tables    :   SELECT * FROM t1 LEFT JOIN t2 ON t1.id = t2.id WHERE t2.v = 'x';
  Table aliases     :   SELECT * FROM t1 AS a JOIN t2 AS b ON a.id = b.id;
  Subqueries        :   SELECT a.* FROM (SELECT * FROM t1) AS a;
  Table functions   :   CREATE FUNCTION f(id integer)
                               RETURNS TABLE (id integer, v text)
                               AS
                               $$
                                    SELECT * FROM t1 WHERE n > id;
                               $$
                        LANGUAGE 'sql' VOLATILE;
                        SELECT * FROM f(1) AS a;

    LATERAL subquery:   SELECT * FROM t1, LATERAL (SELECT * FROM t2 WHERE t1.id=t2.id) AS a;
    The WHERE clause:   SELECT * FROM t1 WHERE x BETWEEN (SELECT x FROM t2 WHERE y=t1.x+10) AND 100;
    The GROUP BY and
    HAVING clauses  :   SELECT x,sum(y) FROM t1 GROUP BY x HAVING sum(y) > 3;
    Window function :   SELECT x, avg(y) OVER (PARTITION BY x) FROM t1 INNER JOIN t2 USING(id);
    The SELECT list :   SELECT t1.*, t2.x FROM t1 INNER JOIN t2 USING(id);
    Column labels   :   SELECT x, x+y+z AS sum FROM t1;
    DISTINCT clause :   SELECT DISTINCT x, y FROM t1 ORDER BY x,y;
    Combining ops   :   SELECT * FROM t1 UNION ALL SELECT * FROM t2 ORDER BY n ASC, m DESC;
    Sorting rows    :   SELECT a,b,c FROM t1 ORDER BY a ASC, b ASC NULLS FIRST, c DESC;
    LIMIT & OFFSET  :   SELECT a,b FROM t1 ORDER BY a LIMIT 4 OFFSET 3;
    VALUES          :   SELECT * FROM (VALUES(1,'x'), (2,'y')) AS t(num, letter);
    The WITH
    statement       :  WITH qry1 AS (
                                 SELECT x, sum(y) AS toty FROM t1 GROUP BY x),
                            qry2 AS (
                                 SELECT x FROM qry1 WHERE toty > 10)
                            SELECT x FROM t1
                            WHERE x IN (SELECT x FROM qry2)
                            GROUP BY x;

    RECURSIVE WITH  :   WITH RECURSIVE t(n) AS (
                             VALUES(1)
                             UNION ALL
                                    SELECT n+1 FROM t WHERE n < 1000
                             )
                             SELECT sum(n) FROM t;
    Data modifying
    statements in
    WITH            :   WITH t AS (
                             UPDATE table SET v=v*10
                             RETURNING *
                             )
                             SELECT * FROM t;
