#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#widget-construction-kit
# http://effbot.org/tkinterbook/pack.htm
import tkinter

root = tkinter.Tk()

w = tkinter.Label(root, text="Red", bg="red", fg="white")
w.pack(fill=tkinter.X)
w = tkinter.Label(root, text="Green", bg="green", fg="black")
w.pack(fill=tkinter.X)
w = tkinter.Label(root, text="Blue", bg="blue", fg="white")
w.pack(fill=tkinter.X)

tkinter.mainloop()
