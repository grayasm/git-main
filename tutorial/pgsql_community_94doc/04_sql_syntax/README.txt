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

        Column references       ex:
        Positional parameters   ex:
        Subscripts              ex:
        Field selection         ex:
        Operator invocation     ex:
        Function calls
        Aggregate expressions
        Window function calls   ex:
        Type casts              ex:
        Collation expressions   ex:
        Scalar subqueries       ex:
        Array constructors      ex:
        Row constructors        ex:
        Expressions eval. rules ex:


4.3     Calling Functions

        Using Positional Notation
        Using Named Notation
        Using Mixed Notation
