#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# pag.423
import tkinter


root = tkinter.Tk()
var = tkinter.StringVar()
entry = tkinter.Entry(root, textvariable=var)
entry.focus_set()
entry.pack()
var.set(root.title())


def changeTitle():
    root.title(var.get())


tkinter.Button(root, text="Change Title", command=changeTitle).pack()
tkinter.Button(root, text="Iconify", command=root.iconify).pack()
tkinter.Button(root, text="Close", command=root.destroy).pack()
tkinter.mainloop()
