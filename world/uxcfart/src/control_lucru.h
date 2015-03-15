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



#ifndef __control_lucru_h__
#define __control_lucru_h__



//c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>
#include <limits>


//c++
#include <iomanip>
#include <iostream>


//misc
#include "unistd.hpp"
#include "filename.hpp"
#include "string.hpp"



class control_lucru
{

public :
    control_lucru();
    ~control_lucru();

    void control_lucru_control();

    //--- files -------
    misc::string control_lucru_get_bmm_path() const;
    misc::string control_lucru_get_pc_test_path() const;
    misc::string control_lucru_get_tf_test_path() const;
    misc::string control_lucru_get_pc_test_rezolvare_path() const;
    misc::string control_lucru_get_tf_test_rezolvare_path() const;
    misc::string control_lucru_get_cmb_path() const;
    misc::string control_lucru_get_dispozitiv_path() const;
    misc::string control_lucru_get_dgt_path() const;
    misc::string control_lucru_get_tf_date_path() const;
    //---end files ----

    misc::string control_lucru_PWD;


    //---input from stdin
    void control_lucru_getstdin(char* buff, unsigned int size);
    void control_lucru_getstdin(float& val);
    void control_lucru_getstdin(int& val);
    void control_lucru_getstdin(long& val);



private:
    int control_lucru_inceperea_aplicatiei ;
    int control_lucru_fisier_lucrare_P_C ;
    int control_lucru_fisier_lucrare_T_F ;


public :
    int control_lucru_P_C ;     //  preg. compl        
    int control_lucru_F_B ;     //  foc de baraj
    int control_lucru_C_M_B ;   //  cond meteo si bal
    int control_lucru_B_M_M ;   //  B.M.M.
    int control_lucru_D_G ;     //  distante si gismente
    int control_lucru_C_C ;     //  corectii calculate
    int control_lucru_D_L ;     //  dispozitiv de lupta

    int control_lucru_T_F ;     //  trqans
    int control_lucru_date_T_F ; // Dt-RT, Mdt-RT, Kt, dDir_r-RT




    // indica functiilor <<registru>> PC si TF sa scrie noile date in fisierele de lucru ;
    int control_lucru_stare_date_T_F;
    int control_lucru_stare_date_P_C;

    int control_lucru_fisier_cumulat_P_C_I_O ; // f = "PC_Test.doc" ;
    int control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef ; //  f = "PC_Test_Rezolvare.doc" ;

    int control_lucru_fisier_cumulat_T_F_I_O ;  //  f = "TF_Test.doc" ;
    int control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef ; //  f = "TF_Test_Rezolvare.doc" ;


    int control_lucru_intrerupe_calcul_depasire_limite[3] ;  //  se intrerupe

    void control_lucru_indicarea_obiectivelor_zero();
};




extern control_lucru g_control_lucru;

#endif//__control_lucru_h__
