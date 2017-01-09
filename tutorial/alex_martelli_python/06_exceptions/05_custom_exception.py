#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 132, Custom Exception Classes
#           You can subclass any of the standard exception classes in order
#           to define your own exception class.


# Own exception class can subclass the standard exception classes.
class InvalidAttribute(AttributeError):
    "Used to indicate attributes that could never be valid"


try:
    raise InvalidAttribute
except Exception as e:
    '''So, what did I just caught'''
    print (e.__doc__)         # Used to indicate attributes ...


# *** Custom Exceptions and Multiple Inheritance ***
class CustomException(Exception):
    pass


class CustomAttributeError(CustomException, AttributeError):
    pass
