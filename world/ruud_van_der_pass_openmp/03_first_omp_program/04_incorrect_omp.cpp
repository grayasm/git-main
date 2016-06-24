/*  I must document what is wrong with the attempt to parallelize the foor
    loop in this sample.
    - it gives incorrect result compare with sequence version
    - it gives incorrect result compared with prev. parallel run
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>


int main(int argc, char* argv[])
{
	const int BENCHMARK=700;
	int i,j,k;
	double t,v,w;
	double m,n,o,p;
	double r,s;

	r=0;


#pragma omp parallel for shared(r) private(i,j,k,t,m,v,n,w,o,p,s)
	for(i=0; i<BENCHMARK; ++i)
	{
		t = ::sin(M_PI * i/BENCHMARK);
		m = i * (22. / (i+1));

		for(j=0; j<BENCHMARK; ++j)
		{
			v = ::cos(M_PI * j/BENCHMARK);
			n = j * (22. / (j+7));

			for(k=0; k<BENCHMARK; ++k)
			{
				w = 0.5 * k;
				o = k * (22. / (k+3));
				p = k * (11. / (k+1));

				s = -1*(k%2);

				r += s*t + s*m + s*v + s*n + s*w + s*o + s*p;
			}
		}
	}
/* End of omp parallel for */

	printf("r = %.6f\n", r);
	double final =  -43006836810.540794;
	if (r+1e-5 > final &&
	    r-1e-5 < final)
		printf("OK\n");
	else
		printf("error\n");

	return 0;
}
