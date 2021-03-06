/*  Cap.8   Data Types
    8.12.   UUID Type

    psql -d mytestdb -U pgmihai
    \i   12.0_uuid.sql
    \?
    \qecho '\033[2J'
*/


/*      The data type uuid stores Universally Unique Identifiers (UUID) as
        defined by RFC 4122, ISO IEC 9834-8:2005, and related standards.
        This identifier is a 128-bit quantity that is generated by an algorithm
        chosen to make it very unlikely that the same identifier will be
        generated by anyone else in the known universe using the same algorithm.
*/


DROP TABLE IF EXISTS uuids CASCADE;
CREATE TABLE uuids (id SERIAL, uuid_ UUID);

/*     PostgreSQL accepts the following forms for input. */
INSERT INTO uuids(uuid_) VALUES ('a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11'),
                                ('A0EEBC99-9C0B-4EF8-BB6D-6BB9BD380A11'),
                                ('{a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11}'),
                                ('a0eebc999c0b4ef8bb6d6bb9bd380a11'),
                                ('a0ee-bc99-9c0b-4ef8-bb6d-6bb9-bd38-0a11'),
                                ('{a0eebc99-9c0b4ef8-bb6d6bb9-bd380a11}');

/*      Output is always in the standard form. */
SELECT * FROM uuids;
/*
 id |                uuid_
----+--------------------------------------
  1 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
  2 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
  3 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
  4 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
  5 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
  6 | a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11
(6 rows)
*/
