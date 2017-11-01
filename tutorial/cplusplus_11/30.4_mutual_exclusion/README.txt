.
   Header     : <mutex>
   Signature  : constexpr mutex() noexcept;
                          mutex(const mutex&) = delete;
   Description:
     - mutex is a lockable object that is designed to signal when critical
       sections of code need exclusive access, preventing other threads with
       the same protection from executing concurrently and access the same
       memory locations
     - it provides exclusive ownership

   See also:
     recursive_mutex      : http://www.cplusplus.com/reference/mutex/recursive_mutex
     timed_mutex          : http://www.cplusplus.com/reference/mutex/timed_mutex
     recursive_timed_mutex: http://www.cplusplus.com/reference/mutex/recursive_timed_mutex

   -----------------------------------------------------------------------------

   SO thread on mutex vs recursive_mutex:
   https://stackoverflow.com/questions/187761/recursive-lock-mutex-vs-non-recursive-lock-mutex
