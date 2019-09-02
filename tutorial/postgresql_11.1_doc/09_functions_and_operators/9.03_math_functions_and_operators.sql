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


/*     Mathematical functions work with double precision or numeric arguments.

       Function      Description
       -----------+-----------------
       abs(x)        Absolute value
       cbrt(x)       Cube root
       ceil(x)       Nearest integer greater than or equal to argument
       ceiling(x)    (same as ceil)
       degrees(x)    Radians to degrees
       div(y,x)      Integer quotient of y/x
       exp(x)        Exponential (e at power x)
       floor(x)      Nearest integer less than or equal to argument
       ln(x)         Natural logarithm
       log(x)        Base 10 logarithm
       log(b,x)      Logarithm to base b
       mod(y,x)      Remainder of y/x
       pi()          pi constant
       power(a,b)    a raised to the power of b
       radians(x)    Degrees to radians
       round(x)      Round to nearest integer
       round(v,s)    Round to s decimal places
       scale(x)      The number of the decimal digits in the fractional part
       sign(x)       Sign of the argument
       sqrt(x)       Square root
       trunc(x)      Truncate toward zero
       trunc(v,s)    Truncate to s decimal places
       width_bucket(x,b1,b2,count): Return the bucket number to which x would be
                     assigned in a histogram having count equal-width buckets
                     spanning the range b1 to b2; returns 0 or count+1 for an
                     input outside the range
       width_bucket(anyelem, anyarray): Return teh bucket number to which
                     anyelem would be assigned given an array listing the lower
                     bounds of the buckets; returns 0 for an input less than
                     the first lower bound; the thresholds array must be sorted,
                     smallest first, or unexpected results will be obtained.
       -------------------------------
*/
SELECT abs(-17.4); -- 17.4
SELECT cbrt(27.0); -- 3
SELECT ceil(-42.8); -- -42
SELECT ceiling(-95.3); -- -95
SELECT degrees(0.5); -- 28.6478897565412
SELECT div(9,4); -- 2
SELECT exp(1.0); -- 2.7182818284590452
SELECT floor(-42.8); -- -43
SELECT ln(2.0); -- 0.6931471805599453
SELECT log(100.0); -- 2
SELECT log(2.0, 64.0); -- 6
SELECT mod(9,4); -- 1
SELECT pi(); -- 3.14159265358979
SELECT power(9.0, 3.0); -- 729
SELECT radians(45.0); -- 0.785398163397448
SELECT round(42.4); -- 42
SELECT round(42.4382, 2); -- 42.44
SELECT scale(8.41); -- 2
SELECT sign(-8.4); -- -1
SELECT sqrt(2.0); -- 1.414213562373095
SELECT trunc(42.8); -- 42
SELECT trunc(42.4382, 2); -- 42.43
SELECT width_bucket(5.35, 0.024, 10.06, 5); -- 3
SELECT width_bucket(now(), array['yesterday', 'today', 'tomorrow']::timestamptz[]); -- 2


/*     Random functions.

       Function      Description
       -----------+-----------------
       random()      Random value in the range [0.0, 1.0)
       setseed(x)    Set seed for subsequent random() calls, x in [-1.0,+1.0]
       -----------------------------
*/

SELECT setseed(0.5);
SELECT random(); -- 0.798512778244913
SELECT random(); -- 0.518533017486334
SELECT random(); -- 0.0734698106534779


/*     Trigonometric functions.

       Function(radians) Function(degrees)  Description
       -----------------+-----------------+-------------------
       acos(x)           acosd(x)           Inverse cosine
       asin(x)           asind(x)           Inverse sine
       atan(x)           atand(x)           Inverse tangent
       atan2(y,x)        atan2d(y,x)        Inverse tangent of y/x
       cos(x)            cosd(x)            Cosine
       cot(x)            cotd(x)            Cotangent
       sin(x)            sind(x)            Sine
       tan(x)            tand(x)            Tangent
       -------------------------------------------------------
*/

SELECT cos(pi()); -- (-1)
SELECT acos(-1);  -- 3.14159265358979
SELECT cosd(180); -- (-1)
SELECT acosd(-1); -- 180
SELECT sin(pi()/2); -- 1
SELECT asin(1); -- 1.5707963267949  (~pi/2)
SELECT sind(90); -- 1
SELECT asind(1); -- 90
SELECT tan(pi()/2); -- 1.63312393531954e+16
SELECT atan(1.63312393531954e+16); -- 1.5707963267949 (~pi/2)
SELECT tand(90); -- Infinity
SELECT atand(9999999); -- 89.9999942704215

/*     Note:
       Another way to work with angles measured in degrees is to use the unit
       transformation functions radians() and degrees() shown earlier.
*/

SELECT cos(radians(45)); -- 0.707106781186548
SELECT degrees(acos(0.707106781186548)); -- 45
