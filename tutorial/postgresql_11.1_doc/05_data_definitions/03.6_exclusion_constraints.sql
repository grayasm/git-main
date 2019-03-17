/*  Chapter 5. Data Definition
    5.3.6. Exclusion Constraints

    psql -d mytestdb -U pgmihai
    \i   03.6_exclusion_constraints.sql
    \?
    \qecho '\033[2J'
*/

/*      Exclusion constraints ensure that if any rows are compared on the
        specified columns or expressions using the specified operators,
        at least one of these operator comparisons will return false or null.

        These guy here explains it better:
        http://nathanmlong.com/2016/01/protect-your-data-with-postgresql-constraints

        What data is valid for a row, considering the rows that already exist
        in this table?
*/

DROP TABLE IF EXISTS test;
CREATE TABLE test (
        user_id        INTEGER,
        start_end      TSTZRANGE,
        EXCLUDE USING gist (start_end WITH &&)
        );

INSERT INTO test VALUES
        (11, tstzrange('2018-05-24 18:16:00', '2018-05-24 18:17:00')),
        (10, tstzrange('2018-06-24 18:16:00', '2018-06-24 18:17:00'));

INSERT INTO test VALUES
        (11, tstzrange('2018-05-24 18:16:20', '2018-05-24 18:19:00'));

/*
psql:08_exclusion_constraints.sql:32: ERROR:  conflicting key value violates
     exclusion constraint "test_start_end_excl"
DETAIL:
Key (start_end)=(["2018-05-24 18:16:20+02","2018-05-24 18:19:00+02"))
conflicts with existing key
    (start_end)=(["2018-05-24 18:16:00+02","2018-05-24 18:17:00+02")).
*/
