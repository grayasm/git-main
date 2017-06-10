#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://pymotw.com/3/subprocess/

import subprocess


stdoutdata = subprocess.getoutput("wc --lines 08_module_subprocess.py")
print("stdoutdata: " + stdoutdata.split()[0])


output = subprocess.check_output('echo to stdout; echo to stderr 1>&2',
                                 shell=True,
                                 stderr=subprocess.STDOUT,)
print('Have {} bytes in output: {!r}'.format(len(output),
                                             output.decode('utf-8')))
