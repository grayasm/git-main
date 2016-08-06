CFLAGS= -O0 -g -DDEBUG
LDFLAGS= -lpthread
release= -O2

lifecycle: lifecycle.c
	gcc $(CFLAGS) $(LDFLAGS) -o lifecycle lifecycle.c


# my samples
pthread_cleanup_push: pthread_cleanup_push.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cleanup_push  pthread_cleanup_push.c

pthread_cleanup_pop: pthread_cleanup_pop.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cleanup_pop  pthread_cleanup_pop.c

clean:
	rm -v lifecycle \
		  pthread_cleanup_push  pthread_cleanup_pop
