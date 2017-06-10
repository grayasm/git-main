#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/xmlrpc.server.html#simplexmlrpcserver-example
import xmlrpc.client


s = xmlrpc.client.ServerProxy('http://localhost:8000')
print(s.pow(2, 3))  # Returns 2**3 = 8
print(s.add(2, 3))  # Returns 5
print(s.mul(5, 2))  # Returns 5*2 = 10

# Print list of available methods
print(s.system.listMethods())
