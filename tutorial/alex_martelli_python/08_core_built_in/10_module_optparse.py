#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# The optparse Module
#
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

# OptionParser.add_option(opt_str, *opt_strs, **kw)
# OptionParser.parse_args(args=sys.argv[1:])
