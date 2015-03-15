CFLAGS= -O0 -g -DDEBUG
LDFLAGS= -lpthread
release= -O2

all: pthread_self.c
	make pthread_self

alarm: alarm.c
	gcc $(CFLAGS) -o alarm alarm.c

alarm_fork: alarm_fork.c
	gcc $(CFLAGS) -o alarm_fork alarm_fork.c

alarm_thread: alarm_thread.c
	gcc $(CFLAGS) $(LDFLAGS) -o alarm_thread alarm_thread.c

thread_error: thread_error.c
	gcc $(release) $(LDFLAGS) -o thread_error thread_error.c

# my samples
# pthread_
pthread_create: pthread_create.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_create pthread_create.c

pthread_exit: pthread_exit.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_exit pthread_exit.c

pthread_join: pthread_join.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_join pthread_join.c

pthread_self: pthread_self.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_self pthread_self.c

pthread_equal: pthread_equal.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_equal pthread_equal.c

pthread_detach: pthread_detach.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_detach pthread_detach.c

pthread_cancel: pthread_cancel.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cancel pthread_cancel.c


# pthread_attr_
pthread_attr_destroy: pthread_attr_destroy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_destroy  pthread_attr_destroy.c

pthread_attr_init: pthread_attr_init.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_init  pthread_attr_init.c

pthread_attr_setaffinity_np: pthread_attr_setaffinity_np.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setaffinity_np  pthread_attr_setaffinity_np.c

pthread_attr_setdetachstate: pthread_attr_setdetachstate.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setdetachstate  pthread_attr_setdetachstate.c

pthread_attr_setguardsize: pthread_attr_setguardsize.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setguardsize  pthread_attr_setguardsize.c

pthread_attr_setinheritsched: pthread_attr_setinheritsched.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setinheritsched  pthread_attr_setinheritsched.c

pthread_attr_setschedparam: pthread_attr_setschedparam.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setschedparam  pthread_attr_setschedparam.c

pthread_attr_setschedpolicy: pthread_attr_setschedpolicy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setschedpolicy  pthread_attr_setschedpolicy.c

pthread_attr_setscope: pthread_attr_setscope.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setscope  pthread_attr_setscope.c

pthread_attr_setstack: pthread_attr_setstack.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setstack  pthread_attr_setstack.c

pthread_attr_setstackaddr: pthread_attr_setstackaddr.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setstackaddr  pthread_attr_setstackaddr.c

pthread_attr_setstacksize: pthread_attr_setstacksize.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_attr_setstacksize  pthread_attr_setstacksize.c



clean:
	rm -v alarm alarm_fork alarm_thread \
		pthread_create pthread_exit pthread_join pthread_self pthread_equal \
		pthread_detach pthread_cancel  \
		pthread_attr_destroy.c  pthread_attr_init.c  \
		pthread_attr_setaffinity_np.c  pthread_attr_setdetachstate.c  \
		pthread_attr_setguardsize.c  pthread_attr_setinheritsched.c  \
		pthread_attr_setschedparam.c  pthread_attr_setschedpolicy.c  \
		pthread_attr_setscope.c  pthread_attr_setstack.c  \
		pthread_attr_setstackaddr.c  pthread_attr_setstacksize.c
