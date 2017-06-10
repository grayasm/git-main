#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import os


shell = os.environ.get('COMSPEC')
if shell is None:
    shell = os.environ.get('SHELL')

if shell is None:
    shell = 'an unknown command processor'

print('Running under', shell)  # Running under /bin/bash
