#!/bin/bash

# Combine ssh with a command to execute on the remote
# ssh user@hostname command_to_execute
# ssh -l user hostname command_to_execute

# Example
ssh -l root -i $HOME/.ssh/id_rsa_do_01112021 $DIGITALOCEAN ls -la

# Enter passphrase for key '/home/<user>/.ssh/id_rsa_do_01112021':
# tput: No value for $TERM and no -T specified
# tput: No value for $TERM and no -T specified
# tput: No value for $TERM and no -T specified
# tput: No value for $TERM and no -T specified
# total 76
# dr-xr-x---.  5 root root  4096 Dec 27 00:15 .
# dr-xr-xr-x. 17 root root   224 Nov 21  2021 ..
# -rw-r--r--.  1 root root   918 Dec 27 00:13 .bash_aliases
# -rw-------.  1 root root 14137 Dec 27 00:15 .bash_history
# -rw-r--r--.  1 root root   494 Nov  1  2021 .bash_iptables
# -rw-r--r--.  1 root root    18 Mar 14  2021 .bash_logout
# -rw-r--r--.  1 root root   176 Mar 14  2021 .bash_profile
# -rw-r--r--.  1 root root   322 Nov  1  2021 .bashrc
