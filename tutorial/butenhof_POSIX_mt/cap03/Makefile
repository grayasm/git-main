CFLAGS= -O0 -g -DDEBUG
LDFLAGS= -lpthread
release= -O2

mutex_static: mutex_static.c
	gcc $(CFLAGS) $(LDFLAGS) -o mutex_static  mutex_static.c

mutex_dynamic: mutex_dynamic.c
	gcc $(CFLAGS) $(LDFLAGS) -o mutex_dynamic  mutex_dynamic.c

alarm_mutex: alarm_mutex.c
	gcc $(CFLAGS) $(LDFLAGS) -o alarm_mutex  alarm_mutex.c

trylock: trylock.c
	gcc $(CFLAGS) $(LDFLAGS) -o trylock  trylock.c

backoff: backoff.c
	gcc $(CFLAGS) $(LDFLAGS) -o backoff  backoff.c

cond_static: cond_static.c
	gcc $(CFLAGS) $(LDFLAGS) -o cond_static  cond_static.c

cond_dynamic: cond_dynamic.c
	gcc $(CFLAGS) $(LDFLAGS) -o cond_dynamic  cond_dynamic.c

cond: cond.c
	gcc $(CFLAGS) $(LDFLAGS) -o cond  cond.c

alarm_cond: alarm_cond.c
	gcc $(CFLAGS) $(LDFLAGS) -o alarm_cond  alarm_cond.c



# my samples
# pthread_mutex_
pthread_mutex_init: pthread_mutex_init.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_init pthread_mutex_init.c

pthread_mutex_lock: pthread_mutex_lock.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_lock pthread_mutex_lock.c

pthread_mutex_tryunlock: pthread_mutex_tryunlock.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_tryunlock pthread_mutex_tryunlock.c

pthread_mutex_unlock: pthread_mutex_unlock.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_unlock pthread_mutex_unlock.c

pthread_mutex_timedlock: pthread_mutex_timedlock.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_timedlock pthread_mutex_timedlock.c

pthread_mutex_destroy: pthread_mutex_destroy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_destroy pthread_mutex_destroy.c

pthread_mutex_getprioceiling: pthread_mutex_getprioceiling.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_getprioceiling pthread_mutex_getprioceiling.c

pthread_mutex_setprioceiling: pthread_mutex_setprioceiling.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_setprioceiling pthread_mutex_setprioceiling.c

pthread_mutex_getpshared: pthread_mutex_getpshared.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutex_getpshared pthread_mutex_getpshared.c

pthread_once: pthread_once.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_once pthread_once.c

# pthread_mutexattr_
pthread_mutexattr_destroy: pthread_mutexattr_destroy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutexattr_destroy  pthread_mutexattr_destroy.c


pthread_mutexattr_gettype: pthread_mutexattr_gettype.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutexattr_gettype  pthread_mutexattr_gettype.c


pthread_mutexattr_init: pthread_mutexattr_init.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutexattr_init  pthread_mutexattr_init.c

pthread_mutexattr_settype: pthread_mutexattr_settype.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_mutexattr_settype  pthread_mutexattr_settype.c


# sched_
sched_get_priority_max: sched_get_priority_max.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_get_priority_max  sched_get_priority_max.c

sched_get_priority_min: sched_get_priority_min.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_get_priority_min  sched_get_priority_min.c

sched_getaffinity: sched_getaffinity.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_getaffinity  sched_getaffinity.c

sched_getparam: sched_getparam.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_getparam  sched_getparam.c

sched_getscheduler: sched_getscheduler.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_getscheduler  sched_getscheduler.c

sched_rr_get_interval: sched_rr_get_interval.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_rr_get_interval  sched_rr_get_interval.c

sched_setaffinity: sched_setaffinity.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_setaffinity  sched_setaffinity.c

sched_setparam: sched_setparam.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_setparam  sched_setparam.c

sched_setscheduler: sched_setscheduler.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_setscheduler  sched_setscheduler.c

sched_yield: sched_yield.c
	gcc $(CFLAGS) $(LDFLAGS) -o sched_yield  sched_yield.c

#pthread_cond_
pthread_cond_init: pthread_cond_init.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_init  pthread_cond_init.c

pthread_cond_destroy: pthread_cond_destroy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_destroy  pthread_cond_destroy.c

pthread_cond_wait: pthread_cond_wait.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_wait  pthread_cond_wait.c

pthread_cond_timedwait: pthread_cond_timedwait.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_timedwait  pthread_cond_timedwait.c

pthread_cond_sinal: pthread_cond_sinal.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_sinal  pthread_cond_sinal.c

pthread_cond_broadcast: pthread_cond_broadcast.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_cond_broadcast  pthread_cond_broadcast.c

#pthread_condattr_
pthread_condattr_init: pthread_condattr_init.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_condattr_init  pthread_condattr_init.c

pthread_condattr_destroy: pthread_condattr_destroy.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_condattr_destroy  pthread_condattr_destroy.c

pthread_condattr_setpshared: pthread_condattr_setpshared.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_condattr_setpshared  pthread_condattr_setpshared.c

pthread_condattr_setclock: pthread_condattr_setclock.c
	gcc $(CFLAGS) $(LDFLAGS) -o pthread_condattr_setclock  pthread_condattr_setclock.c


#etc by me
cond_explained: cond_explained.c
	gcc $(CFLAGS) $(LDFLAGS) -o cond_explained  cond_explained.c




clean:
	rm -v mutex_static  mutex_dynamic trylock backoff \
		cond_static  cond_dynamic alarm_cond  cond_explained \
		pthread_mutex_initc  pthread_mutex_lock \
		pthread_mutex_tryunlock  pthread_mutex_unlock  \
		pthread_mutex_timedlock  pthread_mutex_destroy \
		pthread_mutex_getprioceiling  pthread_mutex_setprioceiling \
		pthread_mutex_getpshared  pthread_once	\
		pthread_mutexattr_destroy  pthread_mutexattr_gettype  \
		pthread_mutexattr_init  pthread_mutexattr_settype  \
		sched_get_priority_max  sched_get_priority_min \
		sched_getaffinity  sched_getparam  \
		sched_getscheduler  sched_rr_get_interval  \
		sched_setaffinity  sched_setparam  \
		sched_setscheduler  sched_yield   \
		pthread_cond_init  pthread_cond_destroy   \
		pthread_cond_wait  pthread_cond_timedwait   \
		pthread_cond_signal  pthread_cond_broadcast  \
		pthread_condattr_init  pthread_condattr_destroy  \
		pthread_condattr_setpshared  pthread_condattr_setclock
