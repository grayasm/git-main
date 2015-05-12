
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
#include "mutex.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include "single_lock.hpp"


class mthread : public misc::thread
{
public:
	mthread(misc::single_lock* sl, int sec)
	: m_sl(sl), m_sec(sec) {} 
	unsigned long run()
	{
		m_sl->lock();
		m_sl->unlock();
		return m_sec;
	}
private:
	misc::single_lock*	m_sl;
	int					m_sec;
};
int main(int, char**)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	misc::mutex m;
	misc::single_lock sl(&m);
	
	sl.lock();
	mthread t(&sl, 2);
	t.resume();
	sleep(2);
	sl.unlock();
	t.join();
	
	return 0;
}