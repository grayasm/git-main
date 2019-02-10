/*  Chapter 1. Getting Started
    Run:
    (a) from command line:

    get shell to database :     psql -d mytestdb -U pgmihai
    run sql file          :     \i 01_test.sql
    help                  :     \?
    clear screen          :     \qecho '\033[2J'

    (b) from pgadmin3 using GUI tool
    (c) from pgadmin4 (probably using the web interface)
*/

SELECT version();
SELECT current_date;
SELECT 2 + 2;
