#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/entry.htm
import tkinter

master = tkinter.Tk()

e = tkinter.Entry(master)
e.pack()

e.focus_set()


def callback():
    print(e.get())


b = tkinter.Button(master, text="get", width=10, command=callback)
b.pack()

tkinter.mainloop()
