#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 239, The zlib Module
#           The zlib module lets Python programs use the free InfoZip zlib
#           compression library (http://www.info-zip.org/pub/infozip/zlib/),
#           version 1.1.3 or later. Module zlib is used by modules gzip and
#           zipfile , but is also available directly for any special
#           compression needs.


#    http://effbot.org/librarybook/zlib.htm
#    Using the zlib module to compress a string
import zlib
import glob

MESSAGE = bytes("life of brian", "utf-8")

compressed_message = zlib.compress(MESSAGE)
decompressed_message = zlib.decompress(compressed_message)

print ("original:", repr(MESSAGE))
print ("compressed message:", repr(compressed_message))
print ("decompressed message:", repr(decompressed_message))


#    http://effbot.org/librarybook/zlib.htm
#    Using the zlib module to compress a group fo files.

for file in glob.glob("../10_file_and_text_op/*"):
    indata = open(file, "rb").read()
    outdata = zlib.compress(indata, zlib.Z_BEST_COMPRESSION)
    print (file, len(indata), "=>", len(outdata), end="")
    print ("%d%%" % (len(outdata) * 100 / len(indata)))
