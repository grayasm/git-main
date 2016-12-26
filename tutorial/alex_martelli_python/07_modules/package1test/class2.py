#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class class2(object):
    def __init__(self):
        '''Constructor for class2.'''
        self.members = ['Actinium', 'Thorium', 'Protactinium', 'Uranium',
                        'Neptunium', 'Plutonium', 'Americium', 'Curium',
                        'Berkelium', 'Californium', 'Einsteinium', 'Fermium',
                        'Mendelevium', 'Nobelium', 'Lawrencium']

    def printMembers(self):
        print 'Actininide Series:'
        for elem in self.members:
            print '\t%s ' % elem
