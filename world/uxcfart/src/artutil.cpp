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



#include "artutil.h"



//c
#include <float.h>
#include <stdlib.h>
//c++
//misc
#include "math.hpp"
#include "unistd.hpp"
//program



float Util::round(float numar)
{
    return ::floor(numar + 0.5f);   
};


float Util::interpoleaza(float var_dt, float eleminf, float elemsup, float interval )
{    
    return eleminf + (var_dt * (elemsup - eleminf)) / (interval);
};


float Util::normalize6000(float unghi)
{
    while(true)
    {
        if(unghi < 0)
        {
            unghi += 6000;
        }
        else if(unghi > 6000)
        {
            unghi -= 6000;
        }
        else
        {
            return unghi;
        }
    }
};


float Util::transform3000(float unghi)
{
    unghi = Util::normalize6000(unghi) ;

    if(unghi < 3000)
    {
        unghi = unghi + 3000 ;
    }
    else if(unghi >= 3000)
    {
        unghi = unghi - 3000 ;
    }

    return unghi;
};



cad::TPoint3d<float> Util::polar(float x, float y, float h, float Do, float To, float tct, float Gdb)
{
    //  Functia calculeaza x_final, y_final, h_final ;        
    

    float directie_de_baza_virtuala = Gdb ;
    float structura_elementelor_distanta = Do ;
    float unghi_de_teren = tct ;


    //Transformarea citirii lunetei in gisment;
    float structura_elementelor_gisment_final = directie_de_baza_virtuala + To ;
    structura_elementelor_gisment_final = Util::normalize6000(structura_elementelor_gisment_final);



    float x_final=0.f;
    float y_final=0.f;
    float h_final=0.f;
    float rumb_final=0.f;


    if(structura_elementelor_gisment_final >= 0.f && structura_elementelor_gisment_final < 1500.f)
    {
        float deltaX = structura_elementelor_distanta * cos(unghi_de_teren*M2D*(float)math::DEG2RAD) * cos(structura_elementelor_gisment_final*M2D*(float)math::DEG2RAD);
        float deltaY = structura_elementelor_distanta * cos(unghi_de_teren*M2D*(float)math::DEG2RAD) * sin(structura_elementelor_gisment_final*M2D*(float)math::DEG2RAD);

        x_final = x + deltaX ;
        y_final = y + deltaY ;
        h_final = h + structura_elementelor_distanta * sin(unghi_de_teren*M2D*(float)math::DEG2RAD);
    }
    else if(structura_elementelor_gisment_final >= 1500.f && structura_elementelor_gisment_final < 3000.f)
    {
        rumb_final = 3000 - structura_elementelor_gisment_final ;
        float deltaX = structura_elementelor_distanta * cos(unghi_de_teren*M2D*(float)math::DEG2RAD) * cos(rumb_final*M2D*(float)math::DEG2RAD);
        float deltaY = (structura_elementelor_distanta*cos(unghi_de_teren*M2D*math::DEG2RAD))*(sin(rumb_final*M2D*math::DEG2RAD));
        x_final = x - deltaX ;
        y_final = y + deltaY ;
        h_final = h + (structura_elementelor_distanta*sin(unghi_de_teren*M2D*math::DEG2RAD));
    }
    else if(structura_elementelor_gisment_final >= 3000.f && structura_elementelor_gisment_final < 4500.f)
    {
        rumb_final = structura_elementelor_gisment_final - 3000 ;
        float deltaX = (structura_elementelor_distanta*cos(unghi_de_teren*M2D*math::DEG2RAD))*(cos(rumb_final*M2D*math::DEG2RAD));
        float deltaY = (structura_elementelor_distanta*cos(unghi_de_teren*M2D*math::DEG2RAD))*(sin(rumb_final*M2D*math::DEG2RAD));
        x_final = x - deltaX ;
        y_final = y - deltaY ;
        h_final = h + (structura_elementelor_distanta*sin(unghi_de_teren*M2D*math::DEG2RAD));
    }
    else if(structura_elementelor_gisment_final >= 4500.f && structura_elementelor_gisment_final <= 6000.f)
    {
        rumb_final = 6000 - structura_elementelor_gisment_final ;
        float deltaX = (structura_elementelor_distanta*cos(unghi_de_teren*M2D*math::DEG2RAD))*(cos(rumb_final*M2D*math::DEG2RAD));
        float deltaY = (structura_elementelor_distanta*cos(unghi_de_teren*M2D*math::DEG2RAD))*(sin(rumb_final*M2D*math::DEG2RAD));
        x_final = x + deltaX ;
        y_final = y - deltaY ;
        h_final = h + (structura_elementelor_distanta*sin(unghi_de_teren*M2D*math::DEG2RAD));
    }
    else
    {
        printf("\n   structura_elementelor_gisment_final = %.0f  -> depasirea intervalului 0 - 60-00", structura_elementelor_gisment_final);
        printf("\n Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }

    if(x_final > 100000)
    {
        x_final = x_final - 100000 ;
    }
    else if(x_final < 0)
    {
        x_final = x_final + 100000 ;
    }

    if(y_final > 100000)
    {
        y_final = y_final - 100000 ;
    }
    else if(y_final < 0)
    {
        y_final = y_final + 100000 ;
    }

    return cad::TPoint3d<float>(x_final, y_final, h_final);
};

SPolar Util::rectangular(float x1, float y1, float h1, float x2, float y2, float h2, float Gdb)
{	
    //return value
	SPolar objPolar;


	float distanta = 0.f;
	float modificare_de_deriva = 0.f;
	float gisment_final = 0.f;	
	float deltah = 0.f;
	
	

	//Functia calculeaza distanta si modificare_de_deriva ;
	float deltaX = x2 - x1;
	float deltaY = y2 - y1;
	deltah = h2 - h1;


	if(deltaX > 50001)
	{
		deltaX = 100000 - deltaX ;
	}

	if(deltaX < -50001)
	{
		deltaX = 100000 + deltaX ;
	}

	if(deltaY > 50001)
	{
		deltaY = 100000 - deltaY ;
	}

	if(deltaY < -50001)
	{
		deltaY = 100000 + deltaY ;
	}


	
	if(deltaX > 0 && deltaY == 0)
	{
		//CADRAN I
		distanta  = deltaX ;
		float rumb_final = 0 ;
		gisment_final = 0 ;

		modificare_de_deriva = rumb_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if((deltaX > 0) && (deltaY > 0))
	{

		//CADRAN I
		//valoarea in radiani a RUMBULUI
		float rumb_final = atan(fabs(deltaY/deltaX));

		//se folosesc funct. COS cu argumentul in RADIANI ;
		distanta = deltaX*(1/cos(rumb_final));


		//valoarea in miimi a RUMBULUI
		rumb_final = rumb_final*math::RAD2DEG*D2M ;
		gisment_final = rumb_final ;


		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if((deltaX == 0) && (deltaY > 0))
	{
		//CADRAN II
		distanta = deltaY ;
		gisment_final = 1500 ;		

		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if((deltaX < 0) && (deltaY == 0))
	{
		//CADRAN II
		distanta = (-1)*deltaX ;

		gisment_final = 3000 ;
		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if((deltaX < 0) && (deltaY > 0))
	{

		//CADRAN  II
		//valoarea in radiani a RUMBULUI
		float rumb_final = atan(fabs(deltaY/deltaX));

		distanta = (-1)*deltaX*(1/cos(rumb_final));

		//valoarea in miimi a RUMBULUI
		rumb_final = rumb_final*math::RAD2DEG*D2M ;
		gisment_final = 3000 - rumb_final ;


		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if(deltaX == 0 && deltaY < 0)
	{

		//CADRAN   III
		distanta = (-1)*deltaY ;
		gisment_final = 4500 ;


		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if((deltaX < 0) && (deltaY < 0))
	{
		//CADRAN   III
		//valoarea in radiani a RUMBULUI
		float rumb_final = atan(fabs(deltaY/deltaX));

		distanta = (-1)*deltaX*(1/cos(rumb_final));

		//valoarea in miimi a RUMBULUI
		rumb_final = rumb_final*math::RAD2DEG*D2M ;
		gisment_final = 3000 + rumb_final ;


		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}
	else if(deltaX > 0 && deltaY < 0)
	{

		//CADRAN IV
		//valoarea in radiani a RUMBULUI
		float rumb_final = atan(fabs(deltaY/deltaX));

		distanta = deltaX*(1/cos(rumb_final));

		// valoarea in miimi a RUMBULUI
		rumb_final = rumb_final*math::RAD2DEG*D2M ;
		gisment_final = 6000 - rumb_final ;


		modificare_de_deriva = gisment_final - Gdb ;

		while(true)
		{
			if(modificare_de_deriva < - 3000)
			{
				modificare_de_deriva = modificare_de_deriva + 6000 ;
			}
			else if(modificare_de_deriva > 3000)
			{
				modificare_de_deriva = modificare_de_deriva - 6000 ;
			}
			else
			{
				break;
			}
		} // while
	}

		
	objPolar.distanta = distanta;
	objPolar.modificare_de_deriva = modificare_de_deriva;
	objPolar.gisment_final = gisment_final;
	objPolar.deltah = deltah;


	return objPolar;
};