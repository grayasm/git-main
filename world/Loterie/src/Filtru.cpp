
#include "Filtru.hpp"

#include <stdlib.h>
#include <time.h>



bool Filtru::StergeConsecutive(Array& variante, size_t interval, size_t maxConsecutive,
							   const Numere& nr_preferentiale)
{
	typedef Varianta::Array::value_type Value;

	for(Array::iterator beg = variante.begin(); beg != variante.end(); /*erasing from list*/)
	{

		Varianta& var = *beg;
		var.Sort();

		size_t vsize = var.GetSize();
		size_t iCount = 0;
		bool erase = false;

		int posibil = (int)vsize - (int)maxConsecutive;
		if(posibil < 0) 
			return false;//all have the same size


		for(size_t i=0; i < vsize-maxConsecutive; ++i)
		{
			Value val0 = var[i];
			for(size_t j=i+1; j<vsize; ++j)
			{
				Value val1 = var[j];

				if(val1 - val0 == interval)
				{
					++iCount;
					val0 = val1;
				}

				if(iCount >= maxConsecutive)
				{
					erase=true;
					j=vsize;
					i=vsize;
					break;
				}

			}//for

			iCount=0;

		}//for


		//contains any of preferred numbers
		if(erase && !nr_preferentiale.empty())
		{
			const Varianta::Array& vararray = var.GetArray();

			Varianta::Array::const_iterator it = std::find_first_of(var.GetArray().begin(), var.GetArray().end(), nr_preferentiale.begin(), nr_preferentiale.end());
			if(it != vararray.end())
				erase = false;
		}

		//to be erased?
		if(erase)
		{
			erase = false;
			iCount = 0;
			Array::iterator erIt = beg;
			++beg;
			variante.erase(erIt);
			continue;
		}

		iCount = 0;
		++beg;		
	}//for

	return true;
};


bool Filtru::StergeIdenticeCrescator(Array& variante, size_t identice, const Numere& nr_preferentiale)
{
	typedef Varianta::Array::value_type Value;

	for(Array::iterator bI0 = variante.begin(); bI0 != variante.end(); /*erasing from array*/)
	{
		Varianta& var0 = *bI0;
		var0.Sort();

		Array::iterator bI1 = bI0;


		for(++bI1; bI1 != variante.end(); /*erasing from array*/)
		{
			Varianta& var1 = *bI1;
			var1.Sort();
					
			bool erase = Filtru::ContinIdentice(var0, var1, identice);

			if(erase && !nr_preferentiale.empty())
			{
				const Varianta::Array& vararray = var1.GetArray();
				Varianta::Array::const_iterator it = std::find_first_of(vararray.begin(), vararray.end(), nr_preferentiale.begin(), nr_preferentiale.end());
				if(it != vararray.end())
					erase = false;
			}

			Array::iterator erIt = bI1;
			++bI1;

			if(erase)
			{
				erase = false;
				variante.erase(erIt);
			}

		}//for I1


		++bI0;
	}//for I0

	return true;
};


bool Filtru::StergeIdenticeAleator(Array& variante, size_t identice, const Numere& nr_preferentiale)
{
	srand((unsigned int) time(NULL));

	Pozitii pozititii;
			
	while(1)
	{
		size_t poz0 = rand() % variante.size();			
		while( std::find(pozititii.begin(), pozititii.end(), poz0) != pozititii.end() )
		{
			poz0 = rand() % variante.size();
		}
		pozititii.push_back(poz0);


		Array::iterator It0 = variante.begin();
		std::advance(It0, poz0);
		(*It0).Sort();

		size_t poz1 = 0;
		for(Array::iterator It1 = variante.begin(); It1 != variante.end(); ++It1, ++poz1)
		{
			if(std::find(pozititii.begin(), pozititii.end(), poz1) != pozititii.end()) continue;
			
			(*It1).Sort();

			//check for "identice"
			bool erase = Filtru::ContinIdentice(*It0, *It1, identice);

			//check preferred numbers.
			if(erase && !nr_preferentiale.empty())
			{
				const Varianta::Array& vararray = It1->GetArray();
				Varianta::Array::const_iterator it = std::find_first_of(vararray.begin(), vararray.end(), nr_preferentiale.begin(), nr_preferentiale.end());
				if(it != vararray.end())
					erase = false;
			}

			//final, to be erased
			if(erase)
			{
				(*It1)[0]= (Value)-1;//marked to be erased
				pozititii.push_back(poz1);				
			}
		}//for

		std::sort(pozititii.begin(), pozititii.end());
		if(pozititii.size() == variante.size())
			break;		
	}//while

	for(Array::iterator bIt = variante.begin(); bIt != variante.end(); /*erasing from list*/)
	{
		if( (*bIt)[0] == (Value)-1 )
		{
			Array::iterator er = bIt;
			++bIt;
			variante.erase(er);
		}
		else
			++bIt;
	}

	return true;	
};

bool Filtru::ContinIdentice(/*sorted*/const Varianta& var0, /*sorted*/const Varianta& var1, size_t identice)
{	
	size_t count = 0;
	
	for(size_t i0 = 0; i0 < var0.GetSize(); ++i0)
	{
		Value val0 = var0[i0];

		for(size_t i1 = 0; i1 < var1.GetSize(); ++i1)
		{
			Value val1 = var1[i1];

			if(val0 == val1)
			{
				++count;

				if(count >= identice)
				{												
					return true;
				}
				else
				{
					++i0;
					if(i0<var0.GetSize())
					{
						val0 = var0[i0];
						continue;
					}
					else
						break;
				}
			}


			//contains any of preferred numbers
			/*if(erase && !nr_preferentiale.empty())
			{
				const Varianta::Array& vararray = var1.GetArray();
				Varianta::Array::const_iterator it = std::find_first_of(vararray.begin(), vararray.end(), nr_preferentiale.begin(), nr_preferentiale.end());
				if(it != vararray.end())
					erase = false;
			}*/
	
		}//for i1
	}//for i0	

	return false;		
};
