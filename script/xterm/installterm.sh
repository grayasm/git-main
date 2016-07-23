#!/bin/bash

cp .Xdefaults $HOME/.Xdefaults
xrdb -merge $HOME/.Xdefaults

echo "DONE"
