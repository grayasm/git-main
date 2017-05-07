#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/button.htm
import tkinter

master = tkinter.Tk()


def callback():
    print("click!")


b = tkinter.Button(master, text="OK", command=callback)
b.pack()


tkinter.mainloop()
