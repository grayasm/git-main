/*  Cap.7   Queries
    7.4     Combining queries

    psql -d mytestdb -U pgmihai
    \i 14_combining_queries.sql
*/


/*      http://www.postgresqltutorial.com/postgresql-union/

        The result of two queries can be combined using set of operations
        union, intersection and difference. The syntax is:

        query1 UNION [ALL] query2
        query1 INTERSECT [ALL] query2
        query1 EXCEPT [ALL] query2
*/

DROP TABLE IF EXISTS sales1, sales2 CASCADE;
CREATE TABLE sales1 (nume TEXT, ammount NUMERIC);
CREATE TABLE sales2 (nume TEXT, ammount NUMERIC);
INSERT INTO sales1 VALUES ('Mike', 100), ('John', 200), ('Mary', 300);
INSERT INTO sales1 VALUES ('Mike', 101), ('John', 201), ('Mary', 300);




/*      We often use the UNION operator to combine data from similar tables
        that are not perfectly normalized.
        Those tables are often found in the reporting or data warehouse system.
        UNION - will remove duplicate rows
        UNION ALL - will include duplicate rows
*/



SELECT * FROM sales1 UNION SELECT * FROM sales2;
/*
 nume | ammount
------+---------
 John |     201
 Mike |     101
 John |     200
 Mary |     300
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
 Mary |     300
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


