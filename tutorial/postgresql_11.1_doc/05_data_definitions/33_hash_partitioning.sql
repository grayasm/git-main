/*  Chapter 5. Data Definition
    5.10. Partitioning
    5.10.2 Declarative Partitioning (PARTITION BY HASH)

    psql -d mytestdb -U pgmihai
    \i 33_hash_paritioning.sql
    \?
    \qecho '\033[2J'
*/


/*  http://pgdash.io/blog/partition-postgres-11.html

    Postgres 10 came with RANGE and LIST type partitions. In 11, we have HASH
    type paritions also. Hash type paritions distribute the rows based on the
    hash value of the partition key. The remainder of the hash value when
    divided by a specified integer is used to calculate which partition the row
    goes into (or can be found in).
*/

DROP TABLE IF EXISTS hp CASCADE;

CREATE TABLE hp (foo TEXT)
       PARTITION BY HASH (foo);

CREATE TABLE hp_0 PARTITION OF hp
       FOR VALUES WITH (MODULUS 3, REMAINDER 0);
CREATE TABLE hp_1 PARTITION OF hp
       FOR VALUES WITH (MODULUS 3, REMAINDER 1);
CREATE TABLE hp_2 PARTITION OF hp
       FOR VALUES WITH (MODULUS 3, REMAINDER 2);

INSERT INTO hp SELECT md5(v::text) FROM generate_series(0, 10000) v;

SELECT * FROM hp;
/*
               foo
----------------------------------
 c81e728d9d4c2f636f067f89cc14862c
 a87ff679a2f3e71d9181a67b7542122c
 1679091c5a880faf6fb5e6087eb1b2dc
...
*/
