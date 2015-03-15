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



#ifndef __TPoint2d_hpp__
#define __TPoint2d_hpp__



//c
//c++
//lib
#include "autoptr.hpp"
#include "math.hpp"


//cad


namespace cad
{


template<typename T>
class TPoint2d
{
public:
    typedef misc::autoptr<TPoint2d<T> > Ptr;

public:
    TPoint2d()
    {
        m_elems[0] = 0;
        m_elems[1] = 0;
    };

    TPoint2d(const T x, const T y)
    {
        m_elems[0] = x;
        m_elems[1] = y;
    };

    ~TPoint2d()
    {
    };

    TPoint2d(const TPoint2d<T>& tc)    
    {
        m_elems[0] = tc.m_elems[0];
        m_elems[1] = tc.m_elems[1];
    };
    
    TPoint2d& operator=(const TPoint2d& tc)
    {
        if(this != &tc)
        {
            m_elems[0] = tc.m_elems[0];
            m_elems[1] = tc.m_elems[1];
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

    void x(const T newx)
    {
        m_elems[0] = newx;
    };

    void y(const T newy)
    {
        m_elems[1] = newy;
    };

    void operator+=(const TPoint2d& ta)
    {
        m_elems[0] += ta.m_elems[0];
        m_elems[1] += ta.m_elems[1];
    };

    void operator-=(const TPoint2d& ts)
    {
        m_elems[0] -= ts.m_elems[0];
        m_elems[1] -= ts.m_elems[1];
    };

    const T operator~() const
    {
        return ::sqrt(m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1]); 
    };

    void operator*=(const T scalar)
    {
        m_elems[0] *= scalar;
        m_elems[1] *= scalar;
    };

    void operator/=(const T denominator)
    {
        m_elems[0] /= denominator;
        m_elems[1] /= denominator;
    };

    const T& operator[](const size_t index) const
    {
        if (index > 2)
            throw misc::exception(U("out of array's boundary"));

        return m_elems[index];
    };

    T& operator[](const size_t index)
    {
        if (index > 2)
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
        return (m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1]);
    };

    bool IsEqual(const TPoint2d& pt, const T tolerance = math::Tol(T())) const
    {
        //orig. return math::is_zero((pt - *this).Length2(), tolerance*tolerance);
        return math::is_zero(~(pt - *this), tolerance);
    };

    //! Normalize this vector
    void Normalize()
    {
        if(m_elems[0] == 0. && m_elems[1] == 0.)
            throw misc::exception(U("Cannot normalize null vector"));

        (*this) /= ~(*this);
        return *this;
    };

private:
    T m_elems[2];

}; // TPoint2d<T>



//! Inverts vector direction.
template<typename T>
TPoint2d<T> operator-(const TPoint2d<T>& v)
{
    return TPoint2d<T>(-v.x(), -v.y());
};


//! Adds 2 points
template<typename T>
TPoint2d<T> operator+(const TPoint2d<T>& p, const TPoint2d<T>& q)
{
    return TPoint2d<T>(p.x() + q.x(), p.y() + q.y() );
};


//! Subtracts one point from another
template<typename T>
TPoint2d<T> operator-(const TPoint2d<T>& p, const TPoint2d<T>& q)
{
    return TPoint2d<T>(p.x() - q.x(), p.y() - q.y() );
};


//! Multiplies point with scalar
template<typename T>
TPoint2d<T> operator*(const TPoint2d<T> &p, const T scalar)
{
    return TPoint2d<T>(p.x() * scalar, p.y() * scalar);
};


//! Multiplies point with scalar
template<typename T>
TPoint2d<T> operator*(const T scalar, const TPoint2d<T> &p)
{
    return TPoint2d<T>(p.x() * scalar, p.y() * scalar);
};


//! Divides point by denominator
template<typename T>
TPoint2d<T> operator/(const TPoint2d<T> &p, const T denominator)
{
    return TPoint2d<T>(p.x() / denominator, p.y() / denominator);
};


//! Dot (Scalar) product of 2 vectors
/*! Area limited by the vectors
 *! 
*/
template<typename T>
T operator*(const TPoint2d<T>& v1, const TPoint2d<T>& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
};


//! Cross product
/*! 1) The magnitude of the resulting cross product is also equal to the area of the 
    parallelogram between the two vectors.

    2) Rotating from v1 to v2 moves in an counter clockwise if result is > 0 or 
    clockwise direction if value < 0.
*/
template<typename T>
T operator%(const TPoint2d<T>& v1, const TPoint2d<T>& v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
};


//! Calculates CW or CCW perpendicular on vector v
template<typename T>
TPoint2d<T> perpendicular(const TPoint2d<T>& v, bool clockwise)
{
    if(clockwise)
        return TPoint2d<T>(v.y(), -v.x());
    else // counter clockwise
        return TPoint2d<T>(-v.y(), v.x());        
};





}; // namespace

#endif // __TPoint2d_hpp__



