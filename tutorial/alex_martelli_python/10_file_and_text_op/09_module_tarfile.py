#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 233, The tarfile Module
#           The tarfile module lets you read and write TAR files (archive files
#           compatible with those handled by popular archiving programs such
#           as tar ) optionally with either gzip or bzip2 compression.
#           For invalid TAR file errors, functions of module tarfile raise
#           exceptions that are instances of exception class tarfile.TarError


#    https://pymotw.com/2/tarfile/#creating-new-archives
#    Creating new archives

import tarfile

print ('creating archive')
out = tarfile.open('tarfile_add.tar', mode='w')
try:
    print ('adding 99_hello.txt')
    out.add('99_hello.txt')
finally:
    print ('closing')
    out.close()

print ()
print ('Contents:')
t = tarfile.open('tarfile_add.tar', 'r')
for member_info in t.getmembers():
    print (member_info.name)
