#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# http://effbot.org/tkinterbook/tkinter-index.htm
# http://effbot.org/tkinterbook/tkinter-events-and-bindings.htm
# Capturing keyboard events
import tkinter


root = tkinter.Tk()


def key(event):
    print("pressed", repr(event.char))


def callback(event):
    frame.focus_set()
    print("clicked at x:", event.x, ", y:", event.y)


frame = tkinter.Frame(root, width=450, height=300)
frame.bind("<Key>", key)
frame.bind("<Button-1>", callback)
frame.pack()

root.mainloop()
