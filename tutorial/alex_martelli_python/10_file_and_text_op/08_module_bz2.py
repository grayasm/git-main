#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 232, The bz2 Module
#           The bz2 module lets you read and write files compatible with those
#           handled by the compression programs bzip2 and bunzip2 , which often
#           achieve even better compression than gzip and gunzip . Module bz2
#           supplies the BZ2File class, for transparent file compression and
#           decompression, and functions compress and decompress to compress
#           and decompress data strings in memory. It also provides objects to
#           compress and decompress data incrementally, enabling you to work
#           with data streams that are too large to comfortably fit in memory
#           at once.


#    https://pymotw.com/3/bz2/index.html
#    One-shot operations in memory
import bz2
import binascii

original_data = b'This is the original text.'
print('Original     : {} bytes'.format(len(original_data)))
print(original_data)

print()
compressed = bz2.compress(original_data)
print('Compressed   : {} bytes'.format(len(compressed)))
hex_version = binascii.hexlify(compressed)
for i in range(len(hex_version) // 40 + 1):
    print(hex_version[i * 40:(i + 1) * 40])

print()
decompressed = bz2.decompress(compressed)
print('Decompressed : {} bytes'.format(len(decompressed)))
print(decompressed)
