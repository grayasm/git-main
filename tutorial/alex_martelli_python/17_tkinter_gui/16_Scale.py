#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#class-reference
# http://effbot.org/tkinterbook/scale.htm
import tkinter

master = tkinter.Tk()

w = tkinter.Scale(master, from_=0, to=100)
w.pack()

w = tkinter.Scale(master, from_=0, to=200, orient=tkinter.HORIZONTAL)
w.pack()

tkinter.mainloop()
