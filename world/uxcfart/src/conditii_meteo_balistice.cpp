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
#include "conditii_meteo_balistice.h"



conditii_meteo_balistice g_conditii_meteo_balistice;




conditii_meteo_balistice::conditii_meteo_balistice()
{
};

conditii_meteo_balistice::~conditii_meteo_balistice()
{
};

void conditii_meteo_balistice::primeste_conditii_meteo_balistice()
{
    for(int i=0; i<3; i++)
    {
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Conditii balistice si meteorologice\n");
        misc::cout << U("\n\t  Bateria  ") << i + 1 << U("  artilerie\n"); 

        misc::cout << U("\n\t  Pentru incarcatura completa tastati 0");
        misc::cout << U("\n\t  Incarcatura (0, 1, 2, 3, 4, 5) = ");    
        g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_inc[i]);
        
        misc::cout << U("\n\t  dvop = ");
        g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_vop[i]);
        

        misc::string sinc;
        if(conditii_meteo_balistice_inc[i] == 0)
        {
            sinc = U("Completa");
        }
        else
        {
            sinc = misc::from_value(conditii_meteo_balistice_inc[i], 0);
            sinc += U(" -a");
        }

        misc::cout << U("\n\t  vo (inc ") << sinc << U(") = ");
        g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_voinc[i]);
        

        misc::cout << U("\n\t  T (inc ") << std::setprecision(0) << conditii_meteo_balistice_inc[i] << U("-a) = ");
        g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_tinc[i]);
        

        misc::cout << U("\n\t  semn proiectil (exemplu: -3 sau +2 sau 0) = ");
        g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_q[i]);
                
        
        while(true)
        {
            misc::cout << U("\n\t  proiectil vopsit (exemplu: d sau n) = ");
            g_control_lucru.control_lucru_getstdin(conditii_meteo_balistice_voppr[i], 5);

            if( conditii_meteo_balistice_voppr[i][0] == 'd' ||
                conditii_meteo_balistice_voppr[i][0] == 'D' ||
                conditii_meteo_balistice_voppr[i][0] == 'n' ||
                conditii_meteo_balistice_voppr[i][0] == 'N' )
                break;
        } // while

    } //for

    g_control_lucru.control_lucru_C_M_B = 1 ;
    g_control_lucru.control_lucru_C_C = 0 ;

    salveaza_conditii_meteo_balistice ();
};

void conditii_meteo_balistice::salveaza_conditii_meteo_balistice()
{
    const int CMB_SIZE=18;    
    misc::string cmb_date[CMB_SIZE];

    for(int i=0; i<3; i++)
    {        
        cmb_date[i]    = misc::from_value(conditii_meteo_balistice_inc[i], 2);
        cmb_date[i+3]  = misc::from_value(conditii_meteo_balistice_vop[i], 2);
        cmb_date[i+6]  = misc::from_value(conditii_meteo_balistice_voinc[i], 2);
        cmb_date[i+9]  = misc::from_value(conditii_meteo_balistice_tinc[i], 2);
        cmb_date[i+12] = misc::string(conditii_meteo_balistice_voppr[i], 1);
        cmb_date[i+15] = misc::from_value(conditii_meteo_balistice_q[i], 2);
    } //for

    misc::string file(g_control_lucru.control_lucru_get_cmb_path());

    chmod(file.c_str(), S_IREAD|S_IWRITE);
    FILE *fisier ;
    fisier = fopen(file.c_str(), "w+");

    for (int i=0; i<18; i++)
    {
        fprintf(fisier, "%s", cmb_date[i].c_str());
        fprintf(fisier, "\n" );
    }

    fclose(fisier);
    chmod("CMB.dat", S_IREAD);
};

void conditii_meteo_balistice::conditii_meteo_balistice_incarca()
{
    if(g_control_lucru.control_lucru_C_M_B == 0)
    {
        char itt[18][20] ;
        FILE *fisier ;

        misc::string file(g_control_lucru.control_lucru_get_cmb_path());

        fisier = fopen(file.c_str(), "r");

        for (int i=0; i < 18; ++i)
        {
            fscanf(fisier, "%s", &itt[i][0]);
        }

        fclose(fisier);

        for(int i=0; i< 3; i++)
        {
            conditii_meteo_balistice_inc[i] = (float)atof(itt[i]); // 0 -> 2
            conditii_meteo_balistice_vop[i] = (float)atof(itt[i+3]); // 3 -> 5
            conditii_meteo_balistice_voinc[i] = (float)atof(itt[i+6]);  // 6 -> 8
            conditii_meteo_balistice_tinc[i] = (float)atof(itt[i+9]);   // 9 -> 11
            //conditii_meteo_balistice_voppr[i][0] = itt[i+12][0] ;     // 12 -> 14
            strncpy(conditii_meteo_balistice_voppr[i], itt[i+12], 20);
            conditii_meteo_balistice_q[i] = (float)atof(itt[i+15]);      // 15 -> 17


            bool bexit = false;
            if( conditii_meteo_balistice_inc[i] < 0 || 
                conditii_meteo_balistice_inc[i] > 5)
            {
                bexit = true;
                misc::cout << U("\n\t  incarcatura invalida");
            }
            
            if( conditii_meteo_balistice_voinc[i] < 0 )
            {
                bexit = true;
                misc::cout << U("\n\t  valoarea Vo(inc) invalida");
            }
               
            if( conditii_meteo_balistice_tinc[i] > 50 ||
                conditii_meteo_balistice_tinc[i] < -50 )
            {
                bexit = true;
                misc::cout << U("\n\t  valoarea Tinc invalida");
            }
                
            
            if( conditii_meteo_balistice_voppr[i][0] == 0 )
            {
                bexit = true;
                misc::cout << U("\n\t  valoarea vopsea proiectil invalida");
            }
            
            if( conditii_meteo_balistice_q[i] < -6 || 
                conditii_meteo_balistice_q[i] > 6 )
            {
                bexit = true;
                misc::cout << U("\n\t  valoarea q proiectil invalida");
            }
            
            // exit for any invalid value
            if(bexit)
            {
                getchar();
                exit(EXIT_FAILURE);
            }
        }

        g_control_lucru.control_lucru_C_M_B = 1 ;
    }
};

void conditii_meteo_balistice::afiseaza_conditii_meteo_balistice()
{
    if(g_control_lucru.control_lucru_C_M_B == 0)
    {
        conditii_meteo_balistice_incarca();
    }

    for(int i=0; i<3; i++)
    {
        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Conditii meteo si balistice");
        misc::cout << U("\n\t  Bt ") << i+1 << U(" Art");
        misc::cout << U("\n\t  Ob. cal. 152 mm md.'81 ");
        misc::cout << U("\n\t  Proiectil OF-540");

        if(conditii_meteo_balistice_inc[i] == 0)
        {
            misc::cout << U("\n\t  Inc = C");
        }
        else
        {            
            misc::cout << U("\n\t  Inc = a ") << std::fixed << std::setprecision(0) << conditii_meteo_balistice_inc[i] << U(" -a");            
        }
        
        
        misc::cout << U("\n\t  dvop = ") << std::fixed << std::setprecision(2) << conditii_meteo_balistice_vop[i] << U(" %");        
        misc::cout << U("\n\t  voinc = ") << std::fixed << std::setprecision(0) << conditii_meteo_balistice_voinc[i] << U(" m/s");        
        misc::cout << U("\n\t  Tinc = ") << std::fixed << std::setprecision(2) << conditii_meteo_balistice_tinc[i] << U(" oC");
        misc::cout << U("\n\t  Vops = ") << conditii_meteo_balistice_voppr[i][0];        
        misc::cout << U("\n\t  q = ") << std::fixed << std::setprecision(0) << conditii_meteo_balistice_q[i];        
        
        getchar();
    } //for
};

void conditii_meteo_balistice::registru()
{
};



void conditii_meteo_balistice::conditii_meteo_balistice_control()
{
    while(true)
    {
        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Conditii meteo si balistice");        
        misc::cout << U("\n\t  1  Introduceti datele");
        misc::cout << U("\n\t  2  Afisarea datelor");
        misc::cout << U("\n\t  3  Intoarcere");
        misc::cout << U("\n");
        misc::cout << U("\n\t  Optiune (1, 2 sau 3) = ");

        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);

        if(g == 1)
            primeste_conditii_meteo_balistice();
        else if(g == 2)
            afiseaza_conditii_meteo_balistice();
        else if(g == 3)
            return;
        
    } // while
};
