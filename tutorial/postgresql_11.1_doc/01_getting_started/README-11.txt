----------------------------------------
BACKUP CURRENT DATABASE - SEE README.txt
----------------------------------------

INSTALL PACKAGES (ver. 11.1)
-----------------------------

    rpm -Uvh https://yum.postgresql.org/11/redhat/rhel-7-x86_64/pgdg-centos11-11-2.noarch.rpm
    emacs /etc/yum.repos.d/pgdg-11-centos.repo
    # priority=9

    yum info postgresql11
    yum info pgadmin4

    yum install postgresql11 postgresql11-contrib postgresql11-libs postgresql11-server
    yum install pgadmin4
    yum install pgcenter pg_top11


DEFAULT INITIALIZATION
----------------------
    # in default location: /var/lib/pgsql/data
    sudo /usr/pgsql-11/bin/postgresql-11-setup initdb


CUSTOM INITIALIZATION
---------------------
    # to initialize the database at a different location:
    mkdir -pv /mnt/sdb1/1TBpostgres/pgsql
    chmod 700 /mnt/sdb1/1TBpostgres
    chown -Rv postgres:postgres /mnt/sdb1/1TBpostgres/pgsql
    chcon -u system_u -r object_r -t postgresql_db_t \
          -Rv /mnt/sdb1/1TBpostgres/pgsql

    su - postgres
    /usr/pgsql-11/bin/initdb -D /mnt/sdb1/1TBpostgres/pgsql/data
    # exit to root, /tmp


START THE SERVICE
-----------------
    # change $PGDATA (to custom db location) !!!The .service file is overwritten
    #                                           when updating CentOS system
    emacs /usr/lib/systemd/system/postgresql-11.service &

    # Environment=PGDATA=/var/lib/pgsql/data
    Environment=PGDATA=/mnt/sdb1/1TBpostgres/pgsql/data


    systemctl enable postgresql-11.service
    systemctl start  postgresql-11.service
    systemctl status postgresql-11.service

    # check if default database directory is empty
    ll /var/lib/pgsql/11/data


TIMEZONE
--------
    # Set TimeZone, DateStyle and IntervalStyle in postgresql.conf
    emacs /mnt/sdb1/1TBpostgres/pgsql/data/postgresql.conf

    timezone = 'GMT'
    log_timezone = 'GMT'
    datestyle = 'iso, mdy'
    intervalstyle = 'postgres'

    # save and reload the postgresql.conf file
    systemctl restart postgresql-11.service

QUERY TUNING
------------
    emacs /mnt/sdb1/1TBpostgres/pgsql/data/postgresql.conf

    # optimizes queries over partition tables
    enable_partition_pruning = on


ADMINISTRATION
--------------
    # (a) set a password for server administrator 'postgres'
    su - postgres
    /usr/pgsql-11/bin/psql
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
    cd /mnt/sdb1/1TBpostgres/pgsql.old
    /usr/pgsql-11/bin/pg_restore -U postgres -C -d postgres -Fc mytestdb.dump
    '***root*** pass'

    # done


PGADMIN4
--------
    cat /var/log/httpd/error_log
    IOError: [Errno 13] Permission denied: '/var/log/pgadmin/pgadmin4.log'
