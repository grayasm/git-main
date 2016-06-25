*
  Chapter 4: OpenMP Language Features
  -----------------------------------
  Open constructs:

      1. Parallel Construct        (4.3)

      2. Work-Sharing Constructs
            2.1  Loop              (4.4.1)
            2.2  Sections          (4.4.2)
            2.3  Single            (4.4.3)

      3. Clauses to control Parallel and Work-Sharing Constructs (1. and 2.)
            3.1  Shared            (4.5.1)
            3.2  Private           (4.5.2)
            3.3  Lastprivate       (4.5.3)
            3.4  Firstprivate      (4.5.4)
            3.5  Default           (4.5.5)
            3.6  Nowait            (4.5.6)
            3.7  Schedule          (4.5.7)

      4.  Synchronization Constructs
            4.1  Barrier      (4.6.1)
            4.2  Ordered      (4.6.2)
            4.3  Critical     (4.6.3)
            4.4  Atomic       (4.6.4)
            4.5  Locks        (4.6.5)
            4.6  Master       (4.6.6)

      5.  More OpenMP Clauses
            5.1  If             (4.8.1)
            5.2  Num_threads    (4.8.2)
            5.3  Ordered        (4.8.3)
            5.4  Reduction      (4.8.4)
            5.5. Copyin         (4.8.5)
            5.6  Copyprivate    (4.8.6)

      6.  Advanced OpenMP Constructs
            6.1  Nested Parallelism         (4.9.1)
            6.2  Flush          Directive   (4.9.2)
            6.3  Threadprivate  Directive   (4.9.3)


  ==============================================================================
  2.1 Loops (4.4.1)
      - the for loop must be over an integer or similar (cannot be iterator)
      - the lower or upper bound must be known also
      - when these are provided then the compiler knows how many threads to
        assign for the loop
      - inside a loop, if working over a container it must be one with constant
        lookup time (vector 0(1), list O(N), map O(logN) , set O(logN))
      - if not a std::vector, a bidirectional iterator must be incremented
        all over from the beginning to the current i position
