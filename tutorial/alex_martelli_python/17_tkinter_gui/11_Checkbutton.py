#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/checkbutton.htm
import tkinter


master = tkinter.Tk()

var = tkinter.IntVar()

c = tkinter.Checkbutton(master, text="Expand", variable=var)
c.pack()

tkinter.mainloop()
