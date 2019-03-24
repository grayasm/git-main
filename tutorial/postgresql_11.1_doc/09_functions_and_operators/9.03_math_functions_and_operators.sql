/*  Cap.9   Functions and Operators
    9.3     Mathematical Functions and Operators

    psql -d mytestdb -U pgmihai
    \i   9.03_math_functions_and_operators.sql
    \?
    \qecho '\033[2J'
*/

/*      Check the next 4 cathegories:
        1. Mathematical  Operators
        2. Mathematical  Functions
        3. Random        Functions
        4. Trigonometric Functions
*/

/*      Mathematical operators are provided for many PostgreSQL types. For types
        without standard mathematical conventions (e.g., date/time types)
        we describe the actual behavior in subsequent sections.

        Operator   Description
        ---------+-------------
        +          Addition
        -          Subtraction
        *          Multiplication
        /          Division (integer division truncates the result)
        %          Modulo (remainder)
        ^          Exponentiation
        |/         Square root (prefix operator)
        ||/        Cube root   (prefix operator)
        !          Factorial
        !!         Factorial prefix operator
        @          Absolute value (prefix operator)
        &          Bitwise AND
        |          Bitwise OR
        #          Bitwise XOR
        ~          Bitwise NOT    (prefix operator)
        <<         Bitwise shift left
        >>         Bitwise shift right
*/

SELECT 2 + 2; -- 4
SELECT 2 - 4; -- -2
SELECT 2 * 5; -- 10
SELECT 2.22 * 10 / 2; -- 11.10000
SELECT 22 % 7; -- 1
SELECT 2.0 ^ 3.0; -- 8.0000
SELECT |/ 25.0; -- 5
SELECT ||/ 27.0; -- 3
SELECT 4!; -- 24
SELECT !!4; -- 24
SELECT @(2-7); -- 5
SELECT B'0101' & B'1011'; -- 0001
SELECT B'0101' & B'1000'; -- 1101
SELECT B'1100' # B'1010'; -- 0110
SELECT ~B'1100'; -- 0011
SELECT B'00000111' << 3; -- 00111000
SELECT B'11110000' >> 3; -- 00011110


/*      Mathematical functions
        In the table 'dp' indicates 'double precision'.
        The functions working with dp data are mostly implemented on top of
        host system's C library.

        Function     Description
        ------------+----------------------------
        abs(dp)
        cbrt(dp)

        ceil(dp)
        ceil(num)

        ceiling(dp)
        ceiling(num)

        degrees(dp)
        div(num, num)

        exp(dp)
        exp(num)

        floor(dp or numeric)
        ln(dp or numeric)
        log(dp or numeric)
        log(b numeric, x numeric)
        mod(y, x)
        pi()
        power(a dp, b dp)
        power(a numeric, b numeric)
        radians(dp)
        round(dp or numeric)
        scale(numeric)
        sign(dp or numeric)
        sqrt(dp)
        trunc(dp)
        width_bucket(dp, dp, dp, int)
        width_bucket(num, num, num, int)
        width_bucket(any, anyarray);
*/
