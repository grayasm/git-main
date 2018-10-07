#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# pag.458
""" This module tests function reverseWords provided by module mod.py. """
import unittest
import mod


class ModTest(unittest.TestCase):
    def testNormalCase(self):
        self.assertEqual(mod.reverseWords('four score and seven years'),
                         'years seven and score four')

    def testSingleWord(self):
        self.assertEqual(mod.reverseWords('justoneword'), 'justoneword')

    def testEmpty(self):
        self.assertEqual(mod.reverseWords(''), '')

    def testRedundantSpacing(self):
        self.assertEqual(mod.reverseWords('with spacing redundant'),
                         'with redundant spacing'),

    def testUnicode(self):
        self.assertEqual(mod.reverseWords(u'unicode is all right too'),
                         u'too right all is unicode')

    def testExactly1Argument(self):
        self.assertRaises(TypeError, mod.reverseWords)
        self.assertRaises(TypeError, mod.reverseWords, 'one', 'another')

    def testMustBeString(self):
        self.assertRaises((AttributeError, TypeError), mod.reverseWords, 1)


if __name__ == '__main__':
    unittest.main()
