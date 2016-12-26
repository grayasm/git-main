#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag.226, The linecache Module lets you read a given line (specified by number)
#          from a file with a given name, keeping an internal cache so that
#          if you read several lines from a file, it's faster than opening
#          and examining the file each time.

'''
linecache.checkcache()
linecache.clearcache()
linecache.getline(filename, lineno)
linecache.getlines(filename)
'''

import linecache

line = linecache.getline('99_eggs.txt', 2)
print "99_eggs.txt:2:%s" % line,
