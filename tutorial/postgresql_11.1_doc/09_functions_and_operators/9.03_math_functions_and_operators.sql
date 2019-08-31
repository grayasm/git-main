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

        Function            Description
        -----------------+---------------------------------------
        abs(dp)             absolute value, abs(-17.4) = 17.4
        cbrt(dp)            cube root     , cbrt(27.0) = 3

        ceil(dp)            nearest integer greater than or equal to argument
        ceil(num)           ceil(-42.8) = -42

        ceiling(dp)         nearest integer greater than or equal to argument
        ceiling(num)        (same as ceil) ceiling(-95.3) = -95

        degrees(dp)         radians to degrees, degrees(0.5) = 28.6478897565412
        div(num, num)       integer quotient of y/x, div(9/4)= 2

        exp(dp)             exponential, exp(1.0) = 2.71828182845905
        exp(num)

        floor(dp or numeric)     nearest integer less then or equal to argument
                                 floor(-42.8) = -43

        ln(dp or numeric)        natural logarithm, ln(2.0) = 0.693147180559945
        log(dp or numeric)       base 10 logarithm, ln(100) = 2

        log(b numeric, x numeric)    logarithm to base, ln(2, 64) = 6.000000
        mod(y, x)                    remainder of y/x,  mod(9/4) = 1
        pi()                         pi constant, 3.14159265358979
        power(a dp, b dp)            a raised to the power of b, power(9,3)= 729
        power(a numeric, b numeric)

        radians(dp)              degrees to radians, radians(45.0) = 0.785398163397448
        round(dp or numeric)     round to nearest integer, round(42.4) = 42

        scale(numeric)           scale of the argument (the number of decimal
                                 digits in the fractional part)
                                 scale(8.41) = 2

        sign(dp or numeric)      sign of the argument (-1,0,+1), sign(-8.4)= -1
        sqrt(dp)                 square root, sqrt(2) = 1.4142135623731
        trunc(dp)                truncate toward zero, trunc(42.8) = 42
        trunc(v numeric, s int)  truncate to s decimal places, trunc(42.43822) = 42.43

        width_bucket(dp, dp, dp, int)   return the bucket number to which
                                        operand would be assigned in a histogram
                                        having count equal-width buckets spanning
                                        the range b1 to b2; returns 0 or count+1
                                        for an input outside the range.
                                        width_bucket(5.35, 0.024, 10.06, 5)=3

        width_bucket(num, num, num, int)  return the bucket number to which
                                          operand would be assigned in a histogram
                                          having count equal-width buckets
                                          spanning the range b1 to b2; returns 0
                                          or count+1 for an input outside the
                                          range
                                          width_bucket(5.35, 0.024, 10.06, 5)=3

        width_bucket(any, anyarray)n   return the bucket number to which operand
                                       would be assigned given an array listing
                                       the lower bounds of the buckets;
                                       returns 0 for an input less than the first
                                       lower bound; the thresholds array must be
                                       shorted, smallest first, or unexpected
                                       result will be obtained.
*/

SELECT abs(-17.4);  -- =17.4
SELECT cbrt(27.0);  -- =3
SELECT ceil(-42.8); -- =-42
SELECT ceiling(-95.3); -- =-95
SELECT degrees(0.5);   -- =28.6478897565412
SELECT div(9, 4);   -- =2
SELECT exp(1.0); -- =2.7182818284590452
SELECT floor(-42.8); -- =-43
