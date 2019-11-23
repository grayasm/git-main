/*  Cap.9   Functions and Operators
    9.7     Pattern Matching

    psql -d mytestdb -U pgmihai
    \i   9.07_pattern_matching.sql
    \?
    \qecho '\033[2J'
*/

/*  There are 3 approaches to pattern matching:
    1.    LIKE        operator
    2.    SIMILAR TO  operator
    3.    POSIX-style regular expression
    4.    Functions to extract, replace or split at maching locations
*/

/*  1.  LIKE Operator
    -----------------
    string LIKE pattern [ESCAPE escape-character]
    string NOT LIKE pattern [ESCAPE escape-character]

    _ denotes any single character
    % denotes any string
    \ disables the special meaning of any of these metacharacters
    ESCAPE can specify a different escape character
*/

SELECT 'abc' LIKE 'abc';  -- t (true)
SELECT 'abc' LIKE 'a%';   -- t (true)
SELECT 'abc' LIKE '_b_';  -- t (true)
SELECT 'abc' LIKE 'c';    -- f (false)


/*  2.  SIMILAR TO Operator
    -------------------------------------------
    string SIMILAR TO pattern [ESCAPE escape-character]
    string NOT SIMILAR TO pattern [ESCAPE escape-character]

    _ denotes any single character
    % denotes any string
    | denotes alternation (either of two alternatives)
    * denotes repetition of the previous item zero or more times
    + denotes repetition of the previous item one or more times
    ? denotes repetition of the previous item zero or one time
    {m} denotes repetition of the previous item exactly m times
    {m,} denotes repetition of the previous item m or more times
    {m,n} denotes repetition of the previous item at least m and not more than n times
    () can be used to group items into a single logical item
    [] specifies a character class, just as in POSIX regexp
    \ disables the special meaning of any of these metacharacters
    ESCAPE can specify a different escape character
*/

SELECT 'abc' SIMILAR TO 'abc';  -- t (true)
SELECT 'abc' SIMILAR TO 'a';    -- f (false)
SELECT 'abc' SIMILAR TO '%(b|d)%'; -- t (true)
SELECT 'abc' SIMILAR TO '(b|c)%';  -- f (false)


/*  4.  Functions to extract, replace or split at maching locations
    ---------------------------------------------------------------
    substring(string from pattern for escape-character)
*/

SELECT substring('foobar' from '%#"o_b#"%' for '#');    -- oob
SELECT substring('foobar' from '#"o_b#"%' for '#');     -- NULL

/*  3.  POSIX Regular Expressions Operators
    ---------------------------------------
    Operator   Description
    ---------+-----------------------------------------------------
    ~          Matches regular expression, case sensitive
    ~*         Matches regular expression, case insensitive
    !~         Does not match regular expression, case sensitive
    !~*        Does not match regular expression, case insensitive
    ---------------------------------------------------------------
*/

