#ifndef __workq_h__
#define __workq_h__
#include <pthread.h>

/*
 * Structure to keep track of work queue requests.
 */
typedef struct workq_ele_tag {
	struct workq_ele_tag *next;
	void                 *data;
} workq_ele_t;

/*
 * Structure describing a work queue.
 */
typedef struct workq_tag {
	pthread_mutex_t    mutex;          /* control access to queue */
	pthread_cond_t     cv;             /* wait for work */
	pthread_attr_t     attr;           /* create detached threads */
	workq_ele_t        *first, *last;  /* work queue */
	int                valid;          /* valid */
	int                quit;           /* workq should quit */
	int                parallelism;    /* maximum threads */
	int                counter;        /* current threads */
	int                idle;           /* number of idle threads */
	void               (*engine)(void *arg);   /* user engine */
} workq_t;

#define WORKQ_VALID 0xdec1992

/*
 * Define work queue functions.
 */
extern int workq_init (
	workq_t     *wq,
	int         threads,               /* maximum threas */
	void        (*engine)(void *));    /* engine routine */
extern int workq_destroy (workq_t *wq);
extern int workq_add (workq_t *wq, void *data);
static void *workq_server (void *arg);

#endif /* __workq_h__ */
