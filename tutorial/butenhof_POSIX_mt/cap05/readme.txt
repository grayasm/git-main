+-------------------------------------------------------------------+
	1. Never acquire resources while asynchronous cancellation is enabled.
	2. Never call any function while asynchronous cancellation is
              enabled unless the function si documented as "async-cancel safe"
	3. Thread specific data: pthread_key_t and the like.
	4. TLS: the order in which destructor functions are called is undefined.
		See: pthread_key_create(pthread_key_t* key, void (*destructor)(void*));

+-------------------------------------------------------------------+
   Cancellation points on any Pthreads system:
+-------------------------------------------------------------------+
        pthread_cond_wait               open
        pthread_cond_timedwait          pause
        pthread_join                    read
        pthread_testcancel              sem_wait
        sigwait                         sigwaitinfo
        aio_suspend                     sigsuspend
        close                           sigtimedwait
        creat                           sleep
        fcntl (F_SETLCKW)               system
        fsnc                            tcdrain
        mq_receive                      wait
        mq_send                         waitpid
        msync                           write
        nanosleep
+-------------------------------------------------------------------+
   Potential cancellation points for you system (read the documentation)
+-------------------------------------------------------------------+
        closedir                        getc_unlocked           printf
        ctermid                         getchar                 putc
        fclose                          getchar_unlocked        putc_unlocked
        fcntl (except F_SETLCKW)        getcwd                  putchar
        fflush                          getgrid                 putchar_unlocked
        fgetc                           getgrid_r               puts
        fgets                           getrtnam                readdir
        fopen                           getgrnam_r              remove
        fprintf                         getgrnam_r              rename
        fputc                           getlogin                rewind
        fputs                           getlogin_r              rewinddir
        fread                           getpwnam                scanf
        freopen                         getpwnam_r              tmpfile
        fscanf                          getpwuid                tmpname
        fseek                           getpwuid_r              ttyname
        ftell                           gets                    ttyname_r
        fwrite                          lseek                   ungetc
        getc                            opendir
+-------------------------------------------------------------------+
    5. Scheduling policies and priorities

       int sched_get_priority_{max,min}(int policy)
       int pthread_attr_{get,set}inheritsched(...)
       int pthread_attr_{get,set}schedparam(...)
       int pthread_attr_{get,set}schedpolicy(...)
       int pthread_{get,set}schedparam(...)
+-------------------------------------------------------------------+
    6. Contention scope and allocation domain

       int pthread_attr_{get,set}scope(...)
+-------------------------------------------------------------------+
    7. Priority-aware mutexes

       int pthread_mutexattr_{get,set}protocol(...)
       int pthread_mutexattr_{get,set}prioceiling(...)
       int pthread_mutex_{get,set}prioceiling(...)
+-------------------------------------------------------------------+
