#ifndef __Extrageri_hpp__
#define __Extrageri_hpp__


#include <list>
#include <vector>
#include <assert.h>


#include "stream.hpp"
#include "Varianta.hpp"



class Extrageri
{
public:
	typedef std::list<Varianta> Array;
	typedef Array::iterator It;
	typedef Array::const_iterator CIt;

	Extrageri();
	~Extrageri();
	Extrageri(const Extrageri&);
	Extrageri& operator=(const Extrageri&);

	size_t GetSize()const;
	Array& GetArray();
	const Array& GetArray()const;
	It GetArrayBegin();
	CIt GetArrayBegin()const;
	It GetArrayEnd();
	CIt GetArrayEnd()const;


private:
	Array m_extrageri;
};



bool operator >> (misc::ifstream& fstream, Extrageri& extrageri);





#endif//__Extrageri_hpp__


