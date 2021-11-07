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
cp -v bashrc        $HOME/.bashrc
cp -v bash_aliases  $HOME/.bash_aliases
cp -v bash_nosave   $HOME/.bash_nosave
cp -v bash_i3       $HOME/.bash_i3
cp -v bash_gpg      $HOME/.bash_gpg
cp -v bash_iptables $HOME/.bash_iptables
