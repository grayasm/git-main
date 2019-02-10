/*  Chapter 5. Data Definition
    5.11. Foreign data.

    psql -d mytestdb -U pgmihai
    \i 34_foreign_data.sql
    \?
    \qecho '\033[2J'
*/


/*
        PostgreSQL implements portions of the SQL/MED specification, allowing
        you to access data that resides outside PostgreSQL using regular SQL
        queries.
        Foreign data wrapper libraries are available as 'contrib' modules.
        To access foreign data you need to create a foreign server object,
        which defines how to connect to a particular external data source
        according to the set of options used by its supporting foreign data
        wrapper.
        Then you need to create one or more foreign tables, which define the
        structure of the remote data. A foreign table can be used in queries
        just like a normal table, but a foreign table has no storage in the
        PostgreSQL server. Whenever it is used, PostgreSQL asks the foreign
        data wrapper to fetch data from the external source, or transmit data
        to the external source in the case of update commands.
*/
