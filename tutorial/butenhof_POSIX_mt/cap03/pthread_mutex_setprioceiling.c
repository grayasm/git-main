/*
 *  int pthread_mutex_setprioceiling(const pthread_mutex_t* mutex,
 *                                   int prioceiling,
 *                                   int* old_ceiling);
 *
 *      Function shall either lock the mutex if it is unlocked, or block until
 *      it can successfully lock the mutex, then it shall change the mutex's
 *      priority ceiling and release the mutex. When the change is successful,
 *      the previous value of the priority ceiling shall be returned in
 *      old_ceiling. If the function fails the mutex priority ceiling shall
 *      not be changed.
 *
 *      If successful function shall return zero, otherwise an error number.
 */

//wait for page 186
