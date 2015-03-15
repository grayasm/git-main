#ifndef __Varianta_hpp__
#define __Varianta_hpp__


#include <vector>

#include "stream.hpp"
#include "strconv.hpp"
#include "exception.hpp"



class Varianta
{
public:
	typedef std::vector<unsigned short> Array;

	Varianta(size_t size);
	~Varianta();
	Varianta(const Varianta& v);
	Varianta& operator=(const Varianta& v);

	Varianta(const Array& arr);
	size_t GetSize() const;
	bool HasValue(Array::value_type value)const;
	Array::value_type& GetItem(Array::value_type value);
	const Array::value_type& GetItem(Array::value_type value)const;

	const Array& GetArray() const;
	
	void Sort();
	
	const Array::value_type& operator[](unsigned short index)const;
	Array::value_type& operator[](unsigned short index);
	bool operator==(const Varianta& v);


private:
	Array	m_numbers;//1-49
};


misc::ostream& operator << (misc::ostream& stream, const Varianta& v);
misc::ofstream& operator << (misc::ofstream& fstream, const Varianta& v);

#endif//__Varianta_hpp__



