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



#ifndef __TPoint3d_hpp__
#define __TPoint3d_hpp__


//c
//c++
//lib
#include "TMatrix.hpp"
#include "autoptr.hpp"
#include "math.hpp"
#include "strconv.hpp"

namespace cad
{

template<typename T>
class TPoint3d
{
public:
    typedef misc::autoptr<TPoint3d<T> > Ptr;

public:
    TPoint3d()
    {
        m_elems[0] = 0;
        m_elems[1] = 0;
        m_elems[2] = 0;
    };

    TPoint3d(const T x, const T y, const T z)
    {
        m_elems[0] = x;
        m_elems[1] = y;
        m_elems[2] = z;
    };

    ~TPoint3d()
    {
    };

    TPoint3d(const TPoint3d<T>& tc)    
    {
        m_elems[0] = tc.m_elems[0];
        m_elems[1] = tc.m_elems[1];
        m_elems[2] = tc.m_elems[2];
    };

    TPoint3d& operator=(const TPoint3d& tc)
    {
        if(this != &tc)
        {
            m_elems[0] = tc.m_elems[0];
            m_elems[1] = tc.m_elems[1];
            m_elems[2] = tc.m_elems[2];
        }

        return *this;
    };

    const T x() const 
    {
        return m_elems[0]; 
    };

    const T y() const 
    {
        return m_elems[1]; 
    };

    const T z() const
    {
        return m_elems[2];
    };

    void x(const T newx)
    {
        m_elems[0] = newx;
    };

    void y(const T newy)
    {
        m_elems[1] = newy;
    };

    void z(const T newz)
    {
        m_elems[2] = newz;
    };

    void operator+=(const TPoint3d& ta)
    {
        m_elems[0] += ta.m_elems[0];
        m_elems[1] += ta.m_elems[1];
        m_elems[2] += ta.m_elems[2];
    };

    void operator-=(const TPoint3d& ts)
    {
        m_elems[0] -= ts.m_elems[0];
        m_elems[1] -= ts.m_elems[1];
        m_elems[2] -= ts.m_elems[2];
    };

    const T operator~() const
    {
        return ::sqrt(m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2]); 
    };

    void operator*=(const T scalar)
    {
        m_elems[0] *= scalar;
        m_elems[1] *= scalar;
        m_elems[2] *= scalar;
    };

    void operator/=(const T denominator)
    {
        m_elems[0] /= denominator;
        m_elems[1] /= denominator;
        m_elems[2] /= denominator;
    };

    const T& operator[](const size_t index) const
    {
        if (index > 3)
            throw misc::exception(U("out of array's boundary"));

        return m_elems[index];
    };

    T& operator[](const size_t index)
    {
        if (index > 3)
            throw misc::exception(U("out of array's boundary"));

        return m_elems[index];
    };

    const T* GetArray() const
    {
        return &m_elems[0];
    };

    T* GetArray()
    {
        return &m_elems[0];
    };

    const T Length2() const
    {
        return (m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2]);
    };

    bool IsEqual(const TPoint3d& pt, const T tolerance = math::Tol(T())) const
    {
        //orig. return math::is_zero((pt - *this).Length2(), tolerance*tolerance);
        return math::is_zero(~(pt - *this), tolerance);
    };

    //! Normalize this vector
    const TPoint3d<T>& Normalize()
    {
        if(m_elems[0] == 0 && m_elems[1] == 0 && m_elems[2] == 0)
            throw misc::exception(U("Cannot normalize null vector"));

        (*this) /= ~(*this);
        return *this;
    };


	//! Transforms point with a 3x3 rotation matrix and a translation	
	void Transform3d(const typename cad::TMatrix<T, 3, 3>& matrix, const TPoint3d<T>& translation)
	{
		T elem0 = m_elems[0];
		T elem1 = m_elems[1];
		T elem2 = m_elems[2];
		m_elems[0] = matrix[0][0]*elem0 + matrix[0][1]*elem1 + 
			matrix[0][2]*elem2 + translation.x();
		m_elems[1] = matrix[1][0]*elem0 + matrix[1][1]*elem1 + 
			matrix[1][2]*elem2 + translation.y();
		m_elems[2] = matrix[2][0]*elem0 + matrix[2][1]*elem1 + 
			matrix[2][2]*elem2 + translation.z();
	};


	//! Transforms point with a 3x3 rotation matrix
    void Transform(const typename cad::TMatrix<T, 3, 3>& matrix)
	{
		T elem0 = m_elems[0];
		T elem1 = m_elems[1];
		T elem2 = m_elems[2];
		m_elems[0] = matrix[0][0]*elem0 + matrix[0][1]*elem1 + matrix[0][2]*elem2;
		m_elems[1] = matrix[1][0]*elem0 + matrix[1][1]*elem1 + matrix[1][2]*elem2;
		m_elems[2] = matrix[2][0]*elem0 + matrix[2][1]*elem1 + matrix[2][2]*elem2;
	};


	//! Transforms a point with a 4x4 matrix
    void Transform(const typename cad::TMatrix< T, 4, 4>& homomatrix)
	{
		cad::TVector<T, 4> origpt(m_elems[0], m_elems[1], m_elems[2], T(1));
		cad::TVector<T, 4> transformed = homomatrix * origpt;

		m_elems[0] = transformed[0];
		m_elems[1] = transformed[1];
		m_elems[2] = transformed[2];
	};


	//! Coordinates are equal
	bool is_eq(const TPoint3d& tc, const T tolerance = math::Tol(T())) const
	{
		return
			math::is_eq(m_elems[0] , tc.x(), tolerance) &&
			math::is_eq(m_elems[1] , tc.y(), tolerance) &&
			math::is_eq(m_elems[2] , tc.z(), tolerance);
	};


	misc::string ToString() const
	{
		misc::string res(U("["));		
		res += misc::from_value(x(), 5) + U(", ") +
			misc::from_value(y(), 5) + U(", ") +
			misc::from_value(z(), 5);
		res += U("] ");
		return res;
	};


private:
    T m_elems[3];
};


}; // namespace


#endif // __TPoint3d_hpp__

