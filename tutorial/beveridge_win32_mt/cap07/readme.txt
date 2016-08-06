+---------------------------------------------------------------------------+
	Data Consistency - the discussion on the design and uses of a 
						Readers / Writers lock
+---------------------------------------------------------------------------+
	1) c/c++ keyword: volatile
	
	void WaitForKey(volatile char *pch)
	{
		while (*pch == 0)
			;
	}
	
	volatile keyword forces the optimizer in the compiler (in release build)
	to fetch pch variable from the address (memory) instead of the CPU register.
	volatile does not allow the copiler to store the variable in the CPU 
	register longer	than it is needed.
+---------------------------------------------------------------------------+
	2) Moving Locks to a Higher Level

	Exclusive locks (per class or per method) look great on paper, but
	they impact the performance a lot. The exclusive lock would force all 
	access to be sequential, and the benefit of mutithreading would be lost.
	
	There is nothing wrong with every thread in the application reading a
	data structure at the same time, as long as no other thread tries to change
	it. On the other hand, if a thread is writing a data structure, other threads
	should be prevented from both reading and writing it.
	
	Courtois, P.J., Heymans, F., and Parnas, D.L.: "Concurrent Control with Readers
	and Writers", Communications of the ACM, vol. 10, pp. 667-668, Oct. 1971
	A proper design giving preference to readers (others: fair-share, or preference to writers)
	is shown in the pseudocode below:
	
		Lock for Reader:
			Lock( Mutex );
			count++;
			if(count == 1)
				Lock( Semaphore );
			Unlock( Mutex );
		
		Unlock for Reader:
			Lock( Mutex );
			count--;
			if( count == 0 )
				Unlock( Semaphore );
			Unlock( Mutex );
		
		Lock for Writer:
			Lock( Semaphore );
			
		Unlock for Writer:
			Unlock( Semaphore );
		
		where:
		Mutex is a reader mutex;
		Semaphore has max=1;
		count is a reader counter;
+---------------------------------------------------------------------------+
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	