#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# /usr/lib64/python3.3/tkinter/simpledialog.py
# http://www.programcreek.com/python/example/6106/tkSimpleDialog.askstring

import tkinter
from tkinter import simpledialog
from tkinter import messagebox


# error: AttributeError: 'NoneType' object has no attribute 'winfo_viewable'
# solution: http://stackoverflow.com/questions/10205295/error-in-a-minimal-tksimpledialog-example
root = tkinter.Tk()
root.withdraw()


def getPassword(prompt='', confirm=0):
    while 1:
        try1 = simpledialog.askstring('Password Dialog', prompt, show='*')
        if not confirm:
            return try1
        try2 = simpledialog.askstring('Password Dialog', 'Confirm Password', show='*')
        if try1 == try2:
            return try1
        else:
            messagebox.showerror('Password Mismatch', 'Passwords did not match, starting over')


getPassword("change password", confirm=1)
