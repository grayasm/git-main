/*  Chapter 5. Data Definition
    5.8. Schemas
    5.8.6. Usage Patterns

    psql -d mytestdb -U pgmihai
    \i   08.6_usage_patterns.sql
    \?
    \qecho '\033[2J'
*/


/*      The default configuration supports the following usage patterns:
        > All users access the 'public' schema implicitly. Recommended when
          there is only a single user or a few cooperating users in a database.

        > Create a schema for each user. The default 'search_path' starts with
          $user, which resolves to the user name. Therefore, if each user has a
          separate schema, they access their own schemas by default.
          You might also want to revoke access to 'public' schema (or drop it
          altogether), so users are truly constrained to their own schemas.

        > Install shared applications (tables to be used by everyone, additional
          functions provided by third parties, etc), into separate schemas.
          Remember to grant appropriate privileges to allow the other users
          to access them.
*/
