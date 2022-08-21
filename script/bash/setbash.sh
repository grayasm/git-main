#!/bin/bash

# check location
if [ "${PWD##*/}" != "bash" ]; then
    echo "switch to script directory!"
    exit
fi

[ -d $HOME/.bashrc.d ] || mkdir -v $HOME/.bashrc.d

cp -v bash_aliases  $HOME/.bashrc.d/bash_aliases
cp -v bash_nosave   $HOME/.bashrc.d/bash_nosave
cp -v bash_i3       $HOME/.bashrc.d/bash_i3
cp -v bash_gpg      $HOME/.bashrc.d/bash_gpg
cp -v bash_iptables $HOME/.bashrc.d/bash_iptables
