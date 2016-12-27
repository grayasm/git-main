#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class class1(object):
    def __init__(self):
        '''Constructor for class1.'''
        self.members = ['Lanthanum', 'Cerium', 'Praseodymium',
                        'Neodymium', 'Promethium', 'Samarium',
                        'Europium', 'Gadolinum', 'Terbium',
                        'Dysprosium', 'Holmium', 'Erbium',
                        'Thulium', 'Ytterbium', 'Lutetium']

    def printMembers(self):
        print ("Lanthanide Series:")
        for elem in self.members:
            print ('\t%s ' % elem)
