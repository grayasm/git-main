/*  Chapter 5. Data Definition
    5.4 System Columns

    psql -d mytestdb -U pgmihai
    \i 09_system_columns.sql
*/

/*      Every table has several "system columns" that are implicitly defined
        by the system. Therefore, these names cannot be used as names of
		user-defined columns. These restrictions are separate from whether
		the name is a key word or not; quoting a name will not allow you to
		escape these restrictions. You do not really need to be concerned
		about these columns; just know they exist.
*/

/*      oid: Object Identification Numbers (OIDs) of a raw. */
DROP TABLE IF EXISTS oidtest CASCADE;
CREATE TABLE oidtest (age INTEGER) WITH OIDS;
INSERT INTO oidtest VALUES (7);
SELECT oid, age FROM oidtest;

/*
  oid  | age
-------+-----
 16996 |   7
(1 row)
*/

/*      tableoid: The OID of the table containing this row.
        Example: how to know which table a particular row originated from. */
DROP TABLE IF EXISTS cities CASCADE;
CREATE TABLE cities (
        name        TEXT,
		population  FLOAT,
		altitude    INT     -- in feet
		);
INSERT INTO cities VALUES
        ('Las Vegas', 2000000, 2174),
		('Mariposa', 500000, 1953),
		('Madison', 1400000, 845);
SELECT c.tableoid, c.name, c.altitude FROM cities c WHERE c.altitude > 500;
/*
 tableoid |   name    | altitude
----------+-----------+----------
    17011 | Las Vegas |     2174
    17011 | Mariposa  |     1953
    17011 | Madison   |      845
(3 rows)
*/


/*      xmin: The identity (transaction ID) of the inserting transaction for
              this row version. */
			  
/*      cmin: The command identifier (starting at zero) within the inserting
              transaction. */
			  
/*      xmax: The identity (transaction ID) of the deleting transaction,
              or zero for an undeleted row version. It is possible for this
			  column to be nonzero in a visible row version. That usually
			  indicates that the deleting transaction hasn't committed yet,
			  or that an attempted deletion was rolled back. */

/*      cmax: The command identifier within the deleting transaction, or zero. */

/*      ctid: The pysical location of the row version within its table. A ctid
              will change if it is updated or moved by VACUUM FULL. Therefore
			  ctid is useless as a long-term row identifier. */
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  
			  