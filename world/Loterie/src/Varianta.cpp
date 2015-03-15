#include "Varianta.hpp"


Varianta::Varianta(size_t size)
{
	m_numbers.resize(size, 0);
};

Varianta::~Varianta()
{
};

Varianta::Varianta(const Varianta& v)
{
	*this=v;
};

Varianta& Varianta::operator=(const Varianta& v)
{
	if(this!=&v)
	{
		m_numbers = v.m_numbers;
	}//
	return *this;
};

Varianta::Varianta(const Array& arr)
{
	m_numbers = arr;
};

size_t Varianta::GetSize() const
{
	return m_numbers.size();
};

bool Varianta::HasValue(Array::value_type value)const
{
	return (std::find(m_numbers.begin(), m_numbers.end(), value) != m_numbers.end()) ;
};

Varianta::Array::value_type& Varianta::GetItem(Array::value_type value)
{
	Array::iterator it = std::find(m_numbers.begin(), m_numbers.end(), value);
	return *it;
};

const Varianta::Array::value_type& Varianta::GetItem(Array::value_type value)const
{
	Array::const_iterator cit = std::find(m_numbers.begin(), m_numbers.end(), value);
	return *cit;
};

const Varianta::Array& Varianta::GetArray() const
{
	return m_numbers;
};


void Varianta::Sort()
{
	std::sort(m_numbers.begin(), m_numbers.end());
};

const Varianta::Array::value_type& Varianta::operator[](unsigned short index)const
{
	return m_numbers[index];
};


Varianta::Array::value_type& Varianta::operator[](unsigned short index)
{
	return m_numbers[index];
};

bool Varianta::operator==(const Varianta& v)
{
	if(this!=&v)
	{
		if(GetSize() != v.GetSize())
			return false;

		Varianta left(*this);
		Varianta right(v);
		left.Sort();
		right.Sort();
		
		size_t i=0; 
		
		while(i<left.GetSize() && left[i] == right[i] && ++i);
		
		return i == left.GetSize();		
		
	}
	return true;
};

//////////////////////////////////////////////////////////////////////////
misc::ostream& operator << (misc::ostream& stream, const Varianta& v)
{
	unsigned short size = v.GetSize();
	for(unsigned short i = 0; i<size; ++i)
	{
		stream << misc::from_value(v[i]).c_str() << " ";
	}
	return stream;
};

misc::ofstream& operator << (misc::ofstream& fstream, const Varianta& v)
{
	unsigned short size = v.GetSize();
	for(unsigned short i = 0; i<size; ++i)
	{
		fstream << misc::from_value(v[i]).c_str() << " ";
	}
	return fstream;
};
//////////////////////////////////////////////////////////////////////////
