/*  Cap.7   Queries
    7.4     Combining queries

    psql -d mytestdb -U pgmihai
    \i 7.04.0_combining_queries.sql
    \?
    \qecho '\033[2J'
*/


/*      The result of two queries can be combined using set of operations
        union, intersection and difference. The syntax is:

        query1 UNION [ALL] query2
        query1 INTERSECT [ALL] query2
        query1 EXCEPT [ALL] query2
*/


/*      http://www.postgresqltutorial.com/postgresql-union/

        The UNION operator combines result sets of two or more SELECT statements
        into a single result set.
        The following rules applies to the queries:

        > Both queries must return the same number of columns.
        > The corresponding columns in the queries must have compatible data
          types.

       The UNION operator removes all duplicate rows unless the UNION ALL
       is used. To sort the result by a column use ORDER BY clause.
*/

DROP TABLE IF EXISTS sales1, sales2 CASCADE;
CREATE TABLE sales1 (nume TEXT, ammount NUMERIC);
CREATE TABLE sales2 (nume TEXT, ammount NUMERIC);
INSERT INTO sales1 VALUES ('Mike', 100), ('John', 200), ('Mary', 300);
INSERT INTO sales1 VALUES ('Mike', 101), ('John', 201), ('Mary', 300);


SELECT * FROM sales1 UNION SELECT * FROM sales2;
/*
 nume | ammount
------+---------
 John |     201
 Mike |     101
 John |     200
 Mary |     300     <-- duplicate removed
 Mike |     100
(5 rows)
*/

SELECT * FROM sales1 UNION ALL SELECT * FROM sales2;
/*
 nume | ammount
------+---------
 Mike |     100
 John |     200
 Mary |     300
 Mike |     101
 John |     201
 Mary |     300     <-- duplicate not removed
(6 rows)
*/

SELECT * FROM sales1 UNION ALL SELECT * FROM sales2 ORDER BY nume ASC, ammount DESC;
/*
 nume | ammount
------+---------
 John |     201
 John |     200
 Mary |     300
 Mary |     300
 Mike |     101
 Mike |     100
(6 rows)
*/


/*      http://www.postgresqltutorial.com/postgresql-intersect/

        PostgreSQL INTERSECT operator combines the result sets of two or more
        SELECT statements into a single result set. The INTERSECT operator
        returns any rows that are available in both result set or returned
        by both queries.
*/
-- 3 tables: key employees, hi-position employees, normal employees
DROP TABLE IF EXISTS keys_empl, hipo_empl, norm_empl CASCADE;

CREATE TABLE norm_empl(id SERIAL PRIMARY KEY, nume TEXT);
CREATE TABLE keys_empl(id INT PRIMARY KEY, _date DATE,
                       FOREIGN KEY (id) REFERENCES norm_empl(id));
CREATE TABLE hipo_empl(id INT PRIMARY KEY, _date DATE,
                       FOREIGN KEY (id) REFERENCES norm_empl(id));

INSERT INTO norm_empl(nume) VALUES ('Hi Mia'),
                                   ('No Jia'),
                                   ('Ky Tao'),
                                   ('Hi Mao'),
                                   ('Ni Tao'),
                                   ('Ky Bao');
INSERT INTO keys_empl VALUES (1, '2012-10-10'),
                             (3, '2013-10-10'),
                             (6, '2013-12-12');
INSERT INTO hipo_empl VALUES (1, '2012-10-10'),
                             (4, '2011-02-01'),
                             (6, '2013-12-12');


SELECT * FROM keys_empl INTERSECT SELECT * FROM hipo_empl;
/*
 id |   _date
----+------------
  1 | 2012-10-10
  6 | 2013-12-12
(2 rows)
*/


/*      http://www.postgresqltutorial.com/postgresql-tutorial/postgresql-except/

        The EXCEPT operator returns rows by comparing the result sets of two
        or more quires. The EXCEPT operator returns distinct rows from
        the first (left) query that are not in the output of the second (right)
        query.
        The follwing rules are mandatory:
        > The number of columns and their orders must be the same in the
          two queries.
        > The data types of the respective columns must be compatible.
*/

DROP TABLE IF EXISTS film,inventory CASCADE;
CREATE TABLE film (id SERIAL PRIMARY KEY, title VARCHAR(255) NOT NULL);
CREATE TABLE inventory (id SERIAL PRIMARY KEY, title VARCHAR(255) NOT NULL,
                        FOREIGN KEY(id) REFERENCES film(id));

INSERT INTO film(title) VALUES ('Star Wars: The Last Jedi'),
                               ('Beauty and the Beast'),
                               ('The Fate of the Furious'),
                               ('Despicable Me 3'),
                               ('Jumanji: Welcome to the Jungle'),
                               ('Spider-Man: Homecoming'),
                               ('Wolf Warrior 2'),
                               ('Guardians of the Galaxy Vol. 2'),
                               ('Thor: Ragnarok'),
                               ('Wonder Woman');
INSERT INTO inventory VALUES (2, 'Beauty and the Beast'),
                             (5, 'Jumanji: Welcome to the Jungle');

-- the following films are in the inventory (don't need EXCEPT for this)
SELECT inventory.id, inventory.title
       FROM inventory INNER JOIN film ON film.id = inventory.id
       ORDER BY id;
/*
 id |             title
----+--------------------------------
  2 | Beauty and the Beast
  5 | Jumanji: Welcome to the Jungle
(2 rows)
*/


-- to get the films that are not in the inventory you need EXCEPT
SELECT film.id, film.title
       FROM film
       EXCEPT
            SELECT DISTINCT inventory.id, inventory.title
            FROM inventory INNER JOIN film ON film.id = inventory.id
       ORDER BY id;
/*
 id |             title
----+--------------------------------
  1 | Star Wars: The Last Jedi
  3 | The Fate of the Furious
  4 | Despicable Me 3
  6 | Spider-Man: Homecoming
  7 | Wolf Warrior 2
  8 | Guardians of the Galaxy Vol. 2
  9 | Thor: Ragnarok
 10 | Wonder Woman
(8 rows)
*/
