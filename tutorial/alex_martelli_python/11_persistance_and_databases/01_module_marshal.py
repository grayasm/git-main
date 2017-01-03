#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 278, The marshal Module
#           The marshal module supports the specific serialization tasks needed
#           to save and reload compiled Python files (.pyc and .pyo).
#           marshal handles only fundamental built-in data types: None,
#           numbers (int, long, float, complex), strings (plain and Unicode),
#           code objects, and built-in containers (tuple, list, dict) whose
#           items are instances of elementary types.
#           marshal does not handle sets nor user-defined types and classes.
#           marshal is faster than other serialization modules, and is the one
#           such module that supports code objects.
