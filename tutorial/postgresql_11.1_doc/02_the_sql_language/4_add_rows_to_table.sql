/*  Cap.2 The SQL Language,
    2.4 Populating a Table with Rows

    Run with:
    psql -d mytestdb -U pgmihai
    \i 2.4_add_rows_to_table.sql
    \?
    \qecho '\033[2J'
*/

INSERT INTO weather VALUES ('San Francisco', 46, 50, 0.25, '1994-11-27');

/*  Constants that are not simple numeric values usually must be surrounded
    by single quotes ('). The date type above is more flexible in what it
    accepts, but for point type we follow the format.
*/
INSERT INTO cities VALUES ('San Francisco', '(-194.0, 53.0)');


/*  The syntax used above requires you to remember the order of the columns.
    An alternative syntax allows you to list the columns explicitly.
*/
INSERT INTO weather (city, temp_lo, temp_hi, prcp, date)
       VALUES ('San Francisco', 43, 57, 0.0, '1994-11-29');

/*  You can list the columns in a different order if you wish or even omit
    some columns, e.g. if the precipitation is unknown.
*/
INSERT INTO weather (date, city, temp_hi, temp_lo)
       VALUES ('1994-11-29', 'Hayward', 54, 37);

/*  Copy 03_weather.txt to /tmp before running this .sql file
    On CentOS only DB superuser is allowed to COPY from file.
    Even with superuser the file needs SELINUX context to be readable.
*/
COPY weather FROM '/tmp/03_weather.txt';
