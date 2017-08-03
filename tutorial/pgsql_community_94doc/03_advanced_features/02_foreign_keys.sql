/*  Cap.3 Advanced Features
    3.3 Foreign Keys

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 02_foreign_keys.sql
*/


/*  You want to make sure that no one can insert rows in the weather table that
    do not have a matching entry in the cities table. This is calling
    maintaining the REFERENTIAL INTEGRITY of your data.
    The new declaration of the tables would look like this:
*/
DROP VIEW myview;    -- delete tables to have them recreated
DROP TABLE cities;
DROP TABLE weather;


CREATE TABLE cities (
	city		varchar(80) primary key,
	location	point
);

CREATE TABLE weather (
	city		varchar(80) references cities(city),
	temp_lo		int,
	temp_hi		int,
	prcp		real,
	date		date
);

INSERT INTO weather VALUES ('Berkeley', 45, 53, 0.0, '1994-11-28');
/*  DETAIL:  Key (city)=(Berkeley) is not present in table "cities".  */
