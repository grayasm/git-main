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


#ifndef __tabla_tragere_h__
#define __tabla_tragere_h__



#include "conditii_meteo_balistice.h"
#include "conditii_balistice_transport_de_foc.h"
#include "artutil.h"



class tabla_tragere
{

public:
    tabla_tragere ();
    ~tabla_tragere();


private:
    int tabla_tragere_plafon0;
    int tabla_tragere_plafon1;
    int tabla_tragere_plafon2;
    int tabla_tragere_plafon3;
    int tabla_tragere_plafon4;
    int tabla_tragere_plafon5;

    float tabla_tragere_vi0;
    float tabla_tragere_vi1;
    float tabla_tragere_vi2;
    float tabla_tragere_vi3;
    float tabla_tragere_vi4;
    float tabla_tragere_vi5;


public:
    int tabla_tragere_plafon ;                 //  ultima inregistrare in tabla curenta incarcata ;
    float tabla_tragere_vi ;                   //  viteza incarcaturii
    float tabla_tragere_v5[87][15];            //  matricea tabla_tragere coresp. inc (C, 1, 2, 3, 4, sau a 5-a);
    float tabla_tragere_incarcatura[3] ;       //  tabla_tragere_incarcatura initializata de P_C sau de T_F


    void tabla_tragere_incarca(int);
    float tabla_tragere_cautare(int nr_bat, int coloana_referinta, float valoarea_referinta, int coloana_dorita);
};



extern tabla_tragere g_tabla_tragere;


#endif//__tabla_tragere_h__
