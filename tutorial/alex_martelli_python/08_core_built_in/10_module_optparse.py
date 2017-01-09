#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 179, The optparse Module
#           The optparse module offers rich, powerful ways to parse the
#           command-line options (a.k.a. flags) that the user passed upon
#           starting your programs (by using syntax elements such as
#           –x or --foo=bar on the command line, after your program name and
#           before other program arguments).
#
# run: python3 10_module_optparse.py --help

'''
OptionParser.add_option(opt_str, *opt_strs, **kw)
OptionParser.parse_args(args=sys.argv[1:])
'''

from optparse import OptionParser

p = OptionParser()
p.add_option("-f", "--file",
             dest="filename",
             help="write report to FILE",
             metavar="FILE")
p.add_option("-q",
             "--quiet",
             action="store_false",
             dest="verbose",
             default=True,
             help="don't print status messages to stdout")

(options, args) = p.parse_args()
