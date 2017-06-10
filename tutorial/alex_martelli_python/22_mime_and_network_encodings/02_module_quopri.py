#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://www.daniweb.com/programming/software-development/threads/211834/quopri-working-in-3-1
# using Python module quopri for MIME strings used in emails
# Python 3.1

import quopri


encoded = quopri.encodestring(b'data to be encoded')
print('encoded:', encoded)
print('of type:', type(encoded))


data = quopri.decodestring(encoded)
print('decoded:', data)
print('of type:', type(data))
