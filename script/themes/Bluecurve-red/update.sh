#!/bin/bash
DEST_CURVE_RED=$HOME/Code/git-main/script/themes/Bluecurve-red
if [ -d $DEST_CURVE_RED ]; then
	cp -aRv ./*  $DEST_CURVE_RED/
fi
