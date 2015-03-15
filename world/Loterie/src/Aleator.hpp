#ifndef __Aleator_hpp__
#define __Aleator_hpp__


#include <vector>

#ifndef WIN32
#include <stddef.h> //linux error: 'size_t' has not been declared ??
#endif

class Aleator
{
public:
	typedef std::vector<unsigned short> Array;
	
	//! generates count random numbers, in range [min, max]
	static Array Generate(size_t count, size_t min, size_t max);


protected:
private:	
	Aleator();
	Aleator(const Aleator&);
	Aleator& operator=(const Aleator&);

};





#endif//Aleator_hpp__

