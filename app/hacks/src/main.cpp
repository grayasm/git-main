
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



class A
{
public:
	A(int s) : m_s(s) {}
	~A() {}
	int get() const { return m_s; }
private:
	int m_s;
};

class B
{
public:
	B(A** aa, int count)
	{
		m_aa = aa;
		m_count = count;
	}
	void f() 
	{
		for(int i=0; i < m_count; ++i)
		{
			A** aa = m_aa + i;
			printf("\n\tB::f(%d) = %d", i, (*aa)->get());
		}
	}
private:
	A** m_aa;
	int m_count;
};
int main(int, char**)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	A** p = 0;
	p = (A**)calloc(5, sizeof(A*));
	for(int i=0; i < 5; ++i)
	{
		A** a = p+i;
		*a = new A(i);
		
		A** b = p+i;
		printf("\np+%d = %d", i, a);
		printf("\nb(%d)=%d", i, (*b)->get());
			
		//new(a)A(i);
	}
	
	B b(p, 5);
	b.f();
	
	for(int i=0; i < 5; ++i)
	{
		A** a = p + i;
		delete (*a);
	}
	
	free(p);
	
	
	return 0;
}