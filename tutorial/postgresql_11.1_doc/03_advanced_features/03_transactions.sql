/*  Cap.3 Advanced Features
    3.4 Transactions

    Run with:
    psql -d mytestdb -U pgmihai   # give password
    \i 03_transactions.sql
*/


-- create the missing tables first for the banking transaction example;
DROP TABLE IF EXISTS accounts, branches;
CREATE TABLE accounts(name varchar(80), branch_name varchar(80), balance real);
CREATE TABLE branches(name varchar(80), balance real);

-- populate the tables with data
INSERT INTO accounts VALUES('Alice', 'New York', 1200.12);
INSERT INTO accounts VALUES('Bob', 'Chicago', 425.43);
INSERT INTO accounts VALUES('Wally', 'Detroit', 125.13);
INSERT INTO branches VALUES('New York', 80000000.0); -- 80 mil
INSERT INTO branches VALUES('Chicago', 70000000.0);  -- 70 mil
INSERT INTO branches VALUES('Detroit', 65000000.0);  -- 65 mil


/*  A transaction bundles multiple steps into a single, all-or-nothing
    operation. If some failure occurs then none of the steps afect the database
    at all. A transaction is surrounding by the SQL commands BEGIN and COMMIT.
    Suppose we want to record a payment of $100.00 from Alice's account to
    Bos's account.
*/
BEGIN;
UPDATE accounts SET balance = balance - 100.00 WHERE name  = 'Alice';
UPDATE branches SET balance = balance - 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Alice');
UPDATE accounts SET balance = balance + 100.00 WHERE name = 'Bob';
UPDATE branches SET balance = balance + 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Bob');
COMMIT;

-- list content of accounts;
SELECT * FROM accounts ORDER BY name;
/*
 name  | branch_name | balance
-------+-------------+---------
 Alice | New York    | 1100.12
 Bob   | Chicago     |  525.43
 Wally | Detroit     |  125.13
*/


/*  If, partway through the transaction, we decide we do not want to commit, we
    can issue the command ROLLBACK instead of COMMIT, and all updates so far
    will be canceled.
*/
BEGIN;
UPDATE accounts SET balance = balance - 100.00 WHERE name  = 'Alice';
UPDATE branches SET balance = balance - 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Alice');
UPDATE accounts SET balance = balance + 100.00 WHERE name = 'Bob';
UPDATE branches SET balance = balance + 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Bob');
ROLLBACK;

-- list content of accounts;
SELECT * FROM accounts ORDER BY name;
/*
 name  | branch_name | balance
-------+-------------+---------
 Alice | New York    | 1100.12
 Bob   | Chicago     |  525.43
 Wally | Detroit     |  125.13
*/


/*  Suppose we debit $100.00 from Alice's account, and credit Bob's account
    only to find later that we should have credited Wally's account.
    Savepoints allow you to selectively discard parts of the transaction while
    committing the rest.
*/
BEGIN;
UPDATE accounts SET balance = balance - 100.00 WHERE name  = 'Alice';
UPDATE branches SET balance = balance - 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Alice');
SAVEPOINT alice_savepoint;

UPDATE accounts SET balance = balance + 100.00 WHERE name = 'Bob';
UPDATE branches SET balance = balance + 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Bob');
ROLLBACK TO alice_savepoint;

UPDATE accounts SET balance = balance + 100.00 WHERE name = 'Wally';
UPDATE branches SET balance = balance + 100.00
       WHERE name = (SELECT branch_name FROM accounts WHERE name = 'Wally');
COMMIT;

-- list content of accounts;
SELECT * FROM accounts ORDER BY name;
/*
 name  | branch_name | balance
-------+-------------+---------
 Alice | New York    | 1000.12
 Bob   | Chicago     |  525.43
 Wally | Detroit     |  225.13
*/




--clean up
DROP TABLE accounts, branches;
