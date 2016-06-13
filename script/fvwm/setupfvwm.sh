#!/bin/bash

# verbose
set -x

# check location
if [ "${PWD##*/}" != "fvwm" ]; then
	echo "switch to script directory!"
	exit
fi

if [ ! -d $HOME/.fvwm ]; then
  mkdir $HOME/.fvwm
fi


cp -v fvwm2rc  $HOME/.fvwm/.fvwm2rc
cp -Rv icons   $HOME/.fvwm/
cp -Rv sounds  $HOME/.fvwm/
cp -Rv wallpapers $HOME/.fvwm/
