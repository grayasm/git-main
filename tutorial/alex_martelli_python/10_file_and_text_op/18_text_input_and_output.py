#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 256, Text Input and Output
#           Python presents non-GUI text input and output channels to your
#           programs as file objects, so you can use the methods of file
#           objects (covered in “Attributes and Methods of File Objects”
#           on page 218) to manipulate these channels.

import sys

sys.stdout = open('file', 'w')
print ('test')
