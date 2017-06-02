#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
Tkinter makes it easy to build simple GUI applications. You import Tkinter ,
create, configure, and position the widgets you want, then enter the Tkinter
main loop. Your application becomes event-driven: the user interacts with the
widgets, causing events, and your application responds via the functions you
installed as handlers for these events.
'''

# yum install python3-tkinter

import sys
import tkinter


tkinter.Label(text="Welcome!").pack()
tkinter.Button(text="Exit", command=sys.exit).pack()
tkinter.mainloop()
