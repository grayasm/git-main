/*  Chapter 5. Data Definition
    5.8. Inheritance

    psql -d mytestdb -U pgmihai
    \i 25_inheritance.sql
    \?
    \qecho '\033[2J'
*/


/*      In PostgreSQL, a table can inherit from zero or more tables, and a
        query can reference either all rows of a table or all rows of a table
        plus all its descendant tables. The later behavior is the default.
*/

/*      https://zaiste.net/table_inheritance_and_partitioning_with_postgresql
        Table Inheritance allows to extract a common set of columns into a
        parent, master table with children defining additional fields.
*/
DROP TABLE IF EXISTS articles_wo_tags, articles_w_tags, articles CASCADE;

CREATE TABLE articles (id        SERIAL,
                       title     VARCHAR,
                       content   TEXT);

CREATE TABLE articles_w_tags (tags  TEXT[]) INHERITS (articles);
CREATE TABLE articles_wo_tags () INHERITS (articles);

INSERT INTO articles_wo_tags (title, content)
       VALUES ('Title 1', 'Content 1'),
              ('Title 2', 'Content 2');

INSERT INTO articles_w_tags (title, content, tags)
       VALUES ('Title 3', 'Content 3', '{"tag_1", "tag_2"}'::text[]),
              ('Title 4', 'Content 4', '{"tag_2", "tag_3"}'::text[]);

SELECT * FROM articles_wo_tags;
/*
 id |  title  |  content
----+---------+-----------
  1 | Title 1 | Content 1
  2 | Title 2 | Content 2
(2 rows)
*/

SELECT * FROM articles_w_tags;
/*
 id |  title  |  content  |     tags
----+---------+-----------+---------------
  3 | Title 3 | Content 3 | {tag_1,tag_2}
  4 | Title 4 | Content 4 | {tag_2,tag_3}
(2 rows)
*/

/*      When querying the master table, the query references all rows of that
        master table plus all of its children tables; values from the common
        set of columns are displayed.
*/
SELECT * FROM articles;
/*
 id |  title  |  content
----+---------+-----------
  3 | Title 3 | Content 3
  4 | Title 4 | Content 4
  1 | Title 1 | Content 1
  2 | Title 2 | Content 2
(4 rows)
*/


/*      Changes performed on the master table are propagated to the children.
*/
UPDATE articles SET content = content || ' Changed';
SELECT * FROM articles_w_tags;
/*
 id |  title  |      content      |     tags
----+---------+-------------------+---------------
  3 | Title 3 | Content 3 Changed | {tag_1,tag_2}
  4 | Title 4 | Content 4 Changed | {tag_2,tag_3}
(2 rows)
*/
