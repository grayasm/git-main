#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/nntplib.html
import nntplib


s = nntplib.NNTP('news.gmane.org')
resp, count, first, last, name = s.group('gmane.comp.python.committers')
print('Group', name, 'has', count, 'articles, range', first, 'to', last)

resp, overviews = s.over((last - 9, last))
for id, over in overviews:
    print(id, nntplib.decode_header(over['subject']))

s.quit()
