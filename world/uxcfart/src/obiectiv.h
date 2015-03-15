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



#ifndef __obiectiv_h__
#define __obiectiv_h__




//c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>


//c++
#include <iomanip>
#include <iostream>
#include <limits>



class obiectiv
{
public :
    obiectiv();
    ~obiectiv();


    // [0,1,2] = 1,2,3 numarul Bt care trage    
    int obiectiv_btno[3] ;

    // foc de baraj - dreapta
    float obiectiv_X_dreapta;
    float obiectiv_Y_dreapta;
    float obiectiv_h_dreapta;

    // foc de baraj - stanga
    float obiectiv_X_stanga;
    float obiectiv_Y_stanga;
    float obiectiv_h_stanga;

    // coordonate obiectiv
    float obiectiv_X_obiectiv[3];
    float obiectiv_Y_obiectiv[3];
    float obiectiv_h_obiectiv[3];

    // Elemente initiale de tragere ;
    float obiectiv_norma_consum[3];
    float obiectiv_ritm_de_tragere[3];
    float obiectiv_timp_ciocan_de_foc[3];
    float obiectiv_corectie_Bataie[3];
    float obiectiv_corectie_Directie[3];

    float obiectiv_Dt[3];
    float obiectiv_delta_h[3];
    float obiectiv_Mdt[3];
    float obiectiv_gisment_obiectiv[3];

    float obiectiv_Dc[3];
    float obiectiv_Ic[3];
    float obiectiv_Niv[3];
    float obiectiv_Mdc[3];
    float obiectiv_fascicul[3];
    float obiectiv_nr_directii[3];
    float obiectiv_consum_piesa[3];

    float obiectiv_furcuta[3];
    float obiectiv_Kd[3];
    float obiectiv_Sd[3];
    float obiectiv_Kb[3];
    float obiectiv_Ka[3];
    float obiectiv_Apb[3];
    float obiectiv_dXmiime[3];

    float obiectiv_front[3];
    float obiectiv_adancime[3];
    float obiectiv_salt[3];
    float obiectiv_val_salt_m[3];

    float obiectiv_p[3];
    float obiectiv_Do_pco[3];
    float obiectiv_To_pco[3];
    float obiectiv_p_po[3];
    float obiectiv_Do_po[3];
    float obiectiv_To_po[3];
    float obiectiv_p_pol[3];
    float obiectiv_Do_pol[3];
    float obiectiv_To_pol[3];

    float obiectiv_gama[3];
    float obiectiv_Dpo_peGama[3];
    float obiectiv_Dpol_peGama[3];

    //--date rezultate din P_C.
    float obiectiv_DdeTrag[3][4][3];
    float obiectiv_GdeTrag[3];

    float obiectiv_corectii_calculate_bataie[3][4][3];
    float obiectiv_corectii_calculate_directie[3][4][3];
    char obiectiv_nr_obiectiv[3][5];

    void obiectiv_primeste_datele(int );
    void obiectiv_primeste_bateria();
};



void getstdin2(char* buff, unsigned int size);
void getstdin2(float& val);
void getstdin2(int& val);
void getstdin2(long& val);



extern obiectiv g_obiectiv;


#endif//__obiectiv_h__
