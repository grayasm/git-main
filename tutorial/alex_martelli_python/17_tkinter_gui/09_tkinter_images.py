#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag 414
import os
import tkinter


root = tkinter.Tk()
L = tkinter.Listbox(selectmode=tkinter.SINGLE)
gifsdict = {}

dirpath = 'imgs'  # subdirectory with gif files
for gifname in os.listdir(dirpath):
    if not gifname[0].isdigit():
        continue
    gifpath = os.path.join(dirpath, gifname)
    gif = tkinter.PhotoImage(file=gifpath)
    gifsdict[gifname] = gif
    L.insert(tkinter.END, gifname)

L.pack()
img = tkinter.Label()
img.pack()


def list_entry_clicked(*ignore):
    imgname = L.get(L.curselection()[0])
    img.config(image=gifsdict[imgname])


L.bind('<ButtonRelease-1>', list_entry_clicked)
root.mainloop()
