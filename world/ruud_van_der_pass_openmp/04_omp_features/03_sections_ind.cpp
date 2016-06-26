/* sections construct does not work if each individual section is not
   independent from the others.
*/


#include <stdio.h>
#include <vector>
#include <map>
#include <omp.h>


int main(int argc, char** argv)
{
	std::vector<std::pair<int, int> >  vec1, vec2, vec3;

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			for(size_t i=0; i<3; ++i)
				vec1.push_back(std::make_pair(i+100, omp_get_thread_num()));

#pragma omp section
			for(size_t j=0; j<3; ++j)
				vec2.push_back(std::make_pair(j+10, omp_get_thread_num()));

#pragma omp section
			for(size_t k=0; k<3; ++k)
				vec3.push_back(std::make_pair(k, omp_get_thread_num()));


		}/* end of sections block. */
	}/* end of parallel region. */




	for(size_t i=0; i<vec1.size(); ++i)
		printf("vec1 th= %d pos= %d val= %d\n",
		       vec1[i].second, i, vec1[i].first);

	for(size_t i=0; i<vec2.size(); ++i)
		printf("vec2 th= %d pos= %d val= %d\n",
		       vec2[i].second, i, vec2[i].first);

	for(size_t i=0; i<vec3.size(); ++i)
		printf("vec3 th= %d pos= %d val= %d\n",
		       vec3[i].second, i, vec3[i].first);

	return 0;
}
