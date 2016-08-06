CFLAGS= -O0 -g -DDEBUG -Wall -pedantic
LDFLAGS= -lpthread
release= -O2

all: sigev_thread

atfork: atfork.c
	gcc $(CFLAGS) $(LDFLAGS) -o atfork  atfork.c

flock: flock.c
	gcc $(CFLAGS) $(LDFLAGS) -o flock  flock.c

putchar: putchar.c
	gcc $(CFLAGS) $(LDFLAGS) -o putchar  putchar.c

getlogin: getlogin.c
	gcc $(CFLAGS) $(LDFLAGS) -o getlogin  getlogin.c

susp: susp.c
	gcc $(CFLAGS) $(LDFLAGS) -o susp  susp.c

sigwait: sigwait.c
	gcc $(CFLAGS) $(LDFLAGS) -o sigwait  sigwait.c

# needs -lrt to link with the real time library
sigev_thread: sigev_thread.c
	gcc $(CFLAGS) $(LDFLAGS) -lrt -o sigev_thread  sigev_thread.c

semaphore_signal: semaphore_signal.c
	gcc $(CFLAGS) $(LDFLAGS) -lrt -o semaphore_signal  semaphore_signal.c

clean:
	rm  -v atfork  flock  putchar  getlogin  susp  sigwait \
	sigev_thread  semaphore_signal
