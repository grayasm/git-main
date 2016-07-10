*
  This chapter is not part of the book:
  "Using OpenMP - Portable Shared Memory Parallel Programming".

  This chapter contains methods I found in my local omp.h at:
  /usr/lib/gcc/x86_64-redhat-linux/4.8.2/include/omp.h

  omp3.1 specifications: 2.3.2 Modifying and retrieving ICV values
                               (Internal Control Variables)

  modify                 retrieve                initial value
  OMP_DYNAMIC
  omp_set_dynamic()      omp_get_dynamic()

  OMP_NESTED
  omp_set_nested()       omp_get_nested()        false

  OMP_NUM_THREADS
  omp_set_num_threads()  omp_get_max_threads()   implem. defined

  OMP_SCHEDULE
  omp_set_schedule()     omp_get_schedule()      implem. defined

  OMP_PROC_BIND                                  implem. defined

  OMP_STACKSIZE                                  implem. defined

  OMP_WAIT_POLICY                                implem. defined

  OMP_THREAD_LIMIT       omp_get_thread_limit()  implem. defined

  OMP_MAX_ACTIVE_LEVELS
  omp_set_max_active_levels()  omp_get_max_active_levels()  implem. defined
