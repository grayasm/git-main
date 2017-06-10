#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 235, The zipfile Module
#           The zipfile module lets you read and write ZIP files (i.e., archive
#           files compatible with those handled by popular compression programs
#           zip and unzip , pkzip and pkunzip , WinZip , and so on).
#           Detailed information on the formats and capabilities of ZIP files
#           can be found at
#           http://www.pkware.com/appnote.html and
#           http://www.info-zip.org/pub/infozip/.
#           You need to study this detailed information in order to perform
#           advanced ZIP file handling with module zipfile. If you do not
#           specifically need to interoperate with other programs using the ZIP
#           file standard, modules gzip and bz2 are most often preferable ways
#           to handle compressed-file needs. Module zipfile can’t handle ZIP
#           files with appended comments, multidisk ZIP files, or .zip archive
#           members using compression types besides the usual ones, known as
#           stored (a file copied to the archive without compression) and
#           deflated (a file compressed using the ZIP format’s default
#           algorithm). For errors related to invalid .zip files, functions of
#           module zipfile raise exceptions that are instances of exception
#           class zipfile.error


#    https://pymotw.com/2/zipfile/#creating-new-archives
#    Creating new archives

import zipfile
import datetime


def print_info(archive_name):
    zf = zipfile.ZipFile(archive_name)
    for info in zf.infolist():
        print (info.filename)
        print ('\tComment:\t', info.comment)
        print ('\tModified:\t', datetime.datetime(*info.date_time))
        print ('\tSystem:\t\t', info.create_system, '(0 = Windows, 3 = Unix)')
        print ('\tZIP version:\t', info.create_version)
        print ('\tCompressed:\t', info.compress_size, 'bytes')
        print ('\tUncompressed:\t', info.file_size, 'bytes')
        print ()


print ('creating archive')
zf = zipfile.ZipFile('zipfile_write.zip', mode='w')
try:
    print ('adding 99_hello.txt')
    zf.write('99_hello.txt')
finally:
    print ('closing')
    zf.close()

print ()
print_info('zipfile_write.zip')
