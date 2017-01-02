#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 261, The curses package
#           The traditional Unix approach to advanced terminal I/O is named
#           curses, for obscure historical reasons. * The Python package curses
#           affords reasonably simple use, but still lets you exert detailed
#           control if required. I cover a small subset of curses , just enough
#           to let you write programs with rich-text I/O functionality.
#           Whenever I mention the screen in this section, I mean the screen of
#           the terminal (for example, the text window of a terminal-emulator
#           program). The simplest and most effective way to use curses is
#           through the curses.wrapper module, which supplies a single function.

from curses import wrapper

def main(stdscr):
    # Clear screen
    stdscr.clear()

    for i in range(0, 10):
        v = i+10
        stdscr.addstr(i, 0, '10 divided by {} is {}'.format(v, 10/v))

    stdscr.refresh()
    stdscr.getkey()

wrapper(main)
