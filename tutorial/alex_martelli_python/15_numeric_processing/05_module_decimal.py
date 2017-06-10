#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://docs.python.org/3.3/library/decimal.html
import decimal


a = decimal.Decimal(1)
b = decimal.Decimal(7)

print('a / b = ', a / b)  # 0.1428571428571428571428571429
print(decimal.getcontext())
# Context(prec=28, rounding=ROUND_HALF_EVEN, Emin=-999999, Emax=999999,
#         capitals=1, clamp=0, flags=[Inexact, Rounded],
#         traps=[InvalidOperation, DivisionByZero, Overflow])

decimal.getcontext().prec = 28
print(decimal.Decimal(2).sqrt())      # 1.414213562373095048801688724

print(decimal.Decimal(1).exp())       # 2.718281828459045235360287471

print(decimal.Decimal('10').ln())     # 2.302585092994045684017991455

print(decimal.Decimal('10').log10())  # 1
