/*  Chapter 5. Data Definition
    5.7. Schemas
    5.7.2. The Public Schema

    psql -d mytestdb -U pgmihai
    \i 20_the_public_schema.sql
    \?
    \qecho '\033[2J'

    \dn -- to list all schemas in a database
*/

/*      By default, tables created without specifying the schema name, are
        automatically put into a schema named "public".
        Every new database contains such a schema.
*/

DROP TABLE IF EXISTS public.products CASCADE;

CREATE TABLE public.products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

INSERT INTO public.products VALUES
        (1, 'left door', 9.99),
        (2, 'right door', 9.99),
        (3, 'front shield', 11.50);

SELECT * from public.products;

/*
 product_no |     name     | price
------------+--------------+-------
          1 | left door    |  9.99
          2 | right door   |  9.99
          3 | front shield | 11.50
(3 rows)
*/
