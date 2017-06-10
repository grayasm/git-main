#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#widget-construction-kit
# http://effbot.org/tkinterbook/grid.htm
import tkinter

master = tkinter.Tk()

tkinter.Label(master, text="First").grid(row=0, sticky=tkinter.W)
tkinter.Label(master, text="Second").grid(row=1, sticky=tkinter.W)

e1 = tkinter.Entry(master)
e2 = tkinter.Entry(master)

e1.grid(row=0, column=1)
e2.grid(row=1, column=1)

tkinter.mainloop()
