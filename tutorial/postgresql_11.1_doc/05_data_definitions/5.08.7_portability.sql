/*  Chapter 5. Data Definition
    5.8. Schemas
    5.8.7. Portability

    psql -d mytestdb -U pgmihai
    \i 26_portability.sql
    \?
    \qecho '\033[2J'
*/


/*      > Objects in the same schema being owned by different users does not
          exist in SQL standard.

        > Some implementations does not allow to create schemas that have a
          different name than their owner. These are database systems with basic
          schema support specified in the standard. The qualified names really
          consist of 'username.tablename'

        > There is no concept of a 'public' schema in SQL standard.
          For conformance you should not use the 'public' schema.

        > Some SQL database systems might not implement schemas at all.
*/
