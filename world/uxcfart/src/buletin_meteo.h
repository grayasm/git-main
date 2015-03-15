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



#ifndef __buletin_meteo_h__
#define __buletin_meteo_h__



//c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>

//c++
#include <iomanip>
#include <iostream>




#include "control_lucru.h"


class buletin_meteo
{
public :
    buletin_meteo () ;
    ~buletin_meteo () ;
    void buletin_meteo_control() ;


    char buletin_meteo_ch[100][100] ;
    void buletin_meteo_incarca();

private :
    //  grupele B.M.M.
    char cha[100][100];
    char cch[100][100];
    
    long bmm[100];


    void primeste_buletin_meteo();
    void salveaza_buletin_meteo();    
    void afiseaza_buletin_meteo();
    void registru();
} ;

extern buletin_meteo g_buletin_meteo;


#endif//__buletin_meteo_h__
