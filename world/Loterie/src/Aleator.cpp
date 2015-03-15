
#include "Aleator.hpp"
#include "exception.hpp"


#include <stdlib.h>
#include <time.h>
#include <algorithm>




Aleator::Array Aleator::Generate(size_t count, size_t min, size_t max)
{
	if(max <= min) 
		throw misc::exception("incorrect interval");

	if(count > max - min + 1)
		throw misc::exception("exceeded maximum values");

	Array numere;

	srand( (unsigned)time( NULL ) );

	
	for(size_t z = 0; z < count; )
	{
		Array::value_type nr = min + rand() % (max - min + 1);		
		if( std::find(numere.begin(), numere.end(), nr) != numere.end()) continue;

		numere.push_back(nr);
		z++;		
	}//for

	return numere;
};