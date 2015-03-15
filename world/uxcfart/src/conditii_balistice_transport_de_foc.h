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



#ifndef __conditii_balistice_transport_de_foc_h__
#define __conditii_balistice_transport_de_foc_h__


#include <stdio.h>
#include <stdlib.h>


class conditii_balistice_transport_de_foc
{

public :
    conditii_balistice_transport_de_foc() ;
    ~conditii_balistice_transport_de_foc() ;


    //--date rezultate din T.F.
    float coeficient_tragere[3];
    float corectie_reglaj_directie[3];
    float distanta_topografica_reper_tragere[3];
    float modificare_deriva_topografica_reper_tragere[3];
    float incarcatura_T_F[3];
} ;



extern conditii_balistice_transport_de_foc g_conditii_balistice_transport_de_foc;



#endif//__conditii_balistice_transport_de_foc_h__
