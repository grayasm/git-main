*
  Chapter 4: OpenMP Language Features

  4.1 Introduction
  ----------------

  The following set of constructs are part of OpenMP language features:
  * Parallel Construct
  * Work-Sharing Constructs
      1. Loop Construct
      2. Sections Construct
      3. Single Construct
  * Data-Sharing, No Wait, Schedule Clauses
  * Barrier Construct
  * Critical Construct
  * Atomic Construct
  * Locks
  * Master Construct


4.2

  Structured Block:
  -----------------
OpenMP requires well-structured programs, and, as can be seen from the above,
constructs are associated with statements, loops, or structured blocks. In C/C++
a “structured block” is defined to be an executable statement, possibly a compound
1All directives except the threadprivate directive are executable directives.
OpenMP Language Features 53
statement, with a single entry at the top and a single exit at the bottom.


the point of entry cannot be a
labeled statement, and the point of exit cannot be a branch of any type

In C/C++ the following additional rules apply to a structured block:
• The point of entry cannot be a call to setjmp().
• longjmp() and throw() (C++ only) must not violate the entry/exit criteria.
• Calls to exit() are allowed in a structured block.
• An expression statement, iteration statement, selection statement, or try
block is considered to be a structured block if the corresponding compound
statement obtained by enclosing it in { and } would be a structured block.


  Region of Code:
  ---------------
“An OpenMP region consists of all code encountered
during a specific instance of the execution of a given OpenMP construct or library
routine. A region includes any code in called routines, as well as any implicit code
introduced by the OpenMP implementation.” In other words, a region encompasses
all the code that is in the dynamic extent of a construct.



  Binding Thread Set:
  -------------------
In
particular, some of the runtime library routines have an effect on the thread that
invokes them (or return information pertinent to that thread only), whereas others
are relevant to a team of threads or to all threads that execute the program. We
will discuss binding issues only in those few places where it is important or not
immediately clear what the binding of a feature is.


  4.3 Parallel Construct
  ----------------------
The thread that encounters the parallel construct becomes the master of the new
team.

Figure 4.5: Clauses supported by the parallel construct

if(scalar-expression) (C/C++)
num threads(integer-expression) (C/C++)
private(list)
firstprivate(list)
shared(list)
default(none|shared) (C/C++)
copyin(list)
reduction(operator:list) (C/C++)


There are several restrictions on the parallel construct and its clauses:

program that branches into or out of a parallel region is nonconforming.
In other words, if a program does so, then it is illegal, and the behavior is
undefined.
* A program must not depend on any ordering of the evaluations of the clauses
of the parallel directive or on any side effects of the evaluations of the clauses.
* At most one if clause can appear on the directive.
* At most one num threads clause can appear on the directive. The expression
for the clause must evaluate to a positive integer value.

    !!! In C++ there is an additional constraint. A throw inside a parallel region must
    cause execution to resume within the same parallel region, and it must be caught
    by the same thread that threw the exception.


The OpenMP standard distinguishes between an active parallel region and an
inactive parallel region. A parallel region is active if it is executed by a team of
OpenMP Language Features 57
threads consisting of more than one thread. If it is executed by one thread only, it
has been serialized and is considered to be inactive.
