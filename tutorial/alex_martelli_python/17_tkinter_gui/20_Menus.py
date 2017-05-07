#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 425
import tkinter


root = tkinter.Tk()
bar = tkinter.Menu()


def show(menu, entry):
    print(menu, entry)


fil = tkinter.Menu()
for x in 'New', 'Open', 'Close', 'Save':
    fil.add_command(label=x, command=lambda x=x: show('File', x))

bar.add_cascade(label='File', menu=fil)
edi = tkinter.Menu()

for x in 'Cut', 'Copy', 'Paste', 'Clear':
    edi.add_command(label=x, command=lambda x=x: show('Edit', x))


bar.add_cascade(label='Edit', menu=edi)
root.config(menu=bar)
tkinter.mainloop()
