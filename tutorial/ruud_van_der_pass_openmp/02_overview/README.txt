*
  2.2 The Idea of OpenMP
  ----------------------
  The fork-join model:
          - program starts with a single thread  ("initial thread")
          - parallel region forks a team of threads  ("the fork")
          - threads join at the end of parallel region ("the join")

  2.3 The Feature Set
  -------------------
  OpenMP provides means for the user to:
          - create teams of threads for parallel execution
          - specify how to share work among the members of a team
          - declare both shared and private variables
          - synchronize threads and enable them to perform certain operations
            exclusively (i.e., without interference by other threads).

  2.3.3 The OpenMP Memory Model
  -----------------------------
    Private variable:
          by default, data is shared among the threads and is visible to all.
          Sometimes, however, one needs variables that have thread-specific
          values. When each thread has its own copy of a variable, so that it
          may potentially have a different value for each of them, we say that
          the variable is private.
          Ex: when a team of threads executes a parallel loop, each thread needs
          its own value of the iteration variable. The use of private variables
          can reduce the frequency of updates to shared memory.
          Positive:  reduce the overhead for memory access.
          Negative:  increase thread stack (program's memory footprint).

    Shared objects:
          The values of shared objects must be made available to all threads at
          synchronization points. Between the synchronization points, threads
          may temporarily keep their updated values in local cache. As a result,
          threads may temporarily have different values for some shared objects.
          If one thread needs a value that was created by another thread,
          then a synchronization point must be inserted into the code.

    flush:
          synchronize memory.
          A flush operation makes sure that the thread calling it has the same
          values for shared data objects as does main memory. Hence, new values
          of any shared objects updated by that thread are written back to
          shared memory, and the thread gets any new values produced by other
          threads for the shared data it reads.
          In some programming languages, a flush is known as a memory fence,
          since reads and writes of shared data may not be moved relative to it.


  2.3.4 Thread Synchronization
  ----------------------------
    Barrier:
          by default, OpenMP gets threads to wait at the end of a worksharing
          construct or parallel region until all threads in the team executing
          it have finished their portion of the work.

    Atomic update feature:
          a thread attempts to execute code that is protected by a such a
          feature, and it is already being executed by another thread, then
          the former will have to wait for its turn.

    Synchronization points:
          the system ensures that threads have consistent values of shared
          data objects.
          - explicit and implicit barriers
          - the start and end of critical regions
          - points where locks are acquired or released
          - anywhere the programmer has inserted a flush directive


  2.4 OpenMP Programming Styles
  -----------------------------
    Implicit (using openmp directives):
          Relies heavily on distributing the work in loops among threads.
          The amount of loop-level parallelism in an application is limited.
          Parallelization leads to unacceptable overheads.

    Explicit:
          Assign work explicitly to different threads using their thread numbers
          Can lead to highly efficient code.
          The programmer must then insert synchronization manually to ensure
              that accesses to shared data are correctly controlled.
          Programming errors such as deadlock (when all threads wait for each
              other in perpetuity) may occur and must be avoided via careful
              code design.
          - give threads slightly different amounts of work
          - domain decomposition: split domain in subdomains, one per thread.
            This strategy is often referred to as
            SPMD (single program muliple data) programming.

  2.5 Correctness Considerations
  ------------------------------
    Data race condition:
          - silent data corruption
          - runtime behavior is not reproducible
          - two or more threads access the same shared variable without any
            synchronization to order the accesses, and at least one of the
            accesses is a write.
          - depends on the system load and the relative timing of the threads

    Incorrect number of threads:
          - wrote the code for 12 threads but execute on a 4 cores machine


  2.6 Performance Considerations
  ------------------------------
    T1 the execution time of an application on 1 processor.
    T1 / P execution time on P processors.
    S = T1/TP is referred to as the parallel speedup.
    S = 1 / ((fpar/P) + (1-fpar));  fpar - fraction of parallelized code.
       when all code is running in parallel-> fpar = 1 and P=8 cores
       S = 1 / (1/8 + 1-1) = 1 / (1/8) = 8
       when only 80% of code runs in parallel-> fpar = 0.8 and P=16 cores
       S = 1 / (0.8/16 + 1-0.8) = 4
