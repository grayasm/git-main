#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#class-reference
# http://effbot.org/tkinterbook/listbox.htm
import tkinter

master = tkinter.Tk()

listbox = tkinter.Listbox(master)
listbox.pack()

listbox.insert(tkinter.END, "a list entry")

for item in ["one", "two", "three", "four"]:
    listbox.insert(tkinter.END, item)

tkinter.mainloop()
