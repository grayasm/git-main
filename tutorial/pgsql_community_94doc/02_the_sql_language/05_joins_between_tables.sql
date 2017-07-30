/*  Cap.2 The SQL Language,
    2.6 Joins Between Tables

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 05_joins_between_tables.sql
*/


/*  Join queries can access multiple tables at once, or access the same table
    in such a way that multiple rows of the table are being processed at the
    same time.
*/
SELECT * FROM weather, cities WHERE city = name;


/*  To avoid having the city column two times you will probably want to output
    columns explicitly rather than using *.
*/
SELECT city, temp_lo, temp_hi, prcp, date, location
	FROM weather, cities
	WHERE city = name;


/*  If there were duplicate column names in the two tables you'd need to
    qualify the column names to show which one you meant. (Good style)
*/
SELECT weather.city, weather.temp_lo, weather.temp_hi,
	weather.prcp, weather.date, cities.location
	FROM weather, cities
	WHERE cities.name = weather.city;
	

/*  Join queries of the kind seen thus far can also be written in this
    alternative form.
*/
SELECT * FROM weather INNER JOIN cities ON (weather.city = cities.name);


/*  We want to get Hayward records back in, and if no matching row is found
    we want some "empty values" to be substituted for the cities table's
    columns. This query is an OUTER JOIN.
*/
SELECT * FROM weather LEFT OUTER JOIN cities ON (weather.city = cities.name);


/*  We can also join a table against itself. This is called a SELF JOIN.
    As an example, we need to compare the temp_lo and temp_hi columns of each
    weather row to the temp_lo and temp_hi columns of all other weather rows.
*/
SELECT W1.city, W1.temp_lo AS low, W1.temp_hi AS high,
	W2.city, W2.temp_lo AS low, W2.temp_hi AS high
	FROM weather W1, weather W2
	WHERE W1.temp_lo < W2.temp_lo
	AND W1.temp_hi > W2.temp_hi;


/*  We have relabeled the weather table as W1 and W2 to distinguish the left
    and right side of the join. You can also use these kinds of aliases in
    other queries to save some typing.
*/
SELECT *
	FROM weather w, cities c
	WHERE w.city = c.name;
















