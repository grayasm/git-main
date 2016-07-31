#!/bin/bash

# verbose
set -x

# loaded when X11 program start, but only if xrdb has not been used in current session
cp .Xdefaults $HOME/.Xdefaults
xrdb -merge $HOME/.Xdefaults

# most Display Managers will load this on login
cp .Xdefaults $HOME/.Xresources

echo "DONE"
