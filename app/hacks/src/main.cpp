
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
#include <semaphore.h>
#include <errno.h>


class mythread : public misc::thread
{
public:
	mythread(int sec)
	: m_sec(sec){}
	~mythread(){}
	unsigned long run()
	{
		sleep(m_sec);
		return m_sec;
	}
private:	
	int		m_sec;
};

int main(int, char**)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	{
		mythread t(5);
		t.resume();
		t.join(1*1e3);
	}
	printf("\n\tmain: sleep(10)");
	sleep(10);
	
	printf("\n\tmain: return 0");
	return 0;
}