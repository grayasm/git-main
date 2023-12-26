#!/bin/ksh

# Bash cannot perform floating point arithmetic natively.
# The alternative is to use external commands: bc, awk, Perl, Python, Ruby.

# Korn shell supports the following libm functions:

# abs       Absolute value
# log       Natural logarithm
# acos      Arc cosine
# sin       Sine
# asin      Arc sine
# sinh      Hyperbolic sine
# cos       Cosine
# sqrt      Square root
# cosh      Hyperbolic cosine
# tan       Tangent
# exp       Exponential function
# tanh      Hyperbolic tangent
# int       Integer part of floating-point number



# Korn example:
n=-5
m=$(( abs("$n") ))
echo "\$m=$m"           # 5


# Bash example
# https://tldp.org/LDP/abs/html/mathc.html
# Invoking 'bc' using command substitution in combination with a 'here document'.
r=-3.5
m=`bc << EOF
define abs(n){
    if ( n < 0 ) return -n;
    return n;
}
abs($r)
EOF
`
echo "\$m=$m"           # 3.5
