#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''DateTime is one of the modules in the mx package made available by eGenix
GmbH. mx is mostly open source, and, at the time of this writing, mx.DateTime
has liberal license conditions similar to those of Python itself. mx.DateTime’s
popularity stems from its functional richness and cross-platform portability.
'''

# do not install egenix-mx-base package with pip
# it patches setuptools in non standard way and later
# it cannot find correct packages on pip server

from mx import DateTime

d = DateTime(year,month=1,day=1,hour=0,minute=0,second=0.0)
