*
  A computer might be able to fetch a datum from memory, multiply two
  floating-point numbers, and evaluate a branch condition all at the same time.
  This is a very low level of parallel processing and is often referred to as
  “instruction-level parallelism” or ILP.
  A processor that supports this is said to have a superscalar architecture.

  1.1. Parallel Computers
  -----------------------
  IBM’s Power5, AMD’s Opteron and Sun’s UltraSPARC IV, IV+, and T1 processors
  go even further, replicating substantial parts of a processor’s logic on a
  single chip and behaving much like shared-memory parallel machines.
  This approach is known as multicore.


  1.2 Shared-Memory Parallel Computers
  ------------------------------------
  We will refer to shared-memory parallel computers as SMPs.

  SMP: a symmetric multiprocessor system, a shared-memory parallel computer
       whose individual processors share memory (and I/O) in such a way
       that each of them can access any memory location with the same speed;
       that is, they have a uniform memory access (UMA) time.

  NUMA: (or cc-NUMA) a non-uniform memory access system;
        Larger shared-memory machines, however, usually do not satisfy
        SMP definition; even though the difference may be relatively small,
        some memory may be “nearer to” one or more of the processors and
        thus accessed faster by them. We say that such machines have
        cache-coherent non-uniform memory access (cc-NUMA).

  1.2.1 Cache Memory Is Not Shared
  --------------------------------
  Speed: CPU got faster but the memory access didn't.
  Design: The CPU got a private built-in cache memory to be fed faster.
          Each SMP needs its own private cache, so not all memory is shared.
          Level 1 cache is faster than Level 2.

  CPU:
          LEVEL 1 Cache (Private to one core, fast access):
                + data         "Data Cache"
                + instructions "Instruction Cache"
                + TLB          "Translation Lookaside Buffer" address cache.

          LEVEL 2 Cache (Shared among cores, slower access):
                + Shared Unified Cache

  Main Memory: outside CPU (the slowest to access)

  The structure of a program influences the best usage of the CPU cache.
      When a processor of an SMP stores results of local computations in its
      private cache, the new values are accessible only to code executing on
      that processor. These data must be displaced from private cache into
      memory but the time is not known. The other cores may in fact access
      old data from memory and this is known as the "memory consistency problem"

      OpenMP memory model provides for shared and private data and specifies
      when updated shared values are guaranteed to be available to all of the
      code in an OpenMP program.

  1.4 What Is OpenMP?
  -------------------
  OpenMP is a shared-memory application programming interface (API).
  OpenMP is intended to be suitable for implementation on a broad range of
  SMP architectures (previous PCF X3H5 attempts wouldn't run on all SMP).
  OpenMP is not a new programming language but a notation.

  1.5 Creating an OpenMP Program
  ------------------------------
  OpenMP directive looks like a pragma to a C/C++ compiler, or FORTRAN comment.
  The first step in creating an OpenMP program from a sequential one is to
      identify the parallelism it contains. Sometimes the developer must
      reorganize portions of code to obtain independent instruction sequences.
  It can be applied incrementally into a portion of code, leaving the rest
      sequential.
  To investigate performance issues OpenMP provides techniques to specify the
      details down to each individual thread.

  1.6 The Bigger Picture
  ----------------------
  Other kinds of architectures exist to exploit parallelism

  Cyber-205, CRAY-1, Fujitsu Facom VP-200:
          vector computers that used the idea of pipelining instructions to
          apply the same operation to many data objects in turn

  CM2, MasPar:
          simultaneously applied the same operation to many data objects

  Intel’s iPSC series, nCUBE and Meiko:
          Connect multiple independent computers via a network.
          Memory is associated with each of the individual computers in
          the network and is thus distributed across the machine.
          These distributed-memory parallel systems are often referred to as
          massively parallel computers (MPPs) because very large systems can
          be put together this way. ( http://www.top500.org )

          If distributed-memory computers are designed with additional support
          that enables memory to be shared between all the processors, they are
          also SMPs according to our definition, and are often called
          DSM distributed shared-memory computers for their distinctive nature.

          When distributed-memory computers are constructed by using standard
          workstations or PCs and an off-the-shelf network, they are usually
          called clusters. Clusters, which are often composed of SMPs, are much
          cheaper to build than proprietary MPPs.

  1.7 Parallel Programming Models
  -------------------------------
  OpenMP (openmp) specific for SMP machines:
          Realizes a shared-memory (or shared address space) programming model.
          Shared-memory programs are executed by multiple independent threads.
          - starting up threads
          - assigning work to them
          - coordinating their accesses to shared data
          - certain operations can be performed by only one thread at a time

  Message Passing (MPI) specific for MPP machines (massive parallel computers):
          Programs will be executed by one or more processes, each of which
          has its own private address space.
          - initiate and manage the participating processes
          - operations for sending and receiving messages
          - performing special operations across data distributed among the
            different processes.
          - processes cooperate to exchange messages whenever one process
            needs data produced by another one.

  This book is based on OpenMP 2.5 specification.
  More info at the ARB website http://www.openmp.org
  User community website http://www.compunity.org
