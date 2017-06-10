#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm#class-reference
# http://effbot.org/tkinterbook/scrollbar.htm
import tkinter

master = tkinter.Tk()

scrollbar = tkinter.Scrollbar(master)
scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)

listbox = tkinter.Listbox(master, yscrollcommand=scrollbar.set)
for i in range(1000):
    listbox.insert(tkinter.END, str(i))
listbox.pack(side=tkinter.LEFT, fill=tkinter.BOTH)

scrollbar.config(command=listbox.yview)

tkinter.mainloop()
