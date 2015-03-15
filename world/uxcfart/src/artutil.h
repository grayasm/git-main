/*
  Copyright (C) 2002 Mihai Vasilian

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




#ifndef __artutil_h__
#define __artutil_h__


//c
//c++
//libs
#include "TPoint3d.hpp"
//program


#define NRPIESE  8
#define M2D 0.06            // miimi -> degrees
#define D2M 1. / 0.06       // degrees -> miimi


struct SPolar
{
public:
	float distanta;
	float deltah;
	float modificare_de_deriva;
	float gisment_final;
};




class Util
{
public:    
    static float round(float numar);
    static float interpoleaza(float var_dt, float eleminf, float elemsup, float interval );
    static float normalize6000(float unghi);
    static float transform3000(float unghi);

    static cad::TPoint3d<float> polar(float x, float y, float h, float Do, float To, float tct, float Gdb);
	
	typedef float Angle;
	typedef float Dist;
	typedef misc::pair<Angle, Dist>  ADistPair;
	static SPolar  rectangular(float x1, float y1, float h1, float x2, float y2, float h2, float Gdb);	
};



#endif // __artutil_h__
