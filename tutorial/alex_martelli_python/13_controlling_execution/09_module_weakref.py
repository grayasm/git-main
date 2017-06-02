#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
Careful design can often avoid reference loops. However, at times you need two
objects to know about each other, and avoiding mutual references would distort
and complicate your design. For example, a container has references to its
items, yet it can often be useful for an object to know about a container
holding it. The result is a reference loop: due to the mutual references, the
container and items keep each other alive, even when all other objects forget
about them. Weak references solve this problem by letting you have objects that
mutually reference each other but do not keep each other alive. Alive objects
cannnot be garbage collected.
'''


# https://pymotw.com/3/weakref/
import weakref


class ExpensiveObject:
    def __del__(self):
        print('(Deleting {})'.format(self))


obj = ExpensiveObject()
r = weakref.ref(obj)

print('obj:', obj)   # obj: <__main__.ExpensiveObject object at 0x7f69a17e5
print('ref:', r)     # ref: <weakref at 0x7f69a9208a48; to 'ExpensiveObject'
print('r():', r())   # r(): <__main__.ExpensiveObject object at 0x7f69a17e5

print('deleting obj')
del obj              # (Deleting <__main__.ExpensiveObject object at 0x7f69
print('r():', r())   # r(): None


def callback(reference):
    """Invoked when referenced object is deleted"""
    print('callback({!r})'.format(reference))


obj = ExpensiveObject()
r = weakref.ref(obj, callback)

print('obj:', obj)   # obj: <__main__.ExpensiveObject object at 0x7f6d5090
print('ref:', r)     # ref: <weakref at 0x7f6d5095c7e0; to 'ExpensiveObject'
print('r():', r())   # r(): <__main__.ExpensiveObject object at 0x7f6d50903

print('deleting obj')
del obj              # callback(<weakref at 0x7f6d5095c7e0; dead>)
print('r():', r())   # r(): None


# and a lot more...
