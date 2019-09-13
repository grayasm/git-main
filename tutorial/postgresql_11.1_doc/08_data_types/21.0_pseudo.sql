/*  Cap.8   Data Types
    8.21.   Pseudo-Types

    psql -d mytestdb -U pgmihai
    \i   21.0_pseudo.sql
    \?
    \qecho '\033[2J'
*/


/*      The PostgreSQL type system contains a number of special-purpose entries
        that are collectively called pseudo-types. A pseudo-type CANNOT be used
        as a column data type, but it can be used to declare a function's
        argument or result type.

        Functions coded in C can be declared to accept or return any of pseudo
        data types.
        Functions coded in procedural languages can use pseudo-types only as
        allowed by their implementation langagues.

        Table 8.25 Pseudo-Types

        Name                Description
        ------------------+-----------------------------------------------------
        any                 Indicates that a function accepts any input data type
        anyelement          .. a function accepts any data type
        anyarray            .. a function accepts any array data type
        anynonarray         .. a function accepts any non-array data type
        anyenum             .. a function accepts any anum data type
        anyrange            .. a function accepts any range data type
        cstring             .. a function accepts or returns a null-terminated C string
        internal            .. a function accepts or returns a server-internal data type
        language_handler    A procedural language call handler is declared to return
                            language_handler
        fdw_handler         A foreign-data wrapper handler is declared to return
                            fdw_handler
        index_am_handler    An index access method handler is declared to return
                            index_am_handler
        tsm_handler         A tablesample method handler is declared to return
                            tsm_handler
        record              Identifies a function taking or returning an unspecified
                            row type
        trigger             A trigger function is declared to return trigger
        event_trigger       An event trigger function is declared to return
                            event_trigger
        pg_ddl_command      Identifies a representation of DDL commands that is
                            available to event triggers
        void                Indicates that a function returns no value
        unknown             Identifies a not-yet-resolved type, e.g. of an
                            undecorated string literal
        opaque              An obsolete type name that formely served many of
                            the above purposes
*/
