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

SELECT price_extension(item, 10) FROM on_hand;
/*
 price_extension
-----------------
           19.90
(1 row)
*/


/*      To write a composite value as a literal constant, enclose the field
        values within parantheses and separate them by commas. You can put
        double quotes around any field value, and must do so if it contains
        commas or parantheses.

        '(val1 , val2 , ...)'
*/
INSERT INTO on_hand VALUES ('("fives dior", 42, 9.99)', 999);
INSERT INTO on_hand VALUES ('("fanti dent", 42,)', 888); --NULL field
INSERT INTO on_hand VALUES ('("",42,)', 777); -- empty string and NULL field


/*      The ROW expression syntax can also be used to construct composite values.
        In most cases this is considerably simpler to use than the string-literal
        syntax since you don't have to worry about multiple layers of quoting.
*/
INSERT INTO on_hand VALUES (ROW('fichu dory', 42, 6.99), 665.9);
INSERT INTO on_hand VALUES (ROW('', 42, NULL), 555);

/*      The ROW keyword is actually optional as long as you have more than one
        field in the expression, so these can be simplified to:
*/
INSERT INTO on_hand VALUES (('foxie dogs', 42, 4.99), 444);
INSERT INTO on_hand VALUES (('', 42, NULL), 333);

SELECT * FROM on_hand;
/*
          item          | count
------------------------+-------
 ("fuzzy dice",42,1.99) |  1000
 ("fives dior",42,9.99) |   999
 ("fanti dent",42,)     |   888
 ("",42,)               |   777
 ("fichu dory",42,6.99) |   666
 ("",42,)               |   555
 ("foxie dogs",42,4.99) |   444
 ("",42,)               |   333
(8 rows)
*/


/*      To access a field of composite column, one writes a dot and the field
        name, much like selecting a field from a table name. You have to use
        parantheses to keep from confusing the parser.
*/
SELECT item.name FROM on_hand WHERE item.price > 9.99;
--ERROR because item is not a table

SELECT (item).name FROM on_hand WHERE (item).price > 5.99;
/*
    name
------------
 fives dior
 fichu dory
(2 rows)
*/

SELECT (on_hand.item).name FROM on_hand WHERE (on_hand.item).price > 5.99;
/*
    name
------------
 fives dior
 fichu dory
(2 rows)
*/


/*      Here are some examples of the proper syntax for inserting and updating
        composite columns.
*/
INSERT INTO on_hand(item) VALUES (('flown drip',22, 16.6));
UPDATE on_hand SET item = ROW('frore dogy',0,0) WHERE count IS NULL;
UPDATE on_hand SET item.supplier_id = (item).supplier_id - 1 WHERE count IS NULL;
INSERT INTO on_hand (item.supplier_id, item.price) VALUES (-1, 0);

SELECT * FROM on_hand;
/*
          item          | count
------------------------+-------
 ("fuzzy dice",42,1.99) |  1000
 ("fives dior",42,9.99) |   999
 ("fanti dent",42,)     |   888
 ("",42,)               |   777
 ("fichu dory",42,6.99) |   666
 ("",42,)               |   555
 ("foxie dogs",42,4.99) |   444
 ("",42,)               |   333
 ("frore dogy",-1,0)    |
 (,-1,0)                |
(10 rows)
*/

--clean up a bit;
DELETE FROM on_hand WHERE (item).price = 0 OR (item).price IS NULL;



/*      There are various special syntax rules and behaviors associated with
        composite types in queries. These rules provide useful shortcuts, but
        can be confusing if you don't know the logic behind them.
        In PostgreSQL, a reference to a table name (or alias) in a query is
        effectively a reference to the composite value of the table's current
        row.
*/
SELECT c FROM (SELECT item FROM on_hand) AS c;
/*
              c
------------------------------
 ("(""fuzzy dice"",42,1.99)")
 ("(""fives dior"",42,9.99)")
 ("(""fichu dory"",42,6.99)")
 ("(""foxie dogs"",42,4.99)")
(4 rows)
*/

SELECT c.* FROM (SELECT item FROM on_hand) AS c;
/*
          item
------------------------
 ("fuzzy dice",42,1.99)
 ("fives dior",42,9.99)
 ("fichu dory",42,6.99)
 ("foxie dogs",42,4.99)
(4 rows)
*/

SELECT (c.item).name, (c.item).supplier_id, (c.item).price FROM (SELECT item FROM on_hand) AS c;
/*
    name    | supplier_id | price
------------+-------------+-------
 fuzzy dice |          42 |  1.99
 fives dior |          42 |  9.99
 fichu dory |          42 |  6.99
 foxie dogs |          42 |  4.99
(4 rows)
*/

DROP FUNCTION IF EXISTS return_item(supplierId INTEGER) CASCADE;

CREATE FUNCTION return_item(supplierId INTEGER)
       RETURNS SETOF on_hand
       AS
       $$
            SELECT * FROM on_hand WHERE (item).supplier_id = supplierId;
       $$
LANGUAGE 'sql' VOLATILE;

SELECT * FROM return_item(42);
/*
          item          | count
------------------------+-------
 ("fuzzy dice",42,1.99) |  1000
 ("fives dior",42,9.99) |   999
 ("fichu dory",42,6.99) |   666
 ("foxie dogs",42,4.99) |   444
(4 rows)
*/

SELECT (item).name, (item).supplier_id, (item).price FROM return_item(42);
/*
    name    | supplier_id | price
------------+-------------+-------
 fuzzy dice |          42 |  1.99
 fives dior |          42 |  9.99
 fichu dory |          42 |  6.99
 foxie dogs |          42 |  4.99
(4 rows)
*/

SELECT (item).name, (item).supplier_id, (item).price
       FROM return_item(42)
       ORDER BY (item).price;

/*
    name    | supplier_id | price
------------+-------------+-------
 fuzzy dice |          42 |  1.99
 foxie dogs |          42 |  4.99
 fichu dory |          42 |  6.99
 fives dior |          42 |  9.99
(4 rows)
*/

SELECT (item).name, (item).price
       FROM return_item(42)
       ORDER BY ROW((item).name, (item).price);

/*
    name    | price
------------+-------
 fichu dory |  6.99
 fives dior |  9.99
 foxie dogs |  4.99
 fuzzy dice |  1.99
(4 rows)
*/

-- or using a row constructor with the key word ROW ommitted
SELECT (item).name, (item).price
       FROM return_item(42)
       ORDER BY ((item).name, (item).price);
/*
    name    | price
------------+-------
 fichu dory |  6.99
 fives dior |  9.99
 foxie dogs |  4.99
 fuzzy dice |  1.99
(4 rows)
*/
