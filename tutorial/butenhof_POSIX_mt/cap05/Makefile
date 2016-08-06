CFLAGS= -O0 -g -DDEBUG -Wall -pedantic
LDFLAGS= -lpthread
release= -O2

once: once.c
	gcc $(CFLAGS) $(LDFLAGS) -o once  once.c

mutex_attr: mutex_attr.c
	gcc $(CFLAGS) $(LDFLAGS) -o mutex_attr  mutex_attr.c

cond_attr: cond_attr.c
	gcc $(CFLAGS) $(LDFLAGS) -o cond_attr  cond_attr.c

thread_attr: thread_attr.c
	gcc $(CFLAGS) $(LDFLAGS) -o thread_attr  thread_attr.c

cancel: cancel.c
	gcc $(CFLAGS) $(LDFLAGS) -o cancel  cancel.c

cancel_disable: cancel_disable.c
	gcc $(CFLAGS) $(LDFLAGS) -o cancel_disable  cancel_disable.c

cancel_async: cancel_async.c
	gcc $(CFLAGS) $(LDFLAGS) -o cancel_async  cancel_async.c

cancel_cleanup: cancel_cleanup.c
	gcc $(CFLAGS) $(LDFLAGS) -o cancel_cleanup  cancel_cleanup.c

cancel_subcontract: cancel_subcontract.c
	gcc $(CFLAGS) $(LDFLAGS) -o cancel_subcontract  cancel_subcontract.c

tsd_once: tsd_once.c
	gcc $(CFLAGS) $(LDFLAGS) -o tsd_once  tsd_once.c

tsd_destructor: tsd_destructor.c
	gcc $(CFLAGS) $(LDFLAGS) -o tsd_destructor  tsd_destructor.c


# my samples
pthread_key_create: pthread_key_create.c
	gcc $(CLFAGS) $(LDFLAGS) -o pthread_key_create  pthread_key_create.c

pthread_key_delete: pthread_key_delete.c
	gcc $(CLFAGS) $(LDFLAGS) -o pthread_key_delete  pthread_key_delete.c

pthread_getspecific: pthread_getspecific.c
	gcc $(CLFAGS) $(LDFLAGS) -o pthread_getspecific  pthread_getspecific.c

pthread_setspecific: pthread_setspecific.c
	gcc $(CLFAGS) $(LDFLAGS) -o pthread_setspecific  pthread_setspecific.c


clean:
	rm 	once  mutex_attr  cond_attr  thread_attr  cancel	\
		cancel_disable  cancel_async  cancel_cleanup		\
		cancel_subcontract  tsd_once  tsd_destructor	\
		pthread_key_create  pthread_key_delete		\
		pthread_getspecific  pthread_setspecific
