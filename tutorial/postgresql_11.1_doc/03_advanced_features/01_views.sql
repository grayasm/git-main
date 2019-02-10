/*  Cap.3 Advanced Features
    3.2 Views

    Run with:
    psql -d mytestdb -U pgmihai
    \i 01_views.sql
    \?
    \qecho '\033[2J'
*/


/*  You can create a view over the query, which gives a name to the query that
    you can refer to like an ordinary table.
    In case the view exists delete it before running this.
    DROP VIEW <view_name>;
*/
CREATE VIEW myview AS
       SELECT city, temp_lo, temp_hi, prcp, date, location
       FROM weather, cities
       WHERE city = name;

SELECT * FROM myview;
