#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 265, Interactive Command Sessions
#           The cmd module offers a simple way to handle interactive sessions
#           of commands. Each command is a line of text. The first word of each
#           command is a verb defining the requested action. The rest of the
#           line is passed as an argument to the method that implements the
#           verb’s action.
#           Module cmd supplies class Cmd to use as a base class, and you
#           define your own subclass of cmd.Cmd. Your subclass supplies methods
#           with names starting with do_ and help_ , and may optionally
#           override some of Cmd ’s methods. When the user enters a command
#           line such as verb and the rest, as long as your subclass defines
#           a method named do_verb, Cmd.onecmd calls:
#           self.do_verb('and the rest')
#           Similarly, as long as your subclass defines a method named
#           help_verb, Cmd.do_help calls the method when the command line
#           starts with 'help verb' or '?verb'
#           Cmd, by default, shows suitable error messages if the user tries
#           to use, or asks for help about, a verb for which the subclass does
#           not define the needed method.


#     https://docs.python.org/3/library/cmd.html#cmd-example
#     The cmd module is mainly useful for building custom shells that let a
#     user work with a program interactively. This section presents a simple
#     example of how to build a shell around a few of the commands in the
#     turtle module.
import cmd
import sys
from turtle import *


class TurtleShell(cmd.Cmd):
    intro = 'Welcome to the turtle shell.   Type help or ? to list commands.\n'
    prompt = '(turtle) '
    file = None

    # ----- basic turtle commands -----
    def do_forward(self, arg):
        'Move the turtle forward by the specified distance:  FORWARD 10'
        forward(*parse(arg))

    def do_right(self, arg):
        'Turn turtle right by given number of degrees:  RIGHT 20'
        right(*parse(arg))

    def do_left(self, arg):
        'Turn turtle left by given number of degrees:  LEFT 90'
        left(*parse(arg))

    def do_goto(self, arg):
        'Move turtle to an absolute position with changing orientation.  GOTO 100 200'
        goto(*parse(arg))

    def do_home(self, arg):
        'Return turtle to the home position:  HOME'
        home()

    def do_circle(self, arg):
        'Draw circle with given radius an options extent and steps:  CIRCLE 50'
        circle(*parse(arg))

    def do_position(self, arg):
        'Print the current turle position:  POSITION'
        print('Current position is %d %d\n' % position())

    def do_heading(self, arg):
        'Print the current turle heading in degrees:  HEADING'
        print('Current heading is %d\n' % (heading(),))

    def do_color(self, arg):
        'Set the color:  COLOR BLUE'
        color(arg.lower())

    def do_undo(self, arg):
        'Undo (repeatedly) the last turtle action(s):  UNDO'

    def do_reset(self, arg):
        'Clear the screen and return turtle to center:  RESET'
        reset()

    def do_bye(self, arg):
        'Stop recording, close the turtle window, and exit:  BYE'
        print('Thank you for using Turtle')
        self.close()
        bye()
        return True

    # ----- record and playback -----
    def do_record(self, arg):
        'Save future commands to filename:  RECORD rose.cmd'
        self.file = open(arg, 'w')

    def do_playback(self, arg):
        'Playback commands from a file:  PLAYBACK rose.cmd'
        self.close()
        with open(arg) as f:
            self.cmdqueue.extend(f.read().splitlines())

    def precmd(self, line):
        line = line.lower()
        if self.file and 'playback' not in line:
            print(line, file=self.file)
        return line

    def close(self):
        if self.file:
            self.file.close()
            self.file = None


def parse(arg):
    'Convert a series of zero or more numbers to an argument tuple'
    return tuple(map(int, arg.split()))


if __name__ == '__main__':
    TurtleShell().cmdloop()
