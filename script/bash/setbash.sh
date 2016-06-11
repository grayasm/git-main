#!/bin/bash

# verbose
set -x

# check location
if [ "${PWD##*/}" != "bash" ]; then
	echo "switch to script directory!"
	exit
fi

# copy files
cp -v $HOME/.bashrc $HOME/.bashrc.old
cp -v bash_aliases  $HOME/.bash_aliases
cp -v bash_nosave   $HOME/.bash_nosave
cp -v bashrc        $HOME/.bashrc
