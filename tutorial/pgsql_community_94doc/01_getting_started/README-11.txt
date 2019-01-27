-----------------------------
INSTALL PACKAGES (ver. 11.1)
-----------------------------

    rpm -Uvh https://yum.postgresql.org/11/redhat/rhel-7-x86_64/pgdg-centos11-11-2.noarch.rpm
    emacs /etc/yum.repos.d/pgdg-11-centos.repo
    # priority=50

    yum clean all
    yum update
    yum search postgresql11
    yum install postgresql11 postgresql11-contrib postgresql11-libs \
                postgresql11-server
    yum install pg_top11

    # HN: What a clusterfuck of a disaster pgadmin4 is.
    #     Fails to install due to pgadmin4-web's python dependencies
    yum info pgadmin4


DEFAULT INITIALIZATION
----------------------
    # default database location is /var/lib/pgsql/11/data
    ls -l /usr/pgsql-11/bin
    sudo /usr/pgsql-11/bin/postgresql-11-setup initdb

CUSTOM INITIALIZATION (see README.txt)
--------------------------------------
START THE SERVICE
-----------------
    # change $PGDATA (to custom db location) if needed
    locate postgresql-11.service
    emacs /usr/lib/systemd/system/postgresql-11.service &

    systemctl enable postgresql-11.service
    systemctl start  postgresql-11.service
    systemctl status postgresql-11.service

    # check if default database directory is empty
    ll /var/lib/pgsql/11/data

TIMEZONE (use README.txt)
-------------------------
ADMINISTRATION
--------------
    # (a) set a password for server administrator 'postgres'
    su - postgres
    /usr/pgsql-11/bin/psql
    ALTER USER postgres WITH PASSWORD '***root pass***';
    \q
    exit  # to root

    # (b) enable socket connections for all users on localhost
    emacs /var/lib/pgsql/11/data/pg_hba.conf &

    # custom configuration (mihai)
    # TYPE  DATABASE        USER            ADDRESS                 METHOD
    local   all             all                                     md5
    host    all             all             127.0.0.1/32            md5
    host    all             all             ::1/128                 md5

    # (c) reload the pg_hba.conf file
    systemctl restart postgresql-11.service

    # (d) check ip(6)tables to have port 5432 open
    nmap localhost
    5432/tcp open   postgresql


RESTORE THE DATABASE
--------------------
    # create pgmihai user
    su - postgres
    /usr/pgsql-11/bin/psql
    CREATE USER pgmihai WITH PASSWORD '***nix/usr pass***';
    DROP DATABASE IF EXISTS mytestdb;
    \q

    # restore "mytestdb" from the .dump file
    cd /var/lib/pgsql.old
    /usr/pgsql-11/bin/pg_restore -U postgres -C -d postgres -Fc mytestdb.dump
    '***root*** pass'
    # done
