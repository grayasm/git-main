#!/bin/bash

# copy from ~/.themes/Blucurve-m to git location.
DEST_CURVE_M=$HOME/Code/git-main/script/themes/Bluecurve-m
if [ -d $DEST_CURVE_M ]; then
	cp -aRv ./*  $DEST_CURVE_M/
fi
