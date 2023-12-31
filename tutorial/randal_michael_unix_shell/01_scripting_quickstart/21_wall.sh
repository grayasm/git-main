#!/bin/bash


# The most common way to get information to the system users is to use
# the /etc/motd file. The file is displayed each time the user logs in.
# If users stay logged in for days at a time they will not see any new
# messages of the day. This is one reason why real-time communication is
# needed.


# wall          Writes a message on the screen of all logged-in users
#               on the local host.
# rwall         Writes a message on the screen of all logged-in users
#               on a remote host.
# write         Writes a message to an individual user. The user must
#               currently be logged in.
# talk          Starts an interactive program that allows two users
#               to have a conversation. The screen is split in two,
#               and both users can see what each person is typing.
