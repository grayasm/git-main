/*  Cap.3 Advanced Features
    3.6 Inheritance

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 05_inheritance.sql
*/
DROP TABLE IF EXISTS weather; -- from prev example;
DROP TABLE IF EXISTS capitals;
DROP TABLE IF EXISTS cities;


/*  Inheritance is a concept from object-oriented databases. It opens up
    interesting new posibilities of database design.
	For this example, capitals are also cities. We want an easy eay to list
	all cities including the capitals and to update/write to DB fast.
*/
CREATE TABLE cities (name text, population real, altitude int);
CREATE TABLE capitals(stats char(2)) INHERITS (cities);

INSERT INTO cities VALUES ('Las Vegas', 2000000, 2174);
INSERT INTO cities VALUES ('Mariposa',   200000, 1953);
INSERT INTO capitals VALUES ('Madison' ,   2000,  845, 'MA');

/*  To find the name of all cities, including capitals with altitude > 500
*/
SELECT name, altitude FROM cities WHERE altitude > 500;

/*
   name    | altitude
-----------+----------
 Las Vegas |     2174
 Mariposa  |     1953
 Madison   |      845
*/

 
/*  To find all the cities that are not state capitals at altitude > 500
*/
SELECT name, altitude FROM ONLY cities WHERE altitude > 500;

/*
   name    | altitude
-----------+----------
 Las Vegas |     2174
 Mariposa  |     1953
*/
