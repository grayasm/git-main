#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 264, The msvcrt Module
#           The msvcrt module, available only on Windows, supplies functions
#           that let Python programs access a few proprietary extras supplied
#           by the Microsoft Visual C++’s runtime library msvcrt.dll.
#           Some msvcrt functions let you read user input character by
#           character rather than reading a full line at a time.

import msvcrt

print ("press 'escape' to quit...")

while 1:
    char = msvcrt.getch()
    if char == chr(27):
        break
    print (char, end="")
    if char == chr(13):
        print ()
