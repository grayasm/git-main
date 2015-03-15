#ifndef __Combinatie_hpp__
#define __Combinatie_hpp__


#include <list>
#include <vector>
#include <algorithm>

#include "stream.hpp"
#include "Varianta.hpp"


class Combinatie
{
public:
	typedef std::vector<unsigned short> Numbers;
	typedef std::list<Varianta> Array;
	typedef Array::iterator It;
	typedef Array::const_iterator CIt;
	
public:
	Combinatie(const Numbers& nr_jucate, size_t nrVarianta);
	~Combinatie();


	Numbers GetNumbers()const;
	size_t GetSize()const;
	Array& GetArray();
	const Array& GetArray()const;
	It GetArrayBegin();
	CIt GetArrayBegin()const;
	It GetArrayEnd();
	CIt GetArrayEnd()const;
	
private:
	//dezactivat
	Combinatie();
	Combinatie(const Combinatie&);
	Combinatie& operator=(const Combinatie&);


	static void Recursive(size_t M, size_t N, size_t i, size_t level, const Numbers& sirnr, Varianta& intermediar, Array& final);

private:
	Numbers m_sortedNumbers;
	Array m_combinatii;

};


misc::ostream& operator << (misc::ostream& stream, const Combinatie& cb);
misc::ofstream& operator << (misc::ofstream& fstream, const Combinatie& cb);


#endif//__Combinatie_hpp__



