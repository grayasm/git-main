
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


void unlock(sem_t* sem)
{
	int error = sem_post(sem);	
	if(error != 0 )
		printf("\nsem_post error");
	else
		printf("\nsem_post ok");
}
void lock(sem_t* sem)
{
	int error = sem_wait(sem);
	if(error == 0)
		printf("\nsem_wait ok");
	else
		printf("\nsem_wait error");
}

int main(int, char**)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	sem_t sem;
	sem_init(&sem, 0, 0);
	
	//unlock(&sem);
	
	lock(&sem);	
	
	
	
	return 0;
}