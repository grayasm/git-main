/*  Cap.8   Data Types
    8.16.   Composite Types
    8.16.1  Declaration of Composite Types
    8.16.2  Constructing Composite Values
    8.16.3  Accessing Composite Types
    8.16.4  Modifying Composite Types
    8.16.5  Using Composite Types in Queries
    8.16.6  Composite Type Input and Output Syntax

    psql -d mytestdb -U pgmihai
    \i 8.16_composite.sql
    \?
    \qecho '\033[2J'
*/


/*      A composite type represents the structure of a row or record; it is
        essentially just a list of field names and their data types. PostgreSQL
        allows composite types to be used in many of the same ways that simple
        types can be used. For example, a column of a table can be declared
        to be of a composite type.
*/

DROP TYPE IF EXISTS inventory_item CASCADE;

CREATE TYPE inventory_item AS (
    name                TEXT,
    supplier_id         INTEGER,
    price               NUMERIC
    );

DROP TABLE IF EXISTS on_hand CASCADE;

CREATE TABLE on_hand (
    item                inventory_item,
    count               INTEGER
    );

INSERT INTO on_hand VALUES (ROW('fuzzy dice', 42, 1.99), 1000);

DROP FUNCTION IF EXISTS price_extension(inventory_item, integer) CASCADE;

CREATE FUNCTION price_extension (inventory_item, integer) RETURNS
    NUMERIC
    AS 'SELECT $1.price * $2'
    LANGUAGE SQL;
