#!/bin/bash

# https://tldp.org/LDP/abs/html/ops.html


# The same arithmetic operators from the C programming language in decreasing
# order of precedence.

# ++ --         Auto-increment and auto-decrement, both prefix and postfix
# +             Unary plus
# -             Unary minus
# ! ~           Logical negation; binary inversion (one's complement)
# * / %         Multiplication; division; modulus (remainder)
# + -           Addition; subtraction
# << >>         Bitwise left shift; bitwise right shift
# <= >=         Less than or equal to; greater than or equal to
# < >           Less than; greater than
# == !=         Equality; inequality (both evaluated left to right)
# &             Bitwise AND
# ^             Bitwise exclusive OR
# |             Bitwise OR
# &&            Logical AND
# ||            Logical OR



n=20            # 20
(( ++n ))       # 21
(( n+=100 ))    # 121
(( r=n%99 ))    # 22
(( r=r<<2 ))    # 22<<2=88
echo "\$r=$r"   # 88
