#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# /usr/lib64/python3.3/tkinter/messagebox.py
# https://www.tutorialspoint.com/python/tk_messagebox.htm
import tkinter
from tkinter import messagebox


top = tkinter.Tk()


def hello():
    messagebox.showinfo("Say Hello", "Hello World")


B1 = tkinter.Button(top, text="Say Hello", command=hello)
B1.pack()

top.mainloop()
