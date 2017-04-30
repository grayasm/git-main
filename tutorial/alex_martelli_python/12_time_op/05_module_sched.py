#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/sched.html
'''The sched module implements an event-scheduler, letting you easily deal,
along a single thread of execution, with events that may be scheduled in
either a “real” or a “simulated” time-scale. sched supplies a scheduler class.
'''

import sched
import time

s = sched.scheduler(time.time, time.sleep)


def print_time(a='default'):
    print("From print_time", time.time(), a)


def print_some_times():
    print(time.time())
    s.enter(10, 1, print_time)
    s.enter(5, 2, print_time, argument=('positional',))
    s.enter(5, 1, print_time, kwargs={'a': 'keyword'})
    s.run()
    print(time.time())


print_some_times()
