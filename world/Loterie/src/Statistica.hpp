#ifndef __Statistica_hpp__
#define __Statistica_hpp__



#include <map>

#include "stream.hpp"
#include "Varianta.hpp"
#include "Extrageri.hpp"




class Statistica
{
public:	
	typedef std::map<Varianta::Array::value_type, unsigned int> MapaAparitii;

	enum WriteMode
	{
		WM_NORMAL=0,	//from first to last number (e.g. 1 to 49)
		WM_TOP_DOWN,	//first with highest rating
		WM_DOWN_TOP		//first with lowest rating
	};


public:
	static void NumarAparitii(Extrageri::CIt beg, Extrageri::CIt end, MapaAparitii& map);
	static void Write(misc::ofstream& fstream, const MapaAparitii& map, WriteMode mode);

	//calculeaza cate extrageri au avut numarul indicat de numere pare/impare
	static void NumerePare(Extrageri::CIt beg, Extrageri::CIt end, size_t min, size_t max, size_t& gasite, size_t& total_extrageri);
	static void NumereImpare(Extrageri::CIt beg, Extrageri::CIt end, size_t min, size_t max, size_t& gasite, size_t& total_extrageri);

	//calculeaza cate extrageri contin numerele preferentiale
	static void NumerePreferentiale(Extrageri::CIt beg, Extrageri::CIt end, const Varianta& preferentiale, size_t& gasite, size_t& total_extrageri);

private:
	Statistica();
	~Statistica();
	Statistica& operator=(const Statistica&);
};



misc::ofstream& operator << (misc::ofstream& fstrea, const Statistica::MapaAparitii& map);



#endif//__Statistica_hpp__



