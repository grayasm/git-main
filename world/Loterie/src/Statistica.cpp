#include "Statistica.hpp"


void Statistica::NumarAparitii(Extrageri::CIt beg, Extrageri::CIt end, MapaAparitii& map)
{
	map.clear();
	for(; beg != end; ++beg)
	{
		const Varianta& varianta = *beg;
		for(size_t i = 0 ; i < varianta.GetSize(); ++i)
		{
			map[varianta[i]]++;
		}//for
	}//for
};


void Statistica::Write(misc::ofstream& fstream, const MapaAparitii& map, WriteMode mode)
{
	if( !fstream.is_open() ) 
		return ;

	if(mode == WM_NORMAL)
	{
		fstream << map;
		return;
	}

	typedef std::multimap<size_t,size_t> RatingMap;
	typedef std::pair<size_t,size_t> RatingPair;


	if(mode == WM_TOP_DOWN)
	{
		RatingMap rating;		
		for(MapaAparitii::const_iterator It = map.begin(); It != map.end(); ++It)
		{
			RatingPair rp((*It).second, (*It).first);
			rating.insert(rp);
		}

		fstream << U("\nSorted by draw times, HIGHEST first\n");
		for(RatingMap::const_reverse_iterator It = rating.rbegin(); It != rating.rend(); ++It)
		{
			fstream << U("\nNO = ") << (*It).second /*no*/ << U(" - ") << (*It).first /*rating*/;
		}

		return;
	}	


	if(mode == WM_DOWN_TOP)
	{
		RatingMap rating;		
		for(MapaAparitii::const_iterator It = map.begin(); It != map.end(); ++It)
		{
			RatingPair rp((*It).second, (*It).first);
			rating.insert(rp);
		}
		
		fstream << U("\nSorted by draw times, LOWEST first\n");
		for(RatingMap::const_iterator It = rating.begin(); It != rating.end(); ++It)
		{
			fstream << U("\nNO = ") << (*It).second /*no*/ << U(" - ") << (*It).first /*rating*/;
		}

		return;
	}	
};


void Statistica::NumerePare(Extrageri::CIt beg, Extrageri::CIt end, size_t min, size_t max, size_t& gasite, size_t& total_extrageri)
{
	total_extrageri = 0;
	gasite = 0;

	for(; beg != end; ++beg, ++total_extrageri)
	{
		const Varianta& varianta = *beg;
		const Varianta::Array& varray = varianta.GetArray();
		size_t nrPare = 0;
		
		for(Varianta::Array::const_iterator vbeg = varray.begin(); vbeg != varray.end(); ++vbeg)
		{
			if( (*vbeg)%2 == 0 )//par ?
				nrPare++;
		}//for
		
		if(nrPare >= min && nrPare <= max)
			gasite++;		
	}//for
};



void Statistica::NumereImpare(Extrageri::CIt beg, Extrageri::CIt end, size_t min, size_t max, size_t& gasite, size_t& total_extrageri)
{
	total_extrageri = 0;
	gasite = 0;

	for(; beg != end; ++beg, ++total_extrageri)
	{
		const Varianta& varianta = *beg;
		const Varianta::Array& varray = varianta.GetArray();
		size_t nrPare = 0;

		for(Varianta::Array::const_iterator vbeg = varray.begin(); vbeg != varray.end(); ++vbeg)
		{
			if( (*vbeg)%2 != 0 )//par ?
				nrPare++;
		}//for

		if(nrPare >= min && nrPare <= max)
			gasite++;		
	}//for
};


void Statistica::NumerePreferentiale(Extrageri::CIt beg, Extrageri::CIt end, const Varianta& preferentiale, size_t& gasite, size_t& total_extrageri)
{
	gasite = 0;
	total_extrageri = 0;
	if(preferentiale.GetArray().empty())
		return;

	const Varianta::Array& parray = preferentiale.GetArray();	
	for(; beg != end; ++beg, ++total_extrageri)
	{
		const Varianta& varianta = *beg;
		const Varianta::Array& varray = varianta.GetArray();
		size_t count = 0;

		for(size_t i=0; i<parray.size(); ++i)
		{
			if(std::find(varray.begin(), varray.end(), parray[i]) != varray.end())
				count++;
		}//for

		if(count == parray.size())
			gasite++;				
	}//for
};



misc::ofstream& operator << (misc::ofstream& fstream, const Statistica::MapaAparitii& map)
{
	if( !fstream.is_open() ) return fstream;
		
	fstream << U("\nSorted by number, not by draws\n");
	for(Statistica::MapaAparitii::const_iterator It = map.begin(); It != map.end(); ++It)
	{
		fstream << U("\nNO= ") << (*It).first << U(" - ") << (*It).second;
	}//for

	return fstream;
};