/*  Chapter 4.1 Lexical Structure
    4.1.6 Operator Precedence

    run with:
    psql -d mytestdb -U pgmihai             # give password
    \dt                                     # list all tables
    \i 06_operator_precedence.sql
*/


/*  Because the precedence and associativity of the operators is hard-wired
    into the parser, some expressions need paranthesis when using combinations
    of binary and unary operators.
    ex with error:  SELECT 5 ! - 6;
*/
SELECT (5!) - 6;  -- 120 - 6 = 114


/*  Operator      Associativity  Description
    .             left           table/column name separator
    ::            left           PostgreSQL - style typecase
    [ ]           left           array element selection
    + -           right          unary plus, unary minus
    ^             left           exponentiation
    * / %         left           multiplication, division, modulo
    + -           left           addition, subtraction
    IS                           IS TRUE, IS FALSE, IS NULL, etc
    ISNULL                       test for null
    NOTNULL                      test for not null
    (any other)   left           all other native and user-def operators
    IN                           set membership
    BETWEEN                      range containmnet
    OVERLAPS                     time interval overalp
    LIKE ILIKE SIMILAR           string pattern matching
    < >                          less than, greater then
    =             right          equality, assignment
    NOT           right          logical negation
    AND           left           logical conjunction
    OR            left           logical disjunction
*/

SELECT (10 + 10 - 5 * 3 / 5 ) % 3; -- 17 % 3 = 2
