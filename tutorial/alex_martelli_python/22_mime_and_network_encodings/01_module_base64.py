#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/base64.html
import base64
encoded = base64.b64encode(b'data to be encoded')
print('encoded:', encoded)

data = base64.b64decode(encoded)
print('decoded:', data)
