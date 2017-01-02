#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 269, The locale Module
#           Python’s support for cultural conventions imitates that of C,
#           though it is slightly simplified. In this architecture, a program
#           operates in an environment of cultural conventions known as a
#           locale.
#           The locale setting permeates the program and is typically set at
#           program startup. The locale is not thread-specific, and module
#           locale is not thread-safe. In a multithreaded program, set the
#           program’s locale before starting secondary threads.
#           If a program does not call locale.setlocale , the program operates
#           in a neutral locale known as the C locale. The C locale is named
#           from this architecture’s origins in the C language and is similar,
#           but not identical, to the U.S. English locale. Alternatively, a
#           program can find out and accept the user’s default locale.
#           In this case, module locale interacts with the operating system
#           (via the environment or in other system-dependent ways) to
#           establish the user’s preferred locale.
#           Finally, a program can set a specific locale, presumably
#           determining which locale to set on the basis of user interaction
#           or via persistent configuration settings such as a program
#           initialization file.

import datetime
import locale
loc = locale.getlocale()  # get current locale

locale.setlocale(locale.LC_ALL, 'de_DE')
locale.strcoll('f\xe4n', 'foo')  # compare a string containing an umlaut
locale.setlocale(locale.LC_ALL, '')   # use user's preferred locale
locale.setlocale(locale.LC_ALL, 'C')  # use default (C) locale
locale.setlocale(locale.LC_ALL, loc)  # restore saved locale

print ("datetime: ", datetime.datetime.strptime(str(1), "%m").strftime("%B"))
