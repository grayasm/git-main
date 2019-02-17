/*  Chapter 1. Getting Started
    Run:
    (a) from command line:

    get shell to database :     psql -d mytestdb -U pgmihai
    run sql file          :     \i 1.4_accesing_a_database.sql
    list all roles(users) :     \du
    list all tables       :     \dt
    SELECT * FROM users   :     TABLE users;
    help                  :     \?
    clear screen          :     \qecho '\033[2J'

    (b) from pgadmin3 using GUI tool
    (c) from pgadmin4 (probably using the web interface)
*/

SELECT version();
SELECT current_date;
SELECT 2 + 2;
