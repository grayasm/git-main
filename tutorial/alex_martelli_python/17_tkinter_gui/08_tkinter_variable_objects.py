#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag.413
import tkinter


root = tkinter.Tk()
tv = tkinter.StringVar()
tkinter.Label(textvariable=tv).pack()
tkinter.Entry(textvariable=tv).pack()
tv.set('Welcome!')
tkinter.Button(text="Exit", command=root.quit).pack()

tkinter.mainloop()
print("Final value is ", tv.get)
