/*  Chapter 5. Data Definition
    5.6. Privileges

    Run as user=postgres

    psql -d mytestdb -U postgres
    \i 5.06_privileges.sql
    \?
    \qecho '\033[2J'
*/


/*      When an object is created, it is assigned an owner. The owner is
        normally the role that executed the creation statement.
        role=owner=user
        There are different kinds of privileges:
        SELECT,  INSERT,  UPDATE,  DELETE,  TRUNCATE,  REFERENCES,  TRIGGER,
        CREATE,  CONNECT,  TEMPORARY, TEMP,  EXECUTE, USAGE and ALL PRIVILEGES.

  GRANT {{ SELECT | INSERT | UPDATE | DELETE | TRUNCATE | REFERENCES | TRIGGER }
        [,...] | ALL [ PRIVILEGES ]}
        ON { [TABLE] table_name [,...]
             | ALL TABLES IN SCHEMA schema_name [,...] }
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT {{ SELECT | INSERT | UPDATE | REFERENCES } (column_name [,...])
        [,...] | ALL [ PRIVILEGES ] (column_name [,...]) }
        ON [ TABLE ] table_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT {{ USAGE | SELECT | UPDATE }
        [,...] | ALL [ PRIVILEGES ] }
        ON { SEQUENCE sequence_name [,...]
             | ALL SEQUENCES IN SCHEMA schema_name [,...] }
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT {{ CREATE | CONNECT | TEMPORARY | TEMP } [,...] | ALL [ PRIVILEGES ] }
        ON DATABASE database_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { USAGE | ALL [ PRIVILEGES ] }
        ON DOMAIN domain_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { USAGE | ALL [ PRIVILEGES ] }
        ON FOREIGN DATA WRAPPER fdw_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { USAGE | ALL [ PRIVILEGES ] }
        ON FOREIGN SERVER server_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { EXECUTE | ALL [ PRIVILEGES ] }
        ON {{ FUNCTION | PROCEDURE | ROUTINE } routine_name
        [([[ argmode ] [ arg_name ] arg_type [,...]])] [,...]
            | ALL { FUNCTIONS | PROCEDURES | ROUTINES } IN SCHEMA schema_name [,...] }
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { USAGE | ALL [ PRIVILEGES ] }
        ON LANGUAGE lang_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT {{ SELECT | UPDATE } [,...] | ALL [ PRIVILEGES ] }
        ON LARGE OBJECT loid [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT {{ CREATE | USAGE } [,..] | ALL [ PRIVILEGES ]}
        ON SCHEMA schema_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { CREATE | ALL [ PRIVILEGES ] }
        ON TABLESPACE tablespace_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  GRANT { USAGE | ALL [ PRIVILEGES ] }
        ON TYPE type_name [,...]
        TO role_specification [,...] [ WITH GRANT OPTION ]

  where role_specification can be
        [ GROUP ] role_name
        | PUBLIC
        | CURRENT_USER
        | SESSION_USER

  GRANT role_name [,...] TO role_name [,...] [ WITH ADMIN OPTION ]

  ==============================================================================
        Ordinarily, only the object's owner (or a superuser) can GRANT or REVOKE
        privileges on an object.
        It is possible to grant a privilege with GRANT option, which gives
        the recipient the right to grant it in turn to others. If the grant
        option is REVOKE-ed then all who received the privilege from that
        recipient (directly or through a chain of grants) will lose
        the privilege.

  REVOKE [ GRANT OPTION FOR ]
         {{ SELECT | INSERT | UPDATE | DELETE | TRUNCATE | REFERENCES | TRIGGER}
         [,...] | ALL [ PRIVILEGES ]}
         ON { [ TABLE ] table_name [,...]
              | ALL TABLES IN SCHEMA schema_name [,...]}
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         {{ SELECT | INSERT | UPDATE | REFERENCES } (column [,...])
         [,...] | ALL [ PRIVILEGES } (column [,...])}
         ON [ TABLE ] table_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         {{ USAGE | SELECT | UPDATE }
         [,...] | ALL [ PRIVILEGES ]}
         ON { SEQUENCE sequence_name [,...]
            | ALL SEQUENCES IN SCHEMA schema_name [,...] }
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         {{ CREATE | CONNECT | TEMPORARY | TEMP } [,...] | ALL [ PRIVILEGES ] }
         ON DATABASE database_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         { USAGE | ALL [ PRIVILEGES ]}
         ON FOREIGN DATA WRAPPER fwd_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         { USAGE | ALL [ PRIVILEGES ] }
         ON FOREIGN SERVER server_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         { EXECUTE | ALL [ PRIVILEGES ] }
         ON { FUNCTION function_name ([[argmode] [arg_name] arg_type [,...]]) [,...]
            | ALL FUNCTIONS IN SCHEMA schema_name [,...] }
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         { USAGE | ALL [ PRIVILEGES ] }
         ON LANGUAGE lang_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         {{ SELECT | UPDATE } [,...] | ALL [ PRIVILEGES ]}
         ON LARGE OBJECT loid [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         {{ CREATE | USAGE } [,...] | ALL [ PRIVILEGES ] }
         ON SCHEMA schema_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ GRANT OPTION FOR ]
         { CREATE | ALL [ PRIVILEGES ] }
         ON TABLESPACE tablespace_name [,...]
         FROM { [ GROUP ] role_name | PUBLIC } [,...]
         [ CASCADE | RESTRICT ]

  REVOKE [ ADMIN OPTION FOR ]
         role_name [,...] FROM role_name [,...]
         [ CASCADE | RESTRICT ]

*/

-- admin postgres
SET ROLE postgres;
DROP TABLE IF EXISTS products CASCADE;
DROP ROLE IF EXISTS joe;
DROP ROLE IF EXISTS alice;

CREATE ROLE joe   WITH PASSWORD 'NotImportant';
CREATE ROLE alice WITH PASSWORD 'NotImporant';

CREATE TABLE products (
        product_no    integer   PRIMARY KEY,
        name          text,
        price         numeric
        );

-- user joe
ALTER TABLE products OWNER TO joe;
SET ROLE joe;
INSERT INTO products VALUES
       (1, 'p1', 99.9),
       (2, 'p2', 88.8),
       (3, 'p3', 77.7),
       (4, 'p4', 66.6),
       (5, 'p5', 10.0);

-- user alice
SET ROLE postgres;
GRANT SELECT,UPDATE ON products TO alice;
SET ROLE alice;
UPDATE products SET price = 55.5 WHERE name = 'p5';


-- revoke all privileges
SET ROLE postgres;
REVOKE SELECT,UPDATE ON products FROM alice;

-- try something as alice
SET ROLE alice;
TABLE products;  -- similar with SELECT * FROM products;
-- ERROR:  permission denied for table products
