/*  Chapter 5. Data Definition
    5.10.1. Overview

    psql -d mytestdb -U pgmihai
    \i 28_table_partitioning_overview.sql
    \?
    \qecho '\033[2J'
*/



/*  Partitioning refers to splitting what is logically one very large table into
    smaller physical pieces. Partitioning can provide several benefits:
      > dramatically improved performance when most rows are in a single
        partition
      > partitioning reduces the index size making it more likely to fit in
        memory
      > queries or updates across a single partition are faster due to a
        sequential scan of that partition compared with random access reads
        scattered across the whole table
      > bulk loads and deletes can be acomplished by adding or removing
        partitions
      > seldom used data can be migrated data to cheaper and slower storage
        media

    Partitioning types:
    -------------------
    Declarative - first in PostgreSQL-10
    Inheritance - existed before PostgreSQL-10

    Forms of partitioning:
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
