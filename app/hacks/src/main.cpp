
// std++
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <limits.h>
// misc++
#include "unistd.hpp"
#include "stream.hpp"
#include "string.hpp"
#include "strconv.hpp"
#include "time.hpp"
#include "thread.hpp"
#include "cpu_timer.hpp"

class mythread : public misc::thread
{
public:
	mythread(int i) : m_i(i){}
	int run()
	{
		printf("\n\tStarted thread %d", m_i);
		sleep(rand()%15);
		printf("\n\tExiting thread %d", m_i);
		return m_i;
	}
private:
	int m_i;
};

int main(int, char**)
{
	setvbuf(stdout, NULL, _IONBF, 0);
		
	mythread* t[5];
	for(int i=0; i<5; ++i)
	{
		t[i] = new mythread(i);
	}
	
	printf("\n\tAll thread are created. Stay tuned to start them...");
	sleep(2);
	for(int i=0; i<5; ++i)
		t[i]->resume();
	
	printf("\n\tJoining threads ...");
	for(int i=0; i<5; ++i)
	{
		if( t[i]->join(2) == 0 )
		{
			printf("\n\t thread %d joined", i);
		}
		else
		{
			printf("\n\t thread %d timeout", i);
		}
	}
	
	printf("\n\tRetrieve exit code...");
	for(int i=0; i<5; ++i)
	{
		unsigned long retval = 0;
		if( t[i]->get_exit_code(&retval) == 0 )
		{
			printf("\n\t thread %d returned %lu", i, retval);
		}
		else
		{
			printf("\n\t thread %d did not finish", i);
		}
	}
	
	printf("\n\tDeleting all threads");
	for(int i=0; i<5; ++i)
	{
		delete t[i];
		t[i] = 0;
	}
	
	return 0;
}