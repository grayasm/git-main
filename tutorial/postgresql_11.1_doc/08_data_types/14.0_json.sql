/*  Cap.8   Data Types
    8.14.   JSON Types
    8.14.1  JSON Input and Ouput Syntax
    8.14.2  Designing JSON documents effectively
    8.14.3  jsonb Containment and Existance
    8.14.4  jsonb Indexing
    8.14.5  Transforms

    psql -d mytestdb -U pgmihai
    \i   14.0_json.sql
    \?
    \qecho '\033[2J'
*/


/*      JSON data types are for storing JSON (JavaScript Object Notation) data,
        as specified in RFC 7159. Such data can also be stored as text, but
        the JSON data types have the advantage of enforcing that each stored
        value is valid according to the JSON rules. There are also assorted
        JSON-specific functions and operators available for data stored in
        these data types.

        There are JSON data types: json and jsonb.

        json data type stores an exact copy of the input text;

        jsonb data is stored in a decomposed binary format that makes it
        slightly slower to input due to added conversion overhead, but
        significantly faster to process, since no reparsing is needed.
        jsonb also supports indexing, which can be a significant advantage.

        JSON primitive      PostgreSQL type    Notes
        -----------------+-------------------+-------------------------------
        string              text               \u0000 is disallowed as are
                                               non-ASCII Unicode escapes if
                                               database encoding is not UTF-8
        number              numeric            NaN and infinity values are
                                               disallowed
        boolean             boolean            Only lowercase true and false
                                               spellings are accepted
        null                (none)             SQL NULL is a different concept
        ----------------------------------------------------------------------
*/

SELECT '5'::json;  -- simple scalar/primitive value
/*
 json
------
 5
(1 row)
*/

SELECT '[1, 2, "foo", null]'::json; -- array of zero or more elements
/*
        json
---------------------
 [1, 2, "foo", null]
(1 row)
*/

SELECT '{"bar": "baz", "balance": 7.77, "active": false}'::json; -- "key":value
/*
                       jsos
--------------------------------------------------
 {"bar": "baz", "balance": 7.77, "active": false}
(1 row)
*/

SELECT '{"foo": [true, "bar"], "tags": {"a":1, "b":null}}'::json; -- nested objs
/*
                       json
---------------------------------------------------
 {"foo": [true, "bar"], "tags": {"a":1, "b":null}}
(1 row)
*/

SELECT '{"bar":"baz", "balance":7.77, "active":false}'::json;
/*
                     json
-----------------------------------------------
 {"bar":"baz", "balance":7.77, "active":false}
(1 row)
*/

SELECT '{"bar":"baz", "balance":7.77, "active":false}'::jsonb;
/*
                      jsonb
--------------------------------------------------
 {"bar": "baz", "active": false, "balance": 7.77}
(1 row)
*/

SELECT '{"reading":1.230e-5}'::json, '{"reading":1.230e-5}'::jsonb;
/*
         json         |          jsonb
----------------------+-------------------------
 {"reading":1.230e-5} | {"reading": 0.00001230}
(1 row)
*/


/*      Testing containment is an important capability of jsonb.
        There is no parallel set of facilities for the json type.
        Containment tests whether one jsonb document has contained within it
        another one. These examples return true except as noted.
*/


SELECT '"foo"'::jsonb @> '"foo"'::jsonb;                        -- t
SELECT '[1, 2, 3]'::jsonb @> '[1, 3]'::jsonb;                   -- t
SELECT '[1, 2, 3]'::jsonb @> '[3, 1]'::jsonb;                   -- t
SELECT '[1, 2, 3]'::jsonb @> '[1, 2, 2]'::jsonb;                -- t
SELECT '{"product":"PostgreSQL", "version":9.4, "jsonb":true}'::jsonb @>
       '{"version":9.4}'::jsonb;                                -- t

SELECT '[1, 2, [1, 3]]'::jsonb @> '[1, 3]'::jsonb;              -- false
SELECT '[1, 2, [1, 3]]'::jsonb @> '[[1, 3]]'::jsonb;            -- t
SELECT '{"foo":{"bar":"baz"}}'::jsonb @> '{"bar":"baz"}'::jsonb;-- false
SELECT '{"foo":{"bar":"baz"}}'::jsonb @> '{"foo":{}}'::jsonb;   -- t

SELECT '["foo", "bar"]'::jsonb @> '"bar"'::jsonb;               -- t
SELECT '"bar"'::jsonb @> '["bar"]'::jsonb;                      -- false

SELECT '["foo", "bar", "baz"]'::jsonb ? 'bar';                  -- t
SELECT '{"foo": "bar"}'::jsonb ? 'foo';                         -- t
SELECT '{"foo": "bar"}'::jsonb ? 'bar';                         -- f
SELECT '{"foo": {"bar": "baz"}}'::jsonb ? 'bar';                -- f

SELECT '"foo"'::jsonb ? 'foo';                                  -- t


/*      jsonb Indexing.
        GIN indexes can be used to efficiently search for keys or key/value
        pairs occuring within a large number of jsonb documents (datums).
*/
DROP TABLE IF EXISTS api CASCADE;

CREATE TABLE api (id SERIAL, jdoc  JSONB);

CREATE INDEX idxginp ON api USING GIN (jdoc jsonb_path_ops);

INSERT INTO api(jdoc) VALUES
       ('{'
        '   "guid": "9c36adc1-7fb5-4d5b-83b4-90356a46061a", '
        '   "name": "Angela Barton",                        '
        '   "is_active": true,                              '
        '   "company": "Magnafone",                         '
        '   "address": "178 Howard Place, Gulf, Washington, 702",'
        '   "registered": "2009-11-07T08:53:22 +08:00",     '
        '   "latitude": 19.793713,                          '
        '   "longitude": 86.513373,                         '
        '   "tags": [                                       '
        '           "enim",                                 '
        '           "aliquip",                              '
        '           "qui"                                   '
        '   ]                                               '
        '}'::jsonb);

SELECT jdoc->'guid', jdoc->'name' FROM api WHERE jdoc @>
       '{"company":"Magnafone"}';
/*
                ?column?                |    ?column?
----------------------------------------+-----------------
 "9c36adc1-7fb5-4d5b-83b4-90356a46061a" | "Angela Barton"
(1 row)
*/

SELECT jdoc->'guid', jdoc->'name' FROM api WHERE jdoc->'tags' ? 'qui';
/*
                ?column?                |    ?column?
----------------------------------------+-----------------
 "9c36adc1-7fb5-4d5b-83b4-90356a46061a" | "Angela Barton"
(1 row)
*/

CREATE INDEX idxgintags ON api USING GIN ((jdoc->'tags'));

SELECT jdoc->'guid', jdoc->'name' FROM api WHERE jdoc @> '{"tags":["qui"]}';
/*
                ?column?                |    ?column?
----------------------------------------+-----------------
 "9c36adc1-7fb5-4d5b-83b4-90356a46061a" | "Angela Barton"
(1 row)
*/
