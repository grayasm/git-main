+-------------------------------------------------------------------+
        Implementing a barrier.

    Simple barrier implementation different than the actual real code
    in pthreads.h:
       pthread_barrier_t
       pthread_barrier_init, pthread_barrier_destroy, pthread_barrier_wait,
       pthread_barrier_attr
       pthread_barrierattr_init, pthread_barrierattr_destroy
       pthread_barrierattr_{get,set}pshared
+-------------------------------------------------------------------+
        7.1.2 Read/write locks

    Implements sharing variable with multiple read access and exclusive
    write access.
    file: rwlock.h
+-------------------------------------------------------------------+
