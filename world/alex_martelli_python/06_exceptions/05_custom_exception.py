#
# *** Custom Exception Classes ***
#
# Own exception class can subclass the standard exception classes.


class InvalidAttribute(AttributeError):
    "Used to indicate attributes that could never be valid"

try:
    raise InvalidAttribute
except Exception, e:
    '''So, what did I just caught'''
    print e.__doc__
# prints: Used to indicate attributes that could never be valid


# Custom Exceptions and Multiple Inheritance
class CustomException(Exception):
    pass


class CustomAttributeError(CustomException, AttributeError):
    pass
