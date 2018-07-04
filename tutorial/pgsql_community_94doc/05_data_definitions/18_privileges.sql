/*  Chapter 5. Data Definition
    5.6. Privileges
	
	psql -d mytestdb -U pgmihai
    \i 18_privileges.sql
*/


/*      When an object is created, it is assigned an owner. The owner is
        normally the role that executed the creation statement.
		role=owner=user
		There are different kinds of privileges:
		SELECT,  INSERT,  UPDATE,  DELETE,  TRUNCATE,  REFERENCES,  TRIGGER,
		CREATE,  CONNECT,  TEMPORARY,  EXECUTE  and USAGE.
		
		Ordinarily, only the object's owner (or a superuser) can GRANT or REVOKE
		privileges on an object.
		It is possible to grant a privilege "with grant option", which gives
		the recipient the right to grant it in turn to others. If the grant
		option is revoked then all who received the privilege from that
		recipient (directly or through a chain of grants) will lose
		the privilege. More on GRANT and REVOKE commands.
*/
DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );
		
ALTER TABLE products OWNER TO pgmihai2;
/*
psql:18_privileges.sql:23: ERROR:  role "pgmihai2" does not exist

Use: pgAdmin3 or pgAdmin III exe to create new role/user in "Login Roles"
     before trying this command.
*/

GRANT UPDATE ON products TO joe;
/*
psql:18_privileges.sql:31: ERROR:  role "joe" does not exist
*/

REVOKE ALL ON products FROM PUBLIC;

DROP TABLE IF EXISTS products CASCADE;  -- pgmihai can still drop the table
