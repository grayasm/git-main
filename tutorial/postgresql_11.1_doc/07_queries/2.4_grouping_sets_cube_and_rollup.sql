/*  Cap.7   Queries
    7.2     Table Expressions
    7.2.4   Grouping SETS, CUBE and ROLLUP

    psql -d mytestdb -U pgmihai
    \i   2.4_grouping_sets_cube_and_rollup.sql
    \?
    \qecho '\033[2J'
*/


DROP TABLE IF EXISTS items_sold CASCADE;
CREATE TABLE items_sold (brand TEXT, size TEXT, sales INTEGER);
INSERT INTO items_sold VALUES ('Foo', 'L', 10),
                              ('Foo', 'M', 20),
                              ('Bar', 'M', 15),
                              ('Bar', 'L', 5);

/*
        More complex grouping operations than those described above are possible
        using the concept of grouping sets. The data selected by the FROM and
        WHERE clauses is grouped separately by each specified grouping set,
        aggregates computed for each group just as for simple GROUP BY clauses,
        and then the results returned.
*/
SELECT * FROM items_sold;
/*
 brand | size | sales
-------+------+-------
 Foo   | L    |    10
 Foo   | M    |    20
 Bar   | M    |    15
 Bar   | L    |     5
(4 rows)
*/

SELECT brand, size, sum(sales)
       FROM items_sold
       GROUP BY GROUPING SETS ((brand), (size), ());
/*
 brand | size | sum
-------+------+-----
       |      |  50
 Foo   |      |  30
 Bar   |      |  20
       | L    |  15
       | M    |  35
(5 rows)
*/


DROP TABLE IF EXISTS items CASCADE;
CREATE TABLE items (a TEXT, b INTEGER, c TEXT, d INTEGER, e INTEGER);
INSERT INTO items VALUES ('a1', 1, 'c1', 10, 100),
                         ('a2', 2, 'c2', 20, 200),
                         ('a3', 3, 'c3', 30, 300),
                         ('a4', 4, 'c4', 40, 400),
                         ('a5', 5, 'c5', 50, 500);

SELECT a, b, c , d
       FROM items
       GROUP BY CUBE ((a,b), (c, d));
/*
 a  | b | c  | d
----+---+----+----
    |   |    |
 a5 | 5 | c5 | 50
 a3 | 3 | c3 | 30
 a2 | 2 | c2 | 20
 a1 | 1 | c1 | 10
 a4 | 4 | c4 | 40
 a1 | 1 |    |
 a3 | 3 |    |
 a2 | 2 |    |
 a5 | 5 |    |
 a4 | 4 |    |
    |   | c4 | 40
    |   | c5 | 50
    |   | c1 | 10
    |   | c2 | 20
    |   | c3 | 30
(16 rows)
*/
