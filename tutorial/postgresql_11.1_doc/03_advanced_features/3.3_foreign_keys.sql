/*  Cap.3 Advanced Features
    3.3 Foreign Keys

    Run with:
    psql -d mytestdb -U pgmihai
    \i 3.3_foreign_keys.sql
    \?
    \qecho '\033[2J'
*/


/*  You want to make sure that no one can insert rows in the weather table that
    do not have a matching entry in the cities table. This is calling
    maintaining the REFERENTIAL INTEGRITY of your data.
    The new declaration of the tables would look like this:
*/
DROP VIEW  IF EXISTS myview;    -- drop old view and tables
DROP TABLE IF EXISTS cities;
DROP TABLE IF EXISTS weather;


CREATE TABLE cities (
       city         varchar(80) primary key,
       location     point
);

CREATE TABLE weather (
       city          varchar(80) references cities(city),
       temp_lo       int,
       temp_hi       int,
       prcp          real,
       date          date
);

INSERT INTO weather VALUES ('Berkeley', 45, 53, 0.0, '1994-11-28');
/*  DETAIL:  Key (city)=(Berkeley) is not present in table "cities".  */



-- clean up
DROP VIEW myview;
DROP TABLE cities;
DROP TABLE weather;
