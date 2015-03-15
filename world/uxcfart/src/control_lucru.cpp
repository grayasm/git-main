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


//c
//c++
//misc
#include "stream.hpp"

//program
#include "control_lucru.h"



/* global variable */
control_lucru g_control_lucru;




control_lucru::control_lucru()
{
    control_lucru_inceperea_aplicatiei = 0 ;  //  neanceputa implicit ;
    control_lucru_P_C = 0 ;    
    
    
    
    control_lucru_F_B = 0 ;
    
    
    control_lucru_C_M_B = 0 ;
    control_lucru_B_M_M = 0 ;
    control_lucru_D_G   = 0 ;
    control_lucru_C_C   = 0 ;
    control_lucru_D_L = 0 ;

    control_lucru_T_F = 0 ;
    control_lucru_date_T_F = 0 ;

    control_lucru_fisier_lucrare_P_C = 0 ;
    control_lucru_fisier_lucrare_T_F = 0 ;

    //indica functiilor <<registru>> PC si TF sa scrie noile date in fisierele de lucru ;
    control_lucru_stare_date_T_F = 1 ;
    control_lucru_stare_date_P_C = 1 ;

    control_lucru_fisier_cumulat_P_C_I_O = 0 ; // f = "PC_Test.doc" ;
    control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef = 0 ; //  f = "PC_Test_Rezolvare.doc"

    control_lucru_fisier_cumulat_T_F_I_O = 0 ;  //  f = "TF_Test.doc" ;
    control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef = 0 ; //  f = "TF_Test_Rezolvare.doc" ;
};

control_lucru::~control_lucru()
{
};

void control_lucru::control_lucru_indicarea_obiectivelor_zero()
{
    int j=0;

    while(j < 3)
    {
        control_lucru_intrerupe_calcul_depasire_limite[j++] = 0 ;
    }
       
    
    
    control_lucru_F_B = 0 ;
    
    
};

void control_lucru::control_lucru_control()
{

    char g[3];

    //////////////////////////////////////////////////////////////////////////
    // configurare generala
    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  configurarea aplicatiei\n");
    misc::cout << U("\n\t  in cazul in care incepeti o noua aplicatie");
    misc::cout << U("\n\t  toate calculele vor fi salvate si vor putea");
    misc::cout << U("\n\t  fi analizate si/sau imprimate la terminare programului\n");
    misc::cout << U("\n\t  incepeti o noua aplicatie ? (d/n) = ");


    control_lucru_getstdin(g, 3);

        
    if(g[0] == 'd' || g[0] == 'D')
    {
        control_lucru_inceperea_aplicatiei = 1;
    }
    else
    {
        control_lucru_inceperea_aplicatiei = 0;
    }


    if(control_lucru_inceperea_aplicatiei == 0)
        return;

    
    //////////////////////////////////////////////////////////////////////////
    // pregatire completa - datele initiale ale problemei (testului)

    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  in cazul folosirii pregatirii complete, exista");
    misc::cout << U("\n\t  posibilitatea salvarii automate in fisierul \"PC_Test.doc\"");
    misc::cout << U("\n\t  a datelor initiale ale problemei (testului), adica:\n");
    misc::cout << U("\n\t  > dispozitivul de lupta");
    misc::cout << U("\n\t  > buletinul meteo-mediu");
    misc::cout << U("\n\t  > conditiile meteo si balistice");
    misc::cout << U("\n\t  > distantele si gismentele de tragere");
    misc::cout << U("\n\t  > indicarea obiectivelor\n");
    misc::cout << U("\n\t  optiune (d/n) = ");
   
    control_lucru_getstdin(g, 3);


    if(g[0] == 'd' || g[0] == 'D')    
    {
        control_lucru_fisier_cumulat_P_C_I_O = 1 ;
    }
    else
    {
        control_lucru_fisier_cumulat_P_C_I_O = 0 ;
    }



    //////////////////////////////////////////////////////////////////////////
    // pregatire completa - rezolvarea problemei (testului)

    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  in cazul folosirii pregatirii complete, exista");
    misc::cout << U("\n\t  posibilitatea salvarii automate in fisierul \"PC_Test_Rezolvare.doc\"");
    misc::cout << U("\n\t  a rezolvarii problemei (testului), adica:\n");
    misc::cout << U("\n\t  > rezolvarea detaliata a pregatirii complete");
    misc::cout << U("\n\t  > elementele topografice si calculate la obiective");
    misc::cout << U("\n\t  > datele si coeficientii la obiective\n");
    misc::cout << U("\n\t  optiune (d/n) = ");


    control_lucru_getstdin(g, 3);    

    if(g[0] == 'D' || g[0] == 'd')
    {
        control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef = 1 ; //  f = "PC_Test_Rezolvare.doc
    }
    else
    {
        control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef = 0 ;
    }


    //////////////////////////////////////////////////////////////////////////
    // transport de foc - datele initiale ale problemei (testului)


    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  in cazul folosirii transportului de foc, exista");
    misc::cout << U("\n\t  posibilitatea salvarii automate in fisierul \"TF_Test.doc\"");
    misc::cout << U("\n\t  a datelor initiale ale problemei (testului), adica:\n");
    misc::cout << U("\n\t  > dispozitivul de lupta");
    misc::cout << U("\n\t  > elementele pe reperele de tragere");
    misc::cout << U("\n\t  > indicarea obiectivelor\n");
    misc::cout << U("\n\t  optiune (d/n) = ");

    control_lucru_getstdin(g, 3);

    if(g[0] == 'D' || g[0] == 'd')
    {
        control_lucru_fisier_cumulat_T_F_I_O = 1 ;  //  f = "TF_Test.doc" ;
    }
    else
    {
        control_lucru_fisier_cumulat_T_F_I_O = 0 ;
    }


    //////////////////////////////////////////////////////////////////////////
    // transport de foc - rezolvarea problemei (testului)

    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  in cazul folosirii transportului de foc, exista");
    misc::cout << U("\n\t  posibilitatea salvarii automate in fisierul \"TF_Test_Rezolvare.doc\"");
    misc::cout << U("\n\t  a rezolvarii problemei (testului), adica:\n");
    misc::cout << U("\n\t  > elementele topografice si calculate la obiective ");
    misc::cout << U("\n\t  > datele si coeficientii la obiective\n");
    misc::cout << U("\n\t  optiune (d/n) = ");

    control_lucru_getstdin(g, 3);

    if(g[0] == 'D' || g[0] == 'd')
    {
        control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef = 1 ; //  f = "TF_Test_Rezolvare.doc" ;
    }
    else
    {
        control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef = 0 ;
    }


    //////////////////////////////////////////////////////////////////////////    
    FILE *f;    
    if(control_lucru_fisier_cumulat_P_C_I_O == 1)
    {
        misc::string file(control_lucru_get_pc_test_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        f =  fopen(file.c_str(), "w+");
        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }
    else
    {
        misc::string file(control_lucru_get_pc_test_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        unlink(file.c_str());
    }


    if(control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef == 1)
    {
        misc::string file(control_lucru_get_pc_test_rezolvare_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        f =  fopen(file.c_str(), "w+");
        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }
    else
    {
        misc::string file(control_lucru_get_pc_test_rezolvare_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        unlink(file.c_str());
    }

    if(control_lucru_fisier_cumulat_T_F_I_O == 1)
    {
        misc::string file(control_lucru_get_tf_test_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        f =  fopen(file.c_str(), "w+");
        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }
    else
    {
        misc::string file(control_lucru_get_tf_test_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        unlink(file.c_str());
    }

    if(control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef == 1)
    {
        misc::string file(control_lucru_get_tf_test_rezolvare_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        f =  fopen(file.c_str(), "w+");
        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }
    else
    {
        misc::string file(control_lucru_get_tf_test_rezolvare_path());
        chmod(file.c_str(), S_IREAD|S_IWRITE);
        unlink(file.c_str());
    }

};

misc::string control_lucru::control_lucru_get_bmm_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("BMM.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_pc_test_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("PC_Test.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_tf_test_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("TF_Test.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_pc_test_rezolvare_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("PC_Test_Rezolvare.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_tf_test_rezolvare_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("TF_Test_Rezolvare.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_cmb_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("CMB.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_dispozitiv_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("Dispozitiv.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_dgt_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("DGT.dat");
    return file.get_path();
};

misc::string control_lucru::control_lucru_get_tf_date_path() const
{
    misc::filename file(control_lucru_PWD);
    file.set_file_name("TF_date.dat");
    return file.get_path();
};


void control_lucru::control_lucru_getstdin(char* buff, unsigned int size)
{
    std::cin.getline(buff, size);
    if( std::cin.fail() )
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
    }
};

void control_lucru::control_lucru_getstdin(float& val)
{
    char buf[30]="";
    control_lucru_getstdin(buf, 30);
    val = (float)atof(buf);
};

void control_lucru::control_lucru_getstdin(int& val)
{
    char buf[30]="";
    control_lucru_getstdin(buf, 30);
    val = atoi(buf);
};

void control_lucru::control_lucru_getstdin(long& val)
{
    char buf[30]="";
    control_lucru_getstdin(buf, 30);
    val = atol(buf);
};