.
   Header     : <condition_variable>
   Signature  : condition_variable();
                condition_variable(const condition_variable&) = delete;
   Description:
     - condition_variable is an object able to lock the calling thread until
       notified to resume
     - works only with std::unique_lock<std::mutex> which allows for max efficency
       on some platforms

   See also:
   condition_variable_any : http://www.cplusplus.com/reference/condition_variable/condition_variable_any

   Diagram:
   -----------------------------------------------------------------------------
   Thread 1               Kernel             Thread 2
   -----------------------------------------------------------------------------

   lock(mutex) ->         mx-locked

   wait(cond_var) ->      mx-unlocked
                          cv-unsignaled

                          mx-locked          <-- lock(mutex)

                          cv-signaled        <-- signal(cond_var)

                          mx-unlocked        <-- unlock(mutex)

   cv-signaled
   -----------------------------------------------------------------------------
