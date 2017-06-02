#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://docs.python.org/3/library/urllib.request.html#examples

import urllib.request


with urllib.request.urlopen('http://www.python.org/') as f:
    print(f.read(300))

with urllib.request.urlopen('http://www.python.org/') as f:
    print(f.read(100).decode('utf-8'))


req = urllib.request.Request(url='https://localhost/cgi-bin/test.cgi',
                             data=b'This data is passed to stdin of the CGI')
with urllib.request.urlopen(req) as f:
    print(f.read().decode('utf-8'))
