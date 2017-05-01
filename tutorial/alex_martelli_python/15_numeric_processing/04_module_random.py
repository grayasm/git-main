#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3.0/library/random.html

import random

for i in range(10):
    print('random.random() = ', random.random())

for i in range(10):
    print('random.randint(1, 10) = ', random.randint(1, 10))

for i in range(3):
    print('random.randrange(0, 11, 2) = ', random.randrange(0, 11, 2))

for i in range(3):
    print('random.choice("abcdefghijkl") = ', random.choice('abcdefghijkl'))

items = [1, 2, 3, 4, 5, 6, 7]
random.shuffle(items)
print(items)    # [4, 7, 5, 1, 3, 2, 6]
