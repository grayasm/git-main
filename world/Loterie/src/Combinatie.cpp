
#include "Combinatie.hpp"






Combinatie::Combinatie(const Numbers& nr_jucate, size_t nrVarianta)
{
	if(nr_jucate.size() < nrVarianta)
		throw misc::exception("cannot generate any combination");


	m_sortedNumbers = nr_jucate;
	std::sort(m_sortedNumbers.begin(), m_sortedNumbers.end(), std::less<Numbers::value_type>());
	
	size_t maxNr=nr_jucate.size();
	Varianta intermediar(nrVarianta);	
	m_combinatii.clear();
	
	size_t i=0;
	size_t level=0;

	Recursive(maxNr, nrVarianta, i, level, m_sortedNumbers, intermediar, m_combinatii);	
};

Combinatie::~Combinatie()
{
};

Combinatie::Numbers Combinatie::GetNumbers()const
{
	return m_sortedNumbers;
};

size_t Combinatie::GetSize()const
{
	return m_combinatii.size();
};

Combinatie::Array& Combinatie::GetArray()
{
	return m_combinatii;
};

const Combinatie::Array& Combinatie::GetArray()const
{
	return m_combinatii;
};


Combinatie::It Combinatie::GetArrayBegin()
{
	return m_combinatii.begin();
};

Combinatie::CIt Combinatie::GetArrayBegin()const
{
	return m_combinatii.begin();
};

Combinatie::It Combinatie::GetArrayEnd()
{
	return m_combinatii.end();
};

Combinatie::CIt Combinatie::GetArrayEnd()const
{
	return m_combinatii.end();
};



void Combinatie::Recursive( 
						   size_t maxNr, 
						   size_t varNr,
						   size_t i, 
						   size_t level, 
						   const Numbers& numerele, 
						   Varianta& varianta, 
						   Array& final )
{
	if(level==0) i=0;
	else i++;

	if(level+1==varNr)
	{
		for(size_t index=i; index < maxNr - varNr + level + 1; ++index)
		{
			short nr = numerele[index];
			Varianta currComb = varianta;
			currComb[level]=nr;
			final.push_back(currComb);
		}	
		return;
	}//if

	for(size_t j=i; j < maxNr - varNr + level + 1; ++j)
	{
		varianta[level] = numerele[j];
		Recursive(maxNr, varNr, j, level+1, numerele, varianta, final);	
	}//for
};


//////////////////////////////////////////////////////////////////////////

misc::ostream& operator << (misc::ostream& stream, const Combinatie& cb)
{	
	Combinatie::CIt Ib = cb.GetArrayBegin();
	Combinatie::CIt Ie = cb.GetArrayEnd();
	for(; Ib != Ie; ++Ib)
	{
		stream << *Ib << std::endl;
	}//for
	return stream;
};

misc::ofstream& operator << (misc::ofstream& fstream, const Combinatie& cb)
{
	Combinatie::CIt Ib = cb.GetArrayBegin();
	Combinatie::CIt Ie = cb.GetArrayEnd();
	for(; Ib != Ie; ++Ib)
	{
		fstream << *Ib << std::endl;
	}//for
	return fstream;
};

//////////////////////////////////////////////////////////////////////////


