CFLAGS= -O0 -g -DDEBUG -Wall -pedantic -I.
LDFLAGS= -lpthread -lrt
release= -O2

sources0= barrier_main.c barrier.c barrier.h
barrier: $(sources0)
	gcc -o barrier $(sources0) $(CFLAGS) $(LDFLAGS)

sources1=rwlock.c rwlock_main.c rwlock.h
rwlock: $(sources1)
	gcc -o rwlock $(sources1) $(CFLAGS) $(LDFLAGS)

sources2=workq_main.c  workq.c  workq.h
workq: $(sources2)
	gcc -o workq  $(sources2) $(CFLAGS) $(LDFLAGS)
