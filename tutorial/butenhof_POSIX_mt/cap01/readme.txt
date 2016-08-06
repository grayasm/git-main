	
	Synchronization may be provided using a wide variety of mechanisms. 
	Some of the most common forms are:
		- mutexes
		- condition variables
		- semaphores
		- (and) events.

	You may also use message passing mechanisms, such as:
		- UNIX pipes
		- sockets
		- POSIX message queues
		- (or) other protocols for communicating between asynchronous processes

	on the same system or across a network. 
	Any form of communication protocol contains some form of synchronization, 
	because passing	data around with no synchronization results in chaos, not communication.
	The terms thread, mutex, and condition variable are the main topics of this
	book.