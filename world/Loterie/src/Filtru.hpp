
#ifndef __Filtru_hpp__
#define __Filtru_hpp__

#include <vector>
#include <list>

#include "Varianta.hpp"

class Filtru
{
public:	
	typedef std::list<Varianta>  Array;
	typedef std::vector<unsigned short>	Numere;
	typedef std::vector<size_t> Pozitii;
	typedef Varianta::Array::value_type Value;


	//! erases the ticket that contains at least maxConsecutive numbers being equal distant with interval value, and 
	//! do not contain any of nr_preferentiale
	static bool StergeConsecutive(Array& variante, size_t interval, size_t maxConsecutive, const Numere& nr_preferentiale);


	//! erases the ticket that contains "identice" identical numbers as in previous version; pivot is choosen forwardly.
	static bool StergeIdenticeCrescator(Array& variante, size_t identice, const Numere& nr_preferentiale);
	
	//! erases the ticket that contains "identice" identical numbers as in previous version; pivot is choosen randomly.
	static bool StergeIdenticeAleator(Array& variante, size_t identice, const Numere& nr_preferentiale);

private:
	//! test if both arrays contains at least "identice" elements.
	static bool ContinIdentice(/*sorted*/const Varianta& var0, /*sorted*/const Varianta& var1, size_t identice);


private:
	Filtru();
	~Filtru();	
};



#endif//__Filtru_hpp__


