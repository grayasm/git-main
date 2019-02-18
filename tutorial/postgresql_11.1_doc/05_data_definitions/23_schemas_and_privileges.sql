/*  Chapter 5. Data Definition
    5.8. Schemas
    5.8.4. Schemas and Privileges

    Run as user=postgres

    psql -d mytestdb -U postgres
    \i 23_schemas_and_privileges.sql
    \?
    \qecho '\033[2J'
*/


/*  By default, users cannot access any objects in schemas they do not own.
    The owner of the schema must:
       > GRANT USAGE privilege to allow users access the objects in the schema
       > GRANT CREATE privilege to allow users create objects in the schema

    Everyone has CREATE and USAGE privileges on the schema "public".

    To remove a usage pattern the postgres admin can run:
    REVOKE CREATE ON SCHEMA public FROM PUBLIC;
    The first public is the schema, the second PUBLIC means every user.

    See previous file "privileges" for more examples on GRANT and REVOKE.
*/


-- user pgmihai
SET ROLE pgmihai;
CREATE SCHEMA myschema;
DROP TABLE IF EXISTS myschema.products CASCADE;

-- user joe gets access to myschema
SET ROLE postgres;
DROP ROLE IF EXISTS joe;
CREATE ROLE joe WITH PASSWORD 'NotImportant';
GRANT CREATE, USAGE ON SCHEMA myschema TO joe;
SET ROLE joe;

-- user joe
CREATE TABLE myschema.products (
       product_no    INTEGER  PRIMARY KEY,
       name          TEXT,
       price         NUMERIC);

INSERT INTO myschema.products(product_no,name,price) VALUES
       (1, 'p1', 99.9),
       (2, 'p2', 88.8),
       (3, 'p3', 77.7),
       (4, 'p4', 66.6),
       (5, 'p5', 10.0);

-- user pgmihai gets access to joe's table
SET ROLE postgres;
GRANT SELECT,UPDATE ON ALL TABLES IN SCHEMA myschema TO pgmihai;
SET ROLE pgmihai;

-- user pgmihai
UPDATE myschema.products SET price = 55.5 WHERE name = 'p5'; -- UPDATE 1


-- user pgmihai gets access revoked
SET ROLE postgres;
REVOKE SELECT,UPDATE ON ALL TABLES IN SCHEMA myschema FROM pgmihai;
SET ROLE pgmihai;

-- user pgmihai with no privileges on joe's table
UPDATE myschema.products SET price = 44.4 WHERE name = 'p5';
-- ERROR:  permission denied for table products

-- clean up
SET ROLE postgres;
DROP TABLE IF EXISTS myschema.products CASCADE;
DROP SCHEMA IF EXISTS myschema;
DROP ROLE joe;
