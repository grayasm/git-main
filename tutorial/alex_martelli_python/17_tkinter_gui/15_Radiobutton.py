#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#class-reference
# http://effbot.org/tkinterbook/radiobutton.htm
import tkinter

master = tkinter.Tk()

v = tkinter.IntVar()

tkinter.Radiobutton(master, text="One", variable=v, value=1).pack(anchor=tkinter.W)
tkinter.Radiobutton(master, text="Two", variable=v, value=2).pack(anchor=tkinter.W)

tkinter.mainloop()
