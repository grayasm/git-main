/*
Copyright (C) 2009 Mihai Vasilian
*/

#ifndef __math_hpp__
#define __math_hpp__

//c
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

//c++
//misc
#include "exception.hpp"


namespace math
{
    //////////////////////////////////////////////////////////////////////////
    //! PI constant
    const double PI_ = 3.1415926535897932384626433832795;

    //! value of 2 * PI
    const double _2PI = 2.*PI_;

    //! value of PI / 2
    const double PI_2 = PI_ / 2.;

    //! Degrees to radians conversion factor.
    const double DEG2RAD = PI_ / 180.;

    //! Radians to degrees conversion factor.
    const double RAD2DEG = 180.0 / PI_;

    //! lower than this tolerance, 2 float values are considered equal.
    const float MATH_TOLF = 1e-6f;

    //! lower than this tolerance, 2 double values are considered equal.
    const double MATH_TOLD = 1e-12;

    //! lower than this tolerance, 2 long double values are considered equal.
    const long double MATH_TOLLD = 1e-16; 

    
    //////////////////////////////////////////////////////////////////////////
    //char - 1 byte
    inline char min_value(char)
    {
        return SCHAR_MIN;
    }

    inline char max_value(char)
    {
        return SCHAR_MAX;
    }

    inline unsigned char max_value(unsigned char)
    {
        return UCHAR_MAX;
    }

    //short - 2 bytes
    inline short min_value(short)
    {
        return SHRT_MIN;
    }

    inline short max_value(short)
    {
        return SHRT_MAX;
    }

    inline unsigned short max_value(unsigned short)
    {
        return USHRT_MAX;
    }

    //int - 4 bytes
    inline int min_value(int)
    {
        return INT_MIN;
    }

    inline int max_value(int)
    {
        return INT_MAX;
    }


    inline unsigned int max_value(unsigned int)
    {
        return UINT_MAX;
    }


    //long - 4 bytes
    inline signed long min_value(signed long)
    {
        return LONG_MIN;
    }


    inline signed long max_value(signed long)
    {
        return LONG_MAX;
    }


    inline unsigned long max_value(unsigned long)
    {
        return ULONG_MAX;
    }

    //long long - 8 bytes
    inline long long int max_value(long long int)
    {
        return LLONG_MAX;
    }

    inline long long int min_value(long long int)
    {
        return LLONG_MIN;
    }

    inline unsigned long long int max_value(unsigned long long int)
    {
        return ULLONG_MAX;
    }

    //float - 4 bytes
    inline float min_value(float)
    {
        return FLT_MIN;
    }

    inline float max_value(float)
    {
        return FLT_MAX;
    }

    //////////////////////////////////////////////////////////////////////////
	// see misc::algobase::min for explanation about macro expanding min vs (min)
    template <typename T>
    inline const T& (min) ( const T& a, const T& b )
    {
        return !(b < a) ? a : b;
    }

    template <typename T, typename Compare>
    inline const T& (min) ( const T& a, const T& b, Compare comp )
    {
        return !comp(b, a) ? a : b;
    }


    template<typename T>
    inline const T& (max)(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }

    template <typename T, typename Compare>
    inline const T& (max) ( const T& a, const T& b, Compare comp )
    {
        return comp(a, b) ? b : a;
    }


    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_eq(const T& a, const T& b)
    {
        return a == b;
    }

    inline bool is_eq(float a, float b, float tol = MATH_TOLF)
    {
        return ( ::fabs( a - b ) <= tol );
    }

    inline bool is_eq(const double& a, const double& b, const double& tol = MATH_TOLD)
    {
        return ( ::fabs( a - b ) <= tol );
    }

    inline bool is_eq(const long double& a, const long double& b, const long double& tol = MATH_TOLLD)
    {
        return ( ::fabs( a - b ) <= tol );
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_zero(const T& a)
    {
        return a == 0;
    }

    inline bool is_zero(float a, float prec = math::MATH_TOLF)
    {
        return ::fabs(a) <= prec;
    }

    inline bool is_zero(const double& a, const double& prec = math::MATH_TOLD)
    {
        return ::fabs(a) <= prec;
    }

    inline bool is_zero(const long double& a, const long double& prec = math::MATH_TOLLD)
    {
        return ::fabs(a) <= prec;
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_notzero(const T& a)
    {
        return a != 0;
    }

    inline bool is_notzero(float a)
    {
        return !is_zero(a);
    }

    inline bool is_notzero(const double& a)
    {
        return !is_zero(a);
    }

    inline bool is_notzero(const long double& a)
    {
        return !is_zero(a);
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_neq(const T& a, const T& b)
    {
        return !is_eq(a, b);
    }

    inline bool is_neq(float a, float b)
    {
        return !is_eq(a, b);
    }

    inline bool is_neq(const double& a, const double& b)
    {
        return !is_eq(a, b);
    }

    inline bool is_neq(const long double& a, const long double& b)
    {
        return !is_eq(a, b);
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_gt(const T& a, const T& b, const T& prec)
    {
        return a > (b + prec);
    }

    inline bool is_gt(float a, float b, float prec)
    {
        return a > (b + prec);
    }

    inline bool is_gt(double a, double b, double prec)
    {
        return a > (b + prec);
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_gte(const T& a, const T& b, const T& prec)
    {
        return a >= (b + prec);
    }

    inline bool is_gte(float a, float b, float prec)
    {
        return a >= (b + prec);
    }

    inline bool is_gte(const double& a, const double& b, const double& prec)
    {
        return a >= (b + prec);
    }

    inline bool is_gte(const long double& a, const long double& b, const long double& prec)
    {
        return a >= (b + prec);
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_lt(const T& a, const T& b, const T& prec)
    {
        return a < (b - prec);
    }

    inline bool is_lt(float a, float b, float prec)
    {
        return a < (b - prec);
    }

    inline bool is_lt(double a, double b, double prec)
    {
        return a < (b - prec);
    }

    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline bool is_lte(const T& a, const T& b, const T& prec)
    {
        return a <= (b - prec);
    }

    inline bool is_lte(float a, float b, float prec)
    {
        return a <= (b - prec);
    }

    inline bool is_lte(const double& a, const double& b, const double& prec)
    {
        return a <= (b - prec);
    }

    inline bool is_lte(const long double& a, const long double& b, const long double& prec)
    {
        return a <= (b - prec);
    }


    //////////////////////////////////////////////////////////////////////////
    inline double round(double val, short iPlaces)
    {
        double dRetval;
        double dMod = +1e-7;

        if (val < 0)
            dMod = -1e-7;

        dRetval =  val;
        dRetval += (5/pow(10.,iPlaces+1));
        dRetval *= pow(10.,iPlaces);
        dRetval =  floor(dRetval+dMod);
        dRetval /= pow(10.,iPlaces);

        return (dRetval);
    }    
    //////////////////////////////////////////////////////////////////////////	
    //!Get tolerance for float precision
    inline float Tol(float)
    {
        return math::MATH_TOLF;
    }

    //!Get tolerance for double precision
    inline double Tol(double)
    {
        return math::MATH_TOLD;
    }

    //!Get tolerance for long double precision
    inline long double Tol(long double)
    {
        return math::MATH_TOLLD;
    }
   

    //!Round value with tolerance
    template<typename T>
    inline T round(const T val, const T tol)
    {
        if(val == 0.0)
            return val;
        const T absVal(fabs(val));
        const T valSign(val/absVal);
        const T dst(fmod(absVal, tol));
        const T tol_2(tol/static_cast<T>(2.0));
        if(dst < tol_2)
            return valSign*(absVal - dst);
        return valSign*(absVal + (tol - dst));
    }

    inline double rand(const double a, const double b)
    {
        return a + (b - a) * ::rand() / (RAND_MAX - 1);
    }

    //!Limit input value by given range
    template<typename T>
    inline T limit(const T value, const T low, const T high)
    {
        if (value < low)
            return low;

        if (value > high)
            return high;

        return value;
    }

    template<typename T>
    inline  T sqrt(T value)
    {
        if ( value < 0 )
        {
            value = 0;
        }
        return ::sqrt( value );
    }


    template<typename T> 
    const T abs (const T& value)
    {
        if ( value > 0 )
            return value;

        if ( value < 0 )
            return -value;

        return 0;
    }

    template<typename T>
    T sign(const T value)
    {        
        if(value < 0)
            return -1;
        return 1;
    }

	template<typename T>
	int digits(T value)
	{
		int count=0;
		value *= sign(value);
		do
		{
			value /= 10;
			++count;
		}
		while(value > 0.1);

		return count;
	}
}  // namespace


#endif//__math_hpp__
