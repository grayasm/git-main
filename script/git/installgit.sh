#!/bin/bash

# need git
git --version 2>&1 >/dev/null
GIT_IS_AVAILABLE=$?
if [ $GIT_IS_AVAILABLE -ne 0 ]; then
    echo "install git"
    exit
fi

# need meld from Epel/Fedora (see: https://meldmerge.org/)
if [ ! -f /usr/bin/meld ]; then
    echo "install meld from epel or fedora"
    exit
fi

# git calls external diff with 7 parameters
# the wrapper script will discard 5 of them
cp -v git-diff-wrapper.sh  $HOME/.git-diff-wrapper.sh
chmod 755 $HOME/.git-diff-wrapper.sh

# configure external diff command
if [ ! -f $HOME/.gitconfig ]; then
    echo "create $HOME/.gitconfig"
    touch $HOME/.gitconfig
fi


grep -n '[diff]' $HOME/.gitconfig
if [ $? -eq 0 ]; then
    echo "$HOME/.gitconfig has [diff] section already; check it;"
    emacs $HOME/.gitconfig &
else
    printf '\n%s'   '[diff]' >> $HOME/.gitconfig
    printf '\n\t%s' 'external = ~/.git-diff-wrapper.sh' >> $HOME/.gitconfig
fi
