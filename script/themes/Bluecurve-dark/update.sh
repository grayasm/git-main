#!/bin/bash
DEST_CURVE=$HOME/Code/git-main/script/themes/Bluecurve-dark
if [ ! -d $DEST_CURVE ]; then
	mkdir -v $DEST_CURVE
fi
cp -aRv ./*  $DEST_CURVE/