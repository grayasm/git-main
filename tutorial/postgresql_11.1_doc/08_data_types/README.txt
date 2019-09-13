    Chapter 8. Data Types

    Numeric Types    : ---------------------------------------------------------
      smallint/int2  : CREATE TABLE t (si SMALLINT, i2 int2);--size=2 bytes
      integer/int4   : CREATE TABLE t (ni INTEGER,  i4 int4);--size=4 bytes
      bigint/int8    : CREATE TABLE t (bi BIGINT,   i8 int8);--size=8 bytes
      numeric        : CREATE TABLE t (nm NUMERIC(5,2));     --up to=(131072,16383)
      real           : CREATE TABLE t (rn REAL);             --prec=6
     double precision: CREATE TABLE t (db DOUBLE PRECISION); --prec=15
      float(24)      : CREATE TABLE t (f24 FLOAT(24));       --same as real
      float(53)      : CREATE TABLE t (f53 FLOAT(53));       --same as d.prec
      smallserial    : CREATE TABLE t (ss SMALLSERIAL);      --size=2 bytes
      serial         : CREATE TABLE t (sr SERIAL);           --size=4 bytes
      bigserial      : CREATE TABLE t (bs BIGSERIAL);        --size=8 bytes
    Monetary Types   : ---------------------------------------------------------
      money          : CREATE TABLE t (mon MONEY);           --$2,470
    Character Tyes   : ---------------------------------------------------------
 character varying(n): CREATE TABLE t (cv CHARACTER VARYING(250)); --var.len with limit
      character(n)   : CREATE TABLE t (ch CHARACTER(20));    --fix.len, blank padded
      varchar(n)     : CREATE TABLE t (cv VARCHAR(250));     --similar with ch.varying(n)
      char(n)        : CREATE TABLE t (ch CHAR(20));         --similar with character(n)
      text           : CREATE TABLE t (tx TEXT);             --var.unlimited len
    Binary Data Types: ---------------------------------------------------------
      bytea          : CREATE TABLE t (bv BYTEA);            --var.len binary string
                       INSERT INTO t VALUES ('\\abc');       --\x5c616263
    Date/Time Types  : ---------------------------------------------------------
      timestamp      : CREATE TABLE t (tswotz TIMESTAMP);    -- '1999-01-08 04:05:06'
timestamp with time zone
                     : CREATE TABLE t (tswtz TIMESTAMP WITH TIME ZONE); --'2018-03-25 02:03:30+01'
      date           : CREATE TABLE t (dt DATE);             -- '1999-01-08'
      time           : CREATE TABLE t (tm TIME);             -- '04:05:06.789'
  time with time zone: CREATE TABLE t (twts TIME WITH TIME ZONE); -- '04:05:06.789-8'
      interval       : CREATE TABLE t (in INTERVAL);         -- '2 months ago'
    Boolean Types    : ---------------------------------------------------------
      boolean        : CREATE TABEL t (bval BOOLEAN);        --TRUE,t,true,y,yes,on,1...
    Enumerated Types : ---------------------------------------------------------
      enum           : CREATE TYPE mood_type AS ENUM ('sad','ok','happy');
                       CREATE TABLE person (name TEXT, mood mood_type);
    Geometric Types  : ---------------------------------------------------------
      point          : CREATE TABLE t (pt POINT); ... VALUES (point(11,11));
      line           : CREATE TABLE t (ln LINE); ... VALUES (CAST('{2,-1,3}'::text AS line));
      lseg           : CREATE TABLE t (ls LSEG); ... VALUES (CAST('(0,0), (5,5)'::text AS lseg));
      box            : CREATE TABLE t (bx BOX); ... VALUES (CAST('(-5,-5), (5,5)'::text AS box));
      path           : CREATE TABLE t (ph PATH); ... VALUES (CAST('[(5,0),(5,10)]'::text AS path));
      polygon        : CREATE TABLE t (pg POLYGON); ... VALUES (CAST('((0,0),(3,3),(-3,3))'::text AS polygon));
      circle         : CREATE TABLE t (cc CIRCLE); ... VALUES (CAST('<(10,10),5>'::text AS circle));
    Network Addr Type: ---------------------------------------------------------
      cidr           : CREATE TABLE t (ci CIDR); ... VALUES ('192.168.100.128/25');
      inet           : CREATE TABLE t (ip INET); ... VALUES ('192.168.0.1');
      macaddr        : CREATE TABLE t (ma MACADDR); ... VALUES ('08002b:010203');
      macaddr8       : CREATE TABLE t (m8 MACADDR8); ... VALUES ('08002b-0102030405');
    Big String Types : ---------------------------------------------------------
      bit(n)         : CREATE TABLE t (b3 BIT(3)); ... VALUES (B'101');
      bit varying(n) : CREATE TABLE t (bv BIT VARYING(5)); ... VALUES (B'101');
    Text Search Types: ---------------------------------------------------------
      tsvector       : SELECT 'a fat cat'::TSVECTOR; -- 'a' 'cat' 'fat' (1 row)
      tsquery        : SELECT 'fat & rat'::TSQUERY;  -- 'fat' & 'rat' (1 row)
    UUID Type        : ---------------------------------------------------------
      uuid           : CREATE TABLE t (ud UUID); ... VALUES ('a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11');
    XML Type         : ---------------------------------------------------------
      xml            : CREATE TABLE t (xl XML); ... VALUES (xml '<foo>bar</foo>');
    JSON Types       : ---------------------------------------------------------
      json           : CREATE TABLE t (jdoc JSON); ... VALUES ('[1,2,"foo",null]'::json);
      jsonb          : CREATE TABLE t (jdoc JSONB); ... VALUES ('{"name": "Angela Barton"}'::jsonb);
    Arrays           : ---------------------------------------------------------
      [][]           : CREATE TABLE t (i smallint[2][]); ... VALUES(ARRAY[[1,2],[3,4]]);
      [][]           : CREATE TABLE t (s TEXT[2][]); ... VALUES('{{"i3","dwm"},{"iwm","wm2"}}');
    Composite Types  : ---------------------------------------------------------
      type           : CREATE TYPE inv_type(n TEXT, p NUMERIC);
                       CREATE TYPE inv (i inv_type, c INTEGER);
                       INSERT INTO inv VALUES (ROW('fuzzy', 1.99), 110);
    Range Types      : ---------------------------------------------------------
      int4range      : CREATE TABLE t(i4 INT4RANGE); ... VALUES (int4range(0,20)); --[0,20)
      int8range      : CREATE TABLE t(i8 INT8RANGE); ... VALUES (int8range(0,20)); --[0,20)
      numrange       : CREATE TABEL t(nr NUMRANGE); ... VALUES (numrange(2.2,4.4));--[2.2,4.4)
      tsrange        : CREATE TABLE t(ts TSRANGE); ... VALUES ('[2010-01-01, 2010-02-01)');
      tstzrange      : CREATE TABLE t(tz TSTZRANGE); ... VALUES ('[2010-01-01+02, 2010-02-01+02)');
      daterange      : CREATE TABLE t(dr DATERANGE); ... VALUES ('[2010-01-01, 2010-02-01)');
    Domain Types     : ---------------------------------------------------------
      domain         : CREATE DOMAIN pint2 AS INT2 CHECK (VALUE > 0);
                       CREATE TABLE t (pi2 PINT2);
    OID Types        : ---------------------------------------------------------
      oid            : CREATE TABLE t (a INT2) WITH OIDS;
                       INSERT INTO t VALUES (7);
                       SELECT oid, a FROM t;
    pg_lsn Type      : ---------------------------------------------------------
      pg_lsn         : Log Sequence Number
    Pseudo-Types     : ---------------------------------------------------------
      pseudo-type    : C function parameters
