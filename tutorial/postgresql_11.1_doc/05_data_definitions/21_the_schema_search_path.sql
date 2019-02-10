/*  Chapter 5. Data Definition
    5.7. Schemas
    5.7.3. The Schema Search Path.

    psql -d mytestdb -U pgmihai
    \i 21_the_schema_search_path.sql
    \?
    \qecho '\033[2J'
*/

/*      The system determines the table by following the 'search path' which is
        a list of schemas. The first matching table is considered.
        If there is no match in the 'search path', an error is reported, even if
        matching table names exist in other schema in the database.
*/

SHOW search_path;

/*
  search_path
----------------
 "$user",public
(1 row)
*/

/*      To put another schema first in the 'search path' use: */
DROP SCHEMA myschema CASCADE;
CREATE SCHEMA myschema;
SET search_path TO myschema,public;

SHOW search_path;

/*
   search_path
------------------
 myschema, public
(1 row)
*/

/*      Create a table using unqualified name in default 'myschema' schema. */
DROP TABLE IF EXISTS products CASCADE;

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

INSERT INTO products VALUES
        (1, 'left door', 9.99),
        (2, 'right door', 9.99),
        (3, 'front shield', 11.50);

SELECT * FROM myschema.products;
/*
 product_no |     name     | price
------------+--------------+-------
          1 | left door    |  9.99
          2 | right door   |  9.99
          3 | front shield | 11.50
(3 rows)
*/

/*      Clean up. */
SET search_path TO public;
