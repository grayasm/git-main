#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 249, The stat Module
#           Function os.stat (covered in stat on page 244) returns instances of
#           stat_result , whose item indices, attribute names, and meaning are
#           covered in Table 10-2. The stat module supplies attributes with
#           names like those of stat_result ’s attributes, turned into
#           uppercase, and corresponding values that are the corresponding item
#           indices.
#           More interesting contents of module stat are functions that examine
#           the st_mode attribute of a stat_result instance to determine the
#           kind of file. os.path also supplies functions for such tasks, which
#           operate directly on the file’s path. The functions supplied by stat
#           are faster when they perform several tests on the same file: they
#           require only one os.stat call at the start of a series of tests,
#           while the functions in os.path implicitly ask the operating system
#           for the information at each test. Each function returns True if
#            mode denotes a file of the given kind; otherwise, False .


#    https://www.tutorialspoint.com/python3/os_stat.htm
#    Usage of stat() method

import os

statinfo = os.stat('99_hello.txt')
print (statinfo)    # os.stat_result(
                    # st_mode=33204,
                    # st_ino=655533,
                    # st_dev=2049,
                    # st_nlink=1,
                    # st_uid=1000,
                    # st_gid=1000,
                    # st_size=82,
                    # st_atime=1483080239,
                    # st_mtime=1480237566,
                    # st_ctime=1480237566)
