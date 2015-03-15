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


#ifndef __dispozitiv_de_lupta_h__
#define __dispozitiv_de_lupta_h__


#include "tabla_tragere.h"



class dispozitiv_de_lupta
{
public :

    dispozitiv_de_lupta();
    ~dispozitiv_de_lupta();

    void dispozitiv_de_lupta_control();    
    void dispozitivul_de_lupta_incarca();

    
       
    float dispozitivul_de_lupta_Xpt[3];
    float dispozitiv_de_lupta_Ypt[3];
    float dispozitiv_de_lupta_hpt[3];   // bateria 1[0] bateria2[1] bateria3[2]

    float dispozitiv_de_lupta_Xpco[3];
    float dispozitiv_de_lupta_Ypco[3];
    float dispozitiv_de_lupta_hpco[3];

    float dispozitiv_de_lupta_Xpo[2];
    float dispozitiv_de_lupta_Ypo[2];
    float dispozitiv_de_lupta_hpo[2];   //  poDn [0], pol Dn[1] ;

    float dispozitiv_de_lupta_Gdb;
    float dispozitiv_de_lupta_limita_stanga[3];
    float dispozitiv_de_lupta_limita_dreapta[3];  //  pentru fiecare baterie o limita in directie

    float dispozitiv_de_lupta_distanta_maxima;
    float dispozitiv_de_lupta_distanta_minima;   //  distanta maxima (minima) pt. toate cele 3 baterii ;

    float dispozitiv_de_lupta_scara_hartii ;   //  1 = 1:25.000  2= 1:50.000 ;
    float dispozitiv_de_lupta_caroiaj_x[10][2] ;    //  caroiajul hartii ;  dispozitiv_de_lupta_caroiaj_x[n][0] = indica axa 20.000
    float dispozitiv_de_lupta_caroiaj_y[10][2] ;    //                      dispozitiv_de_lupta_caroiaj_x[n][1] = indica codificarea axei 09

private :

    void introduce_dispozitivul_de_lupta();
    void salveaza_dispozitivul_de_lupta();
    void afiseaza_dispozitivul_de_lupta();
} ;



extern dispozitiv_de_lupta g_dispozitiv_de_lupta;


#endif//__dispozitiv_de_lupta_h__
