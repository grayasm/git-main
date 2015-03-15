CFLAGS= -O0 -g -DDEBUG -Wall -pedantic -I.
LDFLAGS= -lpthread -lrt
release= -O2

sources= inertia.c
inertia: $(sources)
	gcc -o inertia $(sources) $(CFLAGS) $(LDFLAGS)
