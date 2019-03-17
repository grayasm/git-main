/*  Cap.7   Queries
    7.3     Select Lists
    7.3.1   SelectList Items

    psql -d mytestdb -U pgmihai
    \i   3.1_select.sql
    \?
    \qecho '\033[2J'
*/


/*      A select list is comma separated list of value expressions. */


DROP TABLE IF EXISTS pers,finc CASCADE;
CREATE TABLE pers (id INTEGER, nume TEXT, job TEXT);
CREATE TABLE finc (id INTEGER, salary NUMERIC);

INSERT INTO pers VALUES (1, 'Mi Hia', 'developer'),
                        (2, 'Ni Hao', 'developer'),
                        (3, 'Ji Tia', 'developer');
INSERT INTO finc VALUES (1, 1010), (2, 1020), (3, 1030); -- average=1020


/* SELECT examples. */
SELECT * FROM pers;
SELECT id, nume, job FROM pers;
SELECT a.id, a.nume, a.job FROM pers AS a;
SELECT pers.nume, pers.job, finc.salary FROM pers INNER JOIN finc USING(id);
SELECT pers.*, finc.salary FROM pers INNER JOIN finc USING(id);
