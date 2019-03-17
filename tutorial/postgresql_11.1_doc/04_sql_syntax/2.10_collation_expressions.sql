/*  Chapter 4.2 Value Expressions
    4.2.10 Collation Expressions

    psql -d mytestdb -U pgmihai
    \i   2.10_collation_expressions.sql
    \?
    \qecho '\033[2J'
*/


/*  The COLLATE clause overrides the collation of an expression. It is appended
    to the expression it applies to:
    expr COLLATE collation

    Collation is used to sort strings (text), for example by alphabetic order,
    whether or not case matters, how to deal with letters that have accents,etc.
    COLLATE "C" tells the database not to use collation at all. One might use
    this if they were designing a database to hold data in different languages.

    The results of comparisons between strings depends on LC_CTYPE. In practice,
    the most visible effect is the sort order. 'C' as LC_CTYPE means that the
    byte order is going to drive comparisons, whereas a real locale means that
    cultural rules will drive the comparisons.

    An example with french names, executed from inside an UTF-8 database:
*/

DROP TABLE IF EXISTS my_table CASCADE;
CREATE TABLE my_table (name varchar);
INSERT INTO my_table VALUES ('bernard'),
                            ('bérénice'),
                            ('béatrice'),
                            ('boris');

SELECT name FROM my_table ORDER BY name COLLATE "fr_FR";

/*
   name
----------
 béatrice
 bérénice
 bernard
 boris
*/

-- this differs from what happens with a 'C' locale:
SELECT name FROM my_table ORDER BY name COLLATE "C";

/*
   name
----------
 bernard
 boris
 béatrice
 bérénice
*/
