*
*   Chapter 3 Advanced Features

    Views             ex: CREATE VIEW v AS SELECT * FROM t WHERE id < 100;
                          SELECT * FROM v;
    Foreign Keys      ex: CREATE TABLE c (city TEXT PRIMARY KEY, l point);
                          CREATE TABLE w (city TEXT REFERENCES c(city), t int);
    Transactions      ex: BEGIN;
                          UPDATE acc SET bal = bal - 100.00 WHERE name='Alina';
                          UPDATE acc SET bal = bal + 100.00 WHERE name='Mihai';
                          COMMIT;
    Window Functions  ex: SELECT dep,sal,avg(sal) OVER(PARTITION BY dep) FROM emp;
    Inheritance       ex: CREATE TABLE capitals(stat CHAR(2)) INHERITS (cities);
