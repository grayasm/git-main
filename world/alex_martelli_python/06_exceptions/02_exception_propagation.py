#
# *** Exception Propagation ***
def c():
    print "in c, before 1/0"
    1 / 0
    print "in c, after  1/0"


def b():
    print "in b, before c()"
    c()
    print "in b, after  c()"


def a():
    print "in a, before b()"
    try:
        b()
        print "in a, after b()"
    except ZeroDivisionError:
        print "ZD exception caught"
    print "function a ends"
a()
