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
#include "buletin_meteo.h"




/* global variable */
buletin_meteo g_buletin_meteo;


char grupa[16][20] = {"1102", "zi_ora_min", "alt_SMA", "dHsmadTasma",
                      "0201", "0401", "0802", "1202", "1602", "2003",
                      "2403", "3003", "4003", "5003", "6003", "3030" } ;


buletin_meteo::buletin_meteo()
{
};

buletin_meteo::~buletin_meteo()
{
};

void buletin_meteo::primeste_buletin_meteo()
{

    char g[3] ;

    while(true)
    {        
        misc::cout << U("\n\t  Introduceti B.M.M.");

        for (int i=0, k=0 ; i<400; i++, k++ )
        {
            if((k == 15) || (k == 0))
            {                
                misc::cout << U("\n\t  ") << grupa[k]; //3030
            }
            else
            {
                misc::cout << U("\n\t  ") << ::grupa[k] << U("   -   "); // 2403 - ...                
            }


            if(k == 0)
            {
                strcpy(cha[i], ::grupa[k]) ;
                continue ;
            }
            else if((k >0) && (k<4))
            {
                g_control_lucru.control_lucru_getstdin(cha[i], 100);
            }
            else if(k>3)
            {
                strcpy(cha[i++], ::grupa[k]) ;
                if (atol(cha[i-1]) == 3030)
                {
                    i = 420 ;
                    continue ;
                }

                g_control_lucru.control_lucru_getstdin(cha[i], 100);
            }


            if (atol(cha[i]) == 3030)
            {
                i = 420 ;
            }            
        } //for

        misc::cout << U("\n\t  salvati (exemplu: d sau n) = ");
        g_control_lucru.control_lucru_getstdin(g, 3);
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while

    g_control_lucru.control_lucru_B_M_M = 0 ;   //  pt. a chema fct-ia incarca_datele() ;

    salveaza_buletin_meteo();   // control_lucru_B_M_M se activeaza in functia incarca...(partic ;
};


void buletin_meteo::salveaza_buletin_meteo()
{
    FILE *fisier ;
    misc::string file(g_control_lucru.control_lucru_get_bmm_path());

    chmod(file.c_str(), S_IREAD|S_IWRITE);

    if((fisier = fopen(file.c_str(), "w+")) == NULL)
    {
        misc::cout << U("\n\t  Eroare la deschiderea fisierului BMM.dat : ");
        perror("") ;
        getchar() ;
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<400; ++i)
    {
        int prec, decim ;

        strcpy(cch[i], fcvt((double)atol(cha[i]) , 0, &prec, &decim) ) ;

        fprintf(fisier, "%s", cch[i]);
        fprintf(fisier, "\n" );

        if (atol(cha[i]) == 3030)
            i = 420 ;

    }  //  for (i=0; i<400; i++ )

    fclose(fisier);
    chmod("BMM.dat", S_IREAD);

    g_buletin_meteo.buletin_meteo_incarca();
};


void buletin_meteo::buletin_meteo_incarca()
{

    if(g_control_lucru.control_lucru_B_M_M == 0)
    {
        //citeste BMM daca nu a fost initializat
        FILE *fisier ;

        misc::string file(g_control_lucru.control_lucru_get_bmm_path());

        size_t n_ ;
        if((fisier = fopen(file.c_str(), "r")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului BMM.dat : ") ;
            perror("") ;
            getchar() ;
            exit(EXIT_FAILURE);

        }

        for (int i=0 ; i<100 ; i++ )
        {
            fscanf(fisier, "%s", &g_buletin_meteo.buletin_meteo_ch[i][0]);

            if(atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
                i = 150 ;

            n_ = strlen(g_buletin_meteo.buletin_meteo_ch[i]);
            if((fisier == NULL) ||
               (i < 29 &&  (i > 3 && (i % 2 == 0) &&  (n_ < 3 || n_> 4 || atol(g_buletin_meteo.buletin_meteo_ch[i]) < 0))) ||
               (i > 3  &&  (i % 2 != 0) && (n_ > 6 || atol(g_buletin_meteo.buletin_meteo_ch[i]) < 0 )))
            {
                misc::cout << U("\n\t  Eroare in BMM:");
                misc::cout << U("\n\t  pozitia: ") << i << U(" grupa: ") << i+1 << U(" = ") << atol(g_buletin_meteo.buletin_meteo_ch[i]);
                misc::cout << U("\n\t  Programul va fi terminat");
                fclose(fisier);
                getchar();
                exit(EXIT_FAILURE);
            }//if
        }//for

        fclose(fisier);

        g_control_lucru.control_lucru_B_M_M = 1 ;     //  B. M. M. a fost incarcat ;
        g_control_lucru.control_lucru_C_C = 0 ;  //  trebuie sa se recalculeze corectiile calculate ;
    } //if
};


void buletin_meteo::afiseaza_buletin_meteo()
{
    if(g_control_lucru.control_lucru_B_M_M == 0)
        g_buletin_meteo.buletin_meteo_incarca();


    //
    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  Buletin Meteo Mediu");
    
    for(int i=0, k=0, j=0 ; i<300; i++, k++, j++)
    {
        if(k == 0)
        {
            misc::cout << U("\n\t  ") << g_buletin_meteo.buletin_meteo_ch[i];
            
            if(atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
            {                
                misc::cout << U("\n\t  Terminat.");
                getchar();
                i = 400 ;
            }
        }
        else if((k > 0) && (k < 4))
        {
            misc::cout << U("\n\t  ") << grupa[k] << U("   -   ") << g_buletin_meteo.buletin_meteo_ch[i];            
            if((atol(grupa[k]) == 3030) || (atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030))
            {              
                misc::cout << U("\n\t  Terminat.");
                getchar() ;
                i = 400 ;
            }
        }
        else
        {
            misc::cout << U("\n\t  ") << g_buletin_meteo.buletin_meteo_ch[i++];            
            if(atol(g_buletin_meteo.buletin_meteo_ch[i-1]) == 3030)
            {            
                misc::cout << U("\n\t  Terminat.");
                getchar();
                i = 400 ;
                continue ;
            }
            misc::cout << U("   -   ") << g_buletin_meteo.buletin_meteo_ch[i];            
        }


        if(atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
        {         
            misc::cout << U("\n\t  Terminat.");
            getchar() ;
            i = 400 ;
            continue ;
        }
    }//for
};


void buletin_meteo::registru()
{
};

void buletin_meteo::buletin_meteo_control()
{
    while(true)
    {
        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Buletin Meteo Mediu\n");
        misc::cout << U("\n\t  1  Introducere BMM de la tastatura");
        misc::cout << U("\n\t  2  Afisare BMM");
        misc::cout << U("\n\t  3  Intoarcere");
        misc::cout << U("\n");        
        misc::cout << U("\n\t  Optiune (1,2 sau 3) = ");      

        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);

        if( g == 1 )
            primeste_buletin_meteo();
        else if(g == 2)
            afiseaza_buletin_meteo();
        else if(g == 3)
            return;
    } // while
};
