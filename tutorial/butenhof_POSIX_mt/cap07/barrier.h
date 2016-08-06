#ifndef __barrier_h__
#define __barrier_h__


#include <pthread.h>

/* Structure describing a barrier. */
typedef struct barrier_tag {
    pthread_mutex_t     mutex;          /* Control access to barrier */
    pthread_cond_t      cv;             /* wait for barrier */
    int                 valid;          /* set when valid */
    int                 threshold;      /* number of threads required */
    int                 counter;        /* current number of threads */
    unsigned long       cycle;          /* count cycles */
} barrier_t;

#define BARRIER_VALID   0xdbcafe

/* Support static initialization of barriers. */
#define BARRIER_INITIALIZER(cnt) \
	{PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, \
			BARRIER_VALID, cnt, cnt, 0}

/* Define barrier functions. */
extern int barrier_init (barrier_t *barrier, int count);
extern int barrier_destroy (barrier_t *barrier);
extern int barrier_wait (barrier_t *barrier);


#endif  /*__barrier_h__ */
