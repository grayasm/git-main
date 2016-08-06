

        CAPTHER 4  A few ways to use threads.

1) PIPELINE
   Each thread repeatedly performs the same operation on a
   sequence of data sets, passing each result ot another thread for
   the next step. This is also known as an "assembly line".

2) WORK CREW
   Each thread performs an operation on its own data. Threads in
   a work crew may all perform the same operation, or each a separate
   operation, but they always proceed independently.

3) CLIENT / SERVER
   A client "contracts" with an independent server for each job.
   Often the "contract" is anonymous - a request is made through
   some interface that queues the work item.
