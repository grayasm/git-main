/*
  Copyright (C) 2013 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com

*/

#ifndef __TVector_hpp__
#define __TVector_hpp__


#include <stddef.h>


namespace cad
{
template<typename T, size_t nrelems>
class TVector
{
public:	
	TVector()
	{
	};

	~TVector()
	{
	};

	T& operator[](const size_t& index)
	{
		return m_array[index];
	};


	const T& operator[](const unsigned long& index) const
	{
		return m_array[index];
	};


	void operator+=(const TVector<T, nrelems>& other)
	{		
		for(size_t r=0; r < nrelems; ++r)
		{
			m_array[r] += other[r];
		}
	};


	void operator+=(const T& scalar)
	{
		for(size_t r=0; r < nrelems; ++r)
		{
			m_array[r] += scalar;
		}
	};

	void operator-=(const TVector<T, nrelems>& other)
	{
		for(size_t r=0; r < nrelems; ++r)
		{
			m_array[r] -= other[r];
		}
	};


	void operator-=(const T& scalar)
	{
		for(size_t r=0; r < nrelems; ++r)
		{
			m_array[r] -= scalar;
		}
	};


	void operator*=(const T& scalar)
	{
		for (size_t r=0; r < nrelems; ++r)
		{
			m_array[r] *= scalar;
		}
	};


	void operator/=(const T& scalar)
	{
		for(size_t r=0; r < nrelems; ++r)
		{
			m_array[r] /= scalar;
		}
	};


	const TVector operator-(const TVector& other)
	{
		TVector<T, nrelems> tmp;

		for (size_t i=0; i < nrelems; ++i)
		{
			tmp[i] = m_array[i] - other[i];
		}
		return tmp;
	};


private:
	T m_array[nrelems];

}; // class


}; // namespace

#endif // __TVector_hpp__

