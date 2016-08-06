/*  void omp_set_schedule(omp_sched_t kind, int chunk_size);
    void omp_get_schedule(omp_sched_t *kind, int *chunk_size);


    omp_set_schedule:
    -----------------
    Sets the runtime scheduling method. The kind argument can have the value
    omp_sched_static, omp_sched_dynamic, omp_sched_guided or omp_sched_auto.
    Except for omp_sched_auto, the chunk size is set to the value of chunk_size
    if positive, or to the default value if zero or negative. For omp_sched_auto
    the chunk_size argument is ignored.


    omp_get_schedule:
    -----------------
    Obtain the runtime scheduling method. The kind argument will be set to the
    value omp_sched_static, omp_sched_dynamic, omp_sched_guided or
    omp_sched_auto.
    The second argument, chunk_size, is set to the chunk size.

    for this example see also:
    http://stackoverflow.com/questions/15508128/using-omp-schedule-with-pragma-omp-for-parallel-scheduleruntime
*/


#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
	const int m=7, n=100;
	float a[m][n];
	int i,j;

	omp_set_schedule (omp_sched_static, 0);
#pragma omp parallel for shared(a) private(i,j) num_threads(3)
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++) // each thread has the same work
		{
			a[i][j] = i*j;
		}
		printf ("static  thread= %d\n", omp_get_thread_num ());
	}

	printf("\n");

	omp_set_schedule (omp_sched_dynamic, 0);
#pragma omp parallel for shared(a) private(i,j) num_threads(3)
	for (i=0; i<m; i++)
	{
		for (j=0; j<i; j++) // each thread won't do the same work
		{
			a[i][j] = i*j;
		}
		printf ("dynamic thread= %d\n", omp_get_thread_num ());
	}

	return 0;
}
