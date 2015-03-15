

#include "Extrageri.hpp"


Extrageri::Extrageri()
{
};

Extrageri::~Extrageri()
{
};

Extrageri::Extrageri(const Extrageri& tc)
{
	*this=tc;
};

Extrageri& Extrageri::operator=(const Extrageri& tc)
{
	if(this!=&tc)
	{
		m_extrageri = tc.m_extrageri;
	}//
	return *this;
};

size_t Extrageri::GetSize()const
{
	return m_extrageri.size();
};

Extrageri::Array& Extrageri::GetArray()
{
	return m_extrageri;
};

const Extrageri::Array& Extrageri::GetArray()const
{
	return m_extrageri;
};


Extrageri::It Extrageri::GetArrayBegin()
{
	return m_extrageri.begin();
};

Extrageri::CIt Extrageri::GetArrayBegin()const
{
	return m_extrageri.begin();
};

Extrageri::It Extrageri::GetArrayEnd()
{
	return m_extrageri.end();
};

Extrageri::CIt Extrageri::GetArrayEnd()const
{
	return m_extrageri.end();
};



bool operator >> (misc::ifstream& fstream, Extrageri& extrageri)
{
	if( !fstream.is_open() ) return false; 

	misc::char_t* tok;
	misc::char_t delim[]={ ' ', '\t', '\n' };
	misc::char_t buffer[500];
	Extrageri::Array& array = extrageri.GetArray();
	while( !fstream.eof() )
	{
		fstream.getline(buffer, 500);
		if( strlen(buffer) == 0 ) continue;
		tok = strtok(buffer, delim);
		if(tok == 0) continue;
		
		if(tok[0] == '#') continue;
		size_t i = 0;
		Varianta::Array::value_type val;
		Varianta::Array numere;
		while(tok != 0)
		{			
			misc::to_value(tok, val);
			numere.push_back(val);
			tok = strtok(NULL, delim);
		}//while

		assert(numere.size() == 7);

		Varianta varianta(numere);
		array.push_front(varianta);
	}//while

	return true;
};