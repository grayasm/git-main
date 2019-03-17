/*  Chapter 5. Data Definition
    5.10.1. Overview

    psql -d mytestdb -U pgmihai
    \i   10.1_table_partitioning_overview.sql
    \?
    \qecho '\033[2J'
*/



/*  Partitioning refers to splitting what is logically one large table into
    smaller physical pieces. Query performance can be improved dramatically
    when heavily accessed rows of the table are in a single partition or a
    small number of partitions. The partition reduces the index size making
    it more likely that the heavily-used parts of the indexes fit in memory.

    The benefits are worthwile when a table is very large, which is when
    the size of the table exceeds the physical memory of the database server.

    PostgreSQL offers two types of partitioning:
    --------------------------------------------
    1) Declarative paritioning, first released in version 10
    2) Using table inheritance, released before version 10

    The (1) Declarative partitioning offers built-in support for the following
    forms of partitioning:
    ----------------------
    Range: the table is partitioned into "ranges" defined by a key column or set
           of columns, with no overlap between the ranges of values assigned to
           different partitions.
    List : the table is partitioned by explicitly listing which key values
           appear in each partition
    Hash : the table is partitioned by specifying a modulus and a remainder for
           each partition. Each partition will hold the rows for which the hash
           value of the partition key devided by the specified modulus will
           produce the specified remainder
*/
