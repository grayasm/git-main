*
*  Chapter 2 The SQL Language

   Introduction           ex: psql -d mydatabase -U pguser OR \i test.sql
   Concepts               ex: relational DB management system (RDBMS)
   Create New Table       ex: CREATE TABLE t(id SERIAL, name TEXT);
   Populate With Rows     ex: INSERT INTO t(name) VALUES ('Abigail Larsen);
   Querying a Table       ex: SELECT * FROM t WHERE id < 100 ORDER BY id DESC;
   Joins Between Tables   ex: SELECT * FROM u INNER JOIN t ON (u.id = t.id);
   Aggregage Functions    ex: SELECT max(id) FROM t;
   Updates                ex: UPDATE t SET name='Bon Jovi' WHERE id=500;
   Deletions              ex: DELETE FROM t WHERE name = 'Bon Jovi';
