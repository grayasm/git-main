/*  Cap.2 The SQL Language,
    2.3 Creating a new table.

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 01_create_new_table.sql

    If table already exists, delete it with
    DROP TABLE <table_name>;
*/

CREATE TABLE weather(
       city        varchar(80),    -- string up to 80 chars
       temp_lo     int,        -- the normal integer type
       temp_hi     int,
       prcp        real,       -- single precision floating-point
       date        date        -- field date of type date :)
);


/*  The second example will store cities and their associated
    geographical location:
*/
CREATE TABLE cities(
       name        varchar(80),
       location    point       -- is PostgreSQL specific data type
);
