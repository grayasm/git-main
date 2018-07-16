/*  Chapter 5. Data Definition
    5.9. Partitioning
    5.9.2. Implementing paritioning

    psql -d mytestdb -U pgmihai
    \i 26_implementing_partitioning.sql
*/

/*      Partitioning refers to splitting what is logically one large table into
        smaller physical pieces. Query performance can be improved dramatically
        when heavily accessed rows of the table are in a single partition or a
        small number of partitions. The partition reduces the index size making
        it more likely that the heavily-used parts of the indexes fit in memory.

        The benefits are worthwile when a table is very large, which is when
        the size of the table exceeds the physical memory of the database server.

        PostgreSQL supports paritioning via table inheritance. Each parition
        must be created as a child table of a SINGLE parent table. The parent
        table itself is normally empty; it exists just to represent the entire
        data set.
*/
