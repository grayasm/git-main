#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://www.programcreek.com/python/example/4281/tkFileDialog.askopenfilename
# /usr/lib64/python3.3/tkinter/filedialog.py
from tkinter import filedialog


def openfile():
    opts = {}
    opts['filetypes'] = [('EEG files', '.eeg'), ('all files', '.*')]
    s = filedialog.askopenfilename(**opts)
    return s


fpath = openfile()
print("file=", fpath)
