#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://gmpy2.readthedocs.io/en/latest/mpz.html
#
# yum install gmp-devel mpfr-devel libmpc-devel
# pip install gmpy2

import gmpy2
from gmpy2 import mpz


print(mpz('123') + 1)      # 124
print(10 - mpz(1))         # 9
print(gmpy2.is_prime(17))  # True
