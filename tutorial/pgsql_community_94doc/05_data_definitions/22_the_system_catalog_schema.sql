/*  Chapter 5. Data Definition
    5.7. Schemas
    5.7.5. The System Catalog Schema

    psql -d mytestdb -U pgmihai
    \i 22_the_system_catalog_schema.sql
*/


/*      The default schema is named 'public'.
        Besides this each database contains a 'pg_catalog' schema, which
        contains system tables and all the built-in data types, functions
        and operators.

        These objects will always be findable. To overwrite them set
        'pg_catalog' at the end of the 'search_path'.

        The system table names begin with pg_, to avoid conflict with user
        tables.
*/

SELECT datname, datdba, encoding, datcollate, datctype
FROM pg_catalog.pg_database;

/*
  datname  | datdba | encoding | datcollate  |  datctype
-----------+--------+----------+-------------+-------------
 template1 |     10 |        6 | en_US.UTF-8 | en_US.UTF-8
 template0 |     10 |        6 | en_US.UTF-8 | en_US.UTF-8
 postgres  |     10 |        6 | en_US.UTF-8 | en_US.UTF-8
 mytestdb  |  16384 |        6 | en_US.UTF-8 | en_US.UTF-8
(4 rows)
*/
