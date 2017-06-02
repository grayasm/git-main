#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
threading provides numerous classes for dealing with threads, including Thread,
Condition, Event, RLock, and Semaphore. Besides factory functions for the
classes detailed in the following sections, threading supplies the
currentThread factory function.
'''

import threading


def worker(num):
    """thread worker function"""
    print('Worker: %s' % num)


threads = []
for i in range(5):
    t = threading.Thread(target=worker, args=(i,))
    threads.append(t)
    t.start()

'''
Worker: 0
Worker: 1
Worker: 2
Worker: 3
Worker: 4
'''

# see more at: https://pymotw.com/3/threading/
