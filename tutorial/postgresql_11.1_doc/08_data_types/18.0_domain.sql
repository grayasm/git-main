/*  Cap.8   Data Types
    8.18.   Domain Types

    psql -d mytestdb -U pgmihai
    \i 8.18_domain.sql
    \?
    \qecho '\033[2J'
*/


/*      A domain is a user-defined data type that is based on another underlying
        type. Optionally, it can have constraints that restrict its valid values
        to a subset of what the underlying type would allow. Otherwise, it
        behaves like the underlying type - any operators or function that can be
        applied to the underlying type will work on the domain type.
*/

DROP DOMAIN IF EXISTS posint CASCADE;
DROP TABLE IF EXISTS positives CASCADE;

CREATE DOMAIN posint AS integer CHECK (VALUE > 0);
CREATE TABLE positives (id posint);

INSERT INTO positives VALUES (1); -- works
INSERT INTO positives VALUES (-1); --fails
--ERROR:  value for domain posint violates check constraint "posint_check"


/*      When an operator or function of the underlying type (integer) is applied
        to a domain value, the domain (posint) is automatically down-casted to
        the underlying (integer) type. Here is how to cast the result back to
        underlying type and cause the domain's constraints to be rechecked.
*/
SELECT (positives.id -1) FROM positives;
/*
 ?column?
----------
        0
(1 row)
*/

SELECT (positives.id -1)::posint FROM positives;
--ERROR:  value for domain posint violates check constraint "posint_check"
