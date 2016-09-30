#!/bin/bash

# need subversion
svn --version 2>&1 >/dev/null
SVN_IS_AVAILABLE=$?
if [ $SVN_IS_AVAILABLE -ne 0 ]; then
	echo "install subversion"
	exit
fi

# need bcompare (see: http://www.scootersoftware.com/download.php)
if [ ! -f /usr/bin/bcompare ]; then
	echo "install bcompare from http://www.scootersoftware.com"
	exit
fi

# svn calls external diff with 7 parameters
# the wrapper script will discard 5 of them
cp -v svn-diff-wrapper.sh  $HOME/.svn-diff-wrapper.sh
chmod 755 $HOME/.svn-diff-wrapper.sh

# configure external diff command
echo "diff-cmd=~/.svn-diff-wrapper.sh"
emacs $HOME/.subversion/config
