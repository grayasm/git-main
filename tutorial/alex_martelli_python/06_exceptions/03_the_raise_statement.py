#
# *** The 'raise' Statement
#
'''
raise [expression1[, expression2]]
'''

# A plain raise statement re-raises the same exception object
# that the handler received.
try:
    try:
        try:
            raise Exception, "una exceptione"
        except:
            print "First Handler"
            raise
    except:
        print "Second Handler"
        raise
except:
    print "Last Handler"


# Tipical example of the 'raise' Statement
def crossProduct(seq1, seq2):
    if not seq1 or not seq2:
        raise ValueError, "Sequence arguments must be non-empty"
    return [(x1, x2) for x1 in seq1 for x2 in seq2]
