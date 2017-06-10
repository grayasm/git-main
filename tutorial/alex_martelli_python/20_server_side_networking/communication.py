#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# this is imported into:
# 05_module_select-server.py &
# 06_module_select-client.py

# http://code.activestate.com/recipes/531824-chat-server-client-using-selectselect/
###############################################################################
# The communication module (communication.py)
###############################################################################
import cPickle
import socket
import struct

marshall = cPickle.dumps
unmarshall = cPickle.loads

def send(channel, *args):
    buf = marshall(args)
    value = socket.htonl(len(buf))
    size = struct.pack("L",value)
    channel.send(size)
    channel.send(buf)

def receive(channel):

    size = struct.calcsize("L")
    size = channel.recv(size)
    try:
        size = socket.ntohl(struct.unpack("L", size)[0])
    except struct.error as e:
        return ''
    
    buf = ""

    while len(buf) < size:
        buf = channel.recv(size - len(buf))

    return unmarshall(buf)[0]
