/*  Chapter 5. Data Definition
    5.7. Schemas
    5.7.1. Creating a Schema

    psql -d mytestdb -U pgmihai
    \i 19_creating_a_schema.sql
    \?
    \qecho '\033[2J'

    \dn -- to list all schemas in a database
*/

/*      A database contains one or more named schemas.
        PostgreSQL default schema is named 'public'.
        In a schema there are objects like:
        Collations, Domains, Functions, Sequences, Tables, Views, etc.

        The same object NAME can be used in different schemas without conflict.
        Schemas are analogous to directories at the operating system level,
        except that schemas cannot be nested.

        > Schemas allow many users to use one database without interfering with
          each other. Inside the database, each user will use his own schema
          with his own tables inside.

        > Schemas organizes database objects into logical groups to make them
          more manageable.

        > Schemas can contain 3rd-party applications so they do not collide
          with names of other objects.
*/


/*      To create a schema use: */
CREATE SCHEMA myschema;

/*      Create a table inside the schema using a qualified name: */
DROP TABLE IF EXISTS myschema.products CASCADE;

CREATE TABLE myschema.products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

/*      Drop a schema if it's empty.
psql:19_creating_a_schema.sql:44: ERROR:  cannot drop schema myschema because other objects depend on it
*/
DROP SCHEMA myschema;

/*      Drop a schema including all contained objects. */
DROP SCHEMA myschema CASCADE;

/*      Create a schema that will be owned by someone else.
psql:19_creating_a_schema.sql:50: ERROR:  role "pgmihai2" does not exist
*/
CREATE SCHEMA schemaname AUTHORIZATION pgmihai2;
