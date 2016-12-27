#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
sys.path.append("package1test")

from package1test import class1
from package1test import class2


myCls1 = class1()
myCls1.printMembers()

myCls2 = class2()
myCls2.printMembers()
