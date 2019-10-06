/*  Cap.9   Functions and Operators
    9.6     Bit String Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.06_bit_string_functions_and_operators.sql
    \?
    \qecho '\033[2J'
*/


/*  Bit String Functions and Operators

    - working with types: bit and bit varying
    - requires equal length operands: & | #
    - when bit shiftin the original length is preserved

    Operator            Description
    -----------------+----------------------------
    ||                  concatenation
    &                   bitwise AND
    |                   bitwise OR
    #                   bitwise XOR
    ~                   bitwise NOT
    <<                  bitwise Shift Left
    >>                  bitwise Shift Right
    ----------------------------------------------
*/
SELECT B'10001' || B'011';    -- 10001011
SELECT B'10001' &  B'01101';  -- 00001
SELECT B'10001' |  B'01101';  -- 11101
SELECT B'10001' #  B'01101';  -- 11100
SELECT ~B'10001';             -- 01110
SELECT B'10001' << 3;         -- 01000
SELECT B'10001' >> 2;         -- 00100
