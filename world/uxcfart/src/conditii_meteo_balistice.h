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


#ifndef __conditii_meteo_balistice_h__
#define __conditii_meteo_balistice_h__


#include "buletin_meteo.h"


class conditii_meteo_balistice
{
public :

    conditii_meteo_balistice ();
    ~conditii_meteo_balistice ();

    void conditii_meteo_balistice_control();
    void conditii_meteo_balistice_incarca();

    float conditii_meteo_balistice_vop[3];
    float conditii_meteo_balistice_tinc[3];
    float conditii_meteo_balistice_voinc[3];
    float conditii_meteo_balistice_q[3];
    float conditii_meteo_balistice_inc[3] ;
    char  conditii_meteo_balistice_voppr[3][5] ;

private :

    void primeste_conditii_meteo_balistice();
    void salveaza_conditii_meteo_balistice ();
    void afiseaza_conditii_meteo_balistice ();
    void registru();
};



extern conditii_meteo_balistice g_conditii_meteo_balistice;



#endif//__conditii_meteo_balistice_h__
