====================================
    Chapter 4. SQL Syntax
====================================
4.1     Lexical Structure

        SELECT * FROM MY_TABLE;
        UPDATE MY_TABLE SET A = 5;
        INSERT INTO MY_TABLE VALUES (3, 'hi there');

        Identifiers             ex: MY_TABLE, A
        Key words               ex: SELECT, UPDATE or VALUES
        Constants               ex: 'This is a string', 42, 1.925e-3
        Operators               ex: + - * / < > = ~ ! @ # % ^ & | ' ?
        Special Characters      ex: $ () [] , ; : * .
        Comments                ex: -- standard SQL comment /* multiline */
        Operator precedence     ex: . :: [] +- ^ */% +- IS ISNULL NOTNULL IN
                                    BETWEEN OVERLAPS LIKE ILIKE SIMILAR < >
                                    = NOT AND OR

4.2     Value Expressions

        Column references       ex: my_table.name, my_table.salary
        Positional parameters   ex: inside a function $2 is the 2nd parameter
        Subscripts              ex: CREATE TABLE bigt(v int[2]);
        Field selection         ex: mytable.mycolumn, $1.mycolumn, (fn(a)).col3
        Operator invocation     ex: !!(v);  (v)! AS factorial;
        Function calls          ex: SELECT get_users('tom');
        Aggregate expressions   ex: SELECT avg(salary) FROM my_table;
        Window function calls   ex: SELECT avg(price) OVER (PARITION BY grpid)...
        Type casts              ex: '100'::INTEGER, CAST('100' AS INTEGER);
        Collation expressions   ex: SELECT name FROM table ORDER BY name COLLATE "fr_FR";
        Scalar subqueries       ex: SELECT c, (SELECT max(amt) FROM t WHERE c=d) FROM t;
        Array constructors      ex: SELECT ARRAY[1, 2, 22.7]::integer[];
        Row constructors        ex: SELECT ROW(table.col1, 42) FROM my_table;
        Expressions eval. rules ex: SELECT x FROM tbl WHERE CASE WHEN x > 0 THEN 10/x > 1 ELSE false END;


4.3     Calling Functions

        Using Positional Notation ex: SELECT function('Hello', 'World');
        Using Named Notation      ex: SELECT function(b := c2, a := c1) FROM tbl;
        Using Mixed Notation      ex: SELECT function(c1, b := c2) FROM tbl;
