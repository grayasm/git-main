/usr/include/pthread.h
+-------------------------------------------------------------------+
        POSIX adjusts to threads
+-------------------------------------------------------------------+
    fork():

    Avoid using fork() in a threaded program unless you intend
    to exec a new program immediately.

    In a threaded program fork() will create a duplicate process (child)
    with a single thread - the one that called fork() in the parent.
    The  entire  virtual address  space  of  the  parent is replicated
    in the child, including the states of mutexes, condition variables,
    and other pthreads objects; the use of pthread_atfork(3) may be helpful
    for  dealing  with problems that this can cause.
+-------------------------------------------------------------------+
    exec():

    It wipes out the current program context and replaces it with a new
    program. It terminates all threads in the process except the thread
    calling exec(). The threads will not execute clean-up handlers or
    thread-specific data destructors - they simply cease to exist.
    All synchronization objects also vanish, except for pshared mutexes
    ( PTHREAD_PROCESS_SHARED attribute ).
+-------------------------------------------------------------------+
    exit(): - terminates the process and all threads
    pthread_exit(): - terminates only the running thread
+-------------------------------------------------------------------+
    Execute stdio operations in uninterrupted sequence:

    void  flockfile    (FILE *f)
    int   ftrylockfile (FILE *f)
    void  funlockfile  (FILE *f);
+-------------------------------------------------------------------+
    Efficiently (but incorrect) get and put single characters into
    stdio buffers. Functions _unlocked do not perform any locking,
    so you must use flockfile , funlockfile around any of them.

    int  getc_unlocked (FILE *f)
    int  putc_unlocked (int c, FILE *f)

    int  getchar_unlocked (void)
    int  putchar_unlocked (int c)
+-------------------------------------------------------------------+
	Signals with threads.
+-------------------------------------------------------------------+
    Semaphores.

    sem_init, sem_destroy, sem_open, sem_close, sem_unlink,
    sem_wait, sem_timedwait, sem_trywait, sem_post, sem_getvalue
+-------------------------------------------------------------------+
