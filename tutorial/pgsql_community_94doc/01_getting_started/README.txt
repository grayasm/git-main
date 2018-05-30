----------------
INSTALL PACKAGES
----------------
    yum info postgresql
    yum info pgadmin3

    yum install postgresql postgresql-contrib postgresql-libs postgresql-server
    yum install pgadmin3
    yum install pgcenter pg_top pg_view


DEFAULT INITIALIZATION
----------------------
    # to initialize postgresql database in default location: /var/lib/pgsql/data
    sudo postgresql-setup initdb


CUSTOM INITIALIZATION
---------------------
    # to initialize the database at a different location:
    mkdir -pv /mnt/sdb1/1TBpostgres/pgsql
    chmod 700 /mnt/sdb1/1TBpostgres
    chown -Rv postgres:postgres /mnt/sdb1/1TBpostgres
    chcon -u system_u -r object_r -t postgresql_db_t \
          -Rv /mnt/sdb1/1TBpostgres/pgsql

    su - postgres
    initdb -D /mnt/sdb1/1TBpostgres/pgsql/data
    exit  # to root


START THE SERVICE
-----------------
    # change $PGDATA (to custom db location)
    emacs /usr/lib/systemd/system/postgresql.service &

    # Location of database directory
    # Environment=PGDATA=/var/lib/pgsql/data
    Environment=PGDATA=/mnt/sdb1/1TBpostgres/pgsql/data


    systemctl enable postgresql.service
    systemctl start postgresql.service
    systemctl status postgresql.service

    # check if default database directory is empty
    ll /var/lib/pgsql/data


ADMINISTRATION
--------------
    # to use pgadmin3 GUI we need few extra steps:
    # (a) set a password for server administrator 'postgres'
    su - postgres
    psql
    ALTER USER postgres WITH PASSWORD '***root pass***';
    \q
    exit  # to root

    # (b) enable socket connections for all users on localhost
    emacs /mnt/sdb1/1TBpostgres/pgsql/data/pg_hba.conf &

    # custom configuration (mihai)
    # TYPE  DATABASE        USER            ADDRESS                 METHOD
    local   all             all                                     md5
    host    all             all             127.0.0.1/32            md5
    host    all             all             ::1/128                 md5

    # (c) reload the pg_hba.conf file
    systemctl restart postgresql.service

    # (d) check ip(6)tables to have port 5432 open
    nmap localhost
    5432/tcp open   postgresql

    # from current logged user (miha) start pgadmin3
    pgadmin3

    # add connection to a server with the following details:
    # Name: postgres
    # Host: localhost
    # Port: 5432
    # Service:
    # Mainenance DB: postgres
    # Username: postgres
    # Password: *** root pass ***
    # Store password: no
    # Group: Servers
    # on OK pgadmin3 should connect via socket to local db server.


WORK AS REGULAR USER
--------------------
    # use pgadmin3 with a regular user and database
    su - postgres
    psql
    CREATE USER pgmihai WITH PASSWORD '***nix/usr pass***';
    CREATE DATABASE mytestdb OWNER=pgmihai;

    # now configure pgadmin3 to use pgmihai, all same as above except:
    # Username: pgmihai
    # Password: ***nix/usr pass***


    # pgadmin3 allow to save, change and run .sql files on selected database.

    # to login from console to db as user pgmihai, type from regular account:
    psql -d mytestdb -U pgmihai


GET STARTED
-----------
    \cd /home/mihai/Code/git-main/tutorial/pgsql_community_94doc/01_getting_started
    \i 01_access_to_database.sql
    \dt               -- to list all tables
    \dt a_table_name  -- to see the table description
    \df               -- to list all functions
    \?                -- further help
