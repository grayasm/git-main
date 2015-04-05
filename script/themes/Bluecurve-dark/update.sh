#!/bin/bash
DEST_CURVE=$HOME/Code/git-main/script/themes/Bluecurve-dark
if [ -d $DEST_CURVE ]; then
	cp -aRv ./*  $DEST_CURVE/
fi
