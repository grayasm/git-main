*
*  Chapter 5 Data Definition

   Table Basics           ex: rows order is not guaranteed
   Default Values         ex: CREATE TABLE t (price numeric DEFAULT 9.99, ..
   Check Constraints      ex: CREATE TABLE t (price numeric CHECK (price>0), ..
   NotNull Constraints    ex: CREATE TABLE t (price numeric NOT NULL, ..
   Unique Contraints      ex: CREATE TABLE t (product_no integer UNIQUE, ..
   Primary Keys           ex: CREATE TABLE t (product_no integer PRIMARY KEY, ..
   Foreign Keys           ex: CREATE TABLE t (product_no integer REFERENCES t2 (product_no), ..
   Exclusion Contraints   ex: CREATE TABLE t (.., EXCLUDE USING gist (start_end WITH &&), ..
   System Columns         ex: CREATE TABLE t (..) WITH OIDS;

   Table                  ex:
     Add column           ex: ALTER TABLE t ADD COLUMN desc text;
     Remove column        ex: ALTER TABLE t DROP COLUMN desc;
     Add contraint        ex: ALTER TABLE t ADD CHECK(name <> '');
     Remove contraint     ex: ALTER TABLE t DROP CONSTRAINT by_name;
     Change col def val   ex: ALTER TABLE t ALTER COLUMN p SET DEFAULT 7.77;
     Change col data type ex: ALTER TABLE t ALTER COLUMN p TYPE numeric(10,2);
     Rename column        ex: ALTER TABLE t RENAME COLUMN c0 TO c1;
     Rename table         ex: ALTER TABLE t RENAME TO x;

   Privileges             ex: GRANT UPDATE ON t TO joe;
   Schemas                ex:
     Create schema        ex: CREATE SCHEMA s; CREATE TABLE s.t (...
     The Public Schema    ex: CREATE TABLE public.t(..); INSERT INTO public.t ..
     The Search Path      ex: SHOW search_path; SET search_path TO public,s;
     The Privileges       ex:
     The System Catalog   ex: SELECT datname FROM pg_catalog.pg_database;
     Usage Patterns       ex: create a schema per user with search_path=$user
     Portability          ex: no 'public' schema in SQL standard
   Ineritance             ex: CREATE TABLE t2 (..) INHERITS (t1);
   Paritioning            ex: CREATE TABLE ty2018 (CHECK(..)) INHERITS (t);
     Foreign data         ex: SQL/MED specs, foreign server, foreign tables,..
     Other db objects     ex: views, functions, data types, triggers
     Dependency tracking  ex: DROP TABLE t RESTRICT; DROP TABLE t CASCADE;
