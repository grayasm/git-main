#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://www.programcreek.com/python/example/64776/tkColorChooser.askcolor
# /usr/lib64/python3.3/tkinter/colorchooser.py
import tkinter
from tkinter import colorchooser


def getColorRGB():
    try:
        colorTuple, color = colorchooser.askcolor()
        return colorTuple, color
    except tkinter._tkinter.TclError as errormsg:
        print("Exception: ", errormsg)


colorTuple, color = getColorRGB()
print("colorTuple=", colorTuple)
print("color     =", color)
