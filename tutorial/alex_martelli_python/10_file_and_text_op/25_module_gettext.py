#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 274, The gettext Module
#           A key issue in internationalization is the ability to use text in
#           different natural languages, a task also known as localization.
#           Python supports localization via module gettext , which was
#           inspired by GNU gettext. Module gettext is optionally able to use
#           the latter’s infrastructure and APIs, but is simpler and more
#           general. You do not need to install or study GNU gettext to use
#           Python’s gettext effectively.


#    1) Read the tutorial:
#       http://inventwithpython.com/blog/2014/12/20/translate-your-python-3-program-with-the-gettext-module/
#
#    2) The initial script is here:
#       http://inventwithpython.com/blogstatic/gettext/guess_original.py
#
#    3) Prepare all translatable strings "string" as _("string")
#
#    4) To original script add lines: 36-41
#
#    5) Create .pot file with help from /usr/bin/pygettext.py
#       pygettext.py -d 25_module_gettext  25_module_gettext.py
#
#    6) Create translated file .po with help from /usr/bin/poedit
#       mkdir ./locale/ro/LC_MESSAGES/
#       poedit -> File -> New Catalog from POT file -> 25_module_gettext.pot
#       Add translation for each entry and save file as:
#       ./locale/ro/LC_MESSAGES/25_module_gettext.po
#


import random
import gettext

ro = gettext.translation('25_module_gettext',
                         localedir='locale',
                         languages=['ro'])
ro.install()

guessesTaken = 0

print(_("Hello! What is your name?"))
myName = input()

number = random.randint(1, 20)
print(_("Well, %s, I am thinking of a number between 1 and 20.") % (myName))

while guessesTaken < 6:
    print(_("Take a guess."))
    guess = input()
    guess = int(guess)

    guessesTaken = guessesTaken + 1

    if guess < number:
        print(_("Your guess is too low."))

    if guess > number:
        print(_("Your guess is too high."))

    if guess == number:
        break

if guess == number:
    print(_("Good job, %s! You guessed my number in %d guesses!") % (myName, guessesTaken))

if guess != number:
    print(_("Nope. The number I was thinking of was %d.") % (number))
