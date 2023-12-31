#!/bin/bash

# We often need to test text strings like filenames, variables, file text
# and so on, for comparison. It can sometimes vary so widely that it is
# easier to uppercase or lowercase the text for ease of comparison.
#
# tr - translate or delete characters
# tr [OPTION] ... SET1 [SET2]


VARIABLE="A possIBLe INpuT"

# Upcasing
UPCASEVAR=$(echo $VARIABLE | tr '[a-z]' '[A-Z]')

# Downcasing
DOWNCASEVAR=$(echo $VARIABLE | tr '[A-Z]' '[a-z]')


echo "\$VARIABLE=$VARIABLE"             # A possIBLe INpuT
echo "\$UPCASEVAR=$UPCASEVAR"           # A POSSIBLE INPUT
echo "\$DOWNCASEVAR=$DOWNCASEVAR"       # a possible input
