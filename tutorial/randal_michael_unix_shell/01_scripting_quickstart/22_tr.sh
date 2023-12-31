#!/bin/bash

VARIABLE="A possIBLe INpuT"

# Upcasing
UPCASEVAR=$(echo $VARIABLE | tr '[a-z]' '[A-Z]')

# Downcasing
DOWNCASEVAR=$(echo $VARIABLE | tr '[A-Z]' '[a-z]')


echo "\$VARIABLE=$VARIABLE"             # A possIBLe INpuT
echo "\$UPCASEVAR=$UPCASEVAR"           # A POSSIBLE INPUT
echo "\$DOWNCASEVAR=$DOWNCASEVAR"       # a possible input
