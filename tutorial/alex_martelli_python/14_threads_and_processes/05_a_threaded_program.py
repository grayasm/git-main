#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import threading
import queue


class ExternalInterfacing(threading.Thread):
    def __init__(self, externalCallable, **kwds):
        threading.Thread.__init__(self, **kwds)
        self.setDaemon(1)
        self.externalCallable = externalCallable
        self.workRequestQueue = queue.Queue()
        self.start()

    def request(self, *args, **kwds):
        "called by other threads as externalCallable would be"
        q = queue.Queue()
        self.workRequestQueue.put((q, args, kwds))
        return q.get()

    def run(self):
        while 1:
            q, args, kwds = self.workRequestQueue.get()
            q.put(self.externalCallable(*args, **kwds))


class Serializer(threading.Thread):
    def __init__(self, **kwds):
        threading.Thread.__init__(self, **kwds)
        self.setDaemon(1)
        self.workRequestQueue = queue.Queue()
        self.start()

    def apply(self, callable, *args, **kwds):
        "called by other threads as callable would be"
        q = queue.Queue()
        self.workRequestQueue.put((q, callable, args, kwds))
        return q.get()

    def run(self):
        while 1:
            q, callable, args, kwds = self.workRequestQueue.get()
            q.put(callable(*args, **kwds))


class Worker(threading.Thread):
    requestID = 0

    def __init__(self, requestQueue, resultsQueue, **kwds):
        threading.Thread.__init__(self, **kwds)
        self.setDaemon(1)
        self.workRequestQueue = requestQueue
        self.resultsQueue = resultsQueue
        self.start()

    def performWork(self, callable, *args, **kwds):
        "called by the main thread as callable would be, but w/o return"
        Worker.requestID += 1
        self.workRequestQueue.put((Worker.requestID, callable, args, kwds))
        return Worker.requestID

    def run(self):
        while 1:
            requestID, callable, args, kwds = self.workRequestQueue.get()
            self.resultQueue.put((requestID, callable(*args, **kwds)))


requestsQueue = queue.Queue()
resultsQueue = queue.Queue()
numberOfWorkers = 10
for i in range(numberOfWorkers):
    worker = Worker(requestsQueue, resultsQueue)
