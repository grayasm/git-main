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
#include <assert.h>
//c++
//misc
#include "stream.hpp"

//program
#include "dispozitiv_de_lupta.h"


/* global variable */
dispozitiv_de_lupta g_dispozitiv_de_lupta;





dispozitiv_de_lupta::dispozitiv_de_lupta()
{
};

dispozitiv_de_lupta::~dispozitiv_de_lupta()
{
};

void dispozitiv_de_lupta::introduce_dispozitivul_de_lupta()
{
    char g[3];  //  confirmare de introducere a datelor

    char cXpt[3][10];
    char cYpt[3][10];
    char chpt[3][10];

    char cXpco[3][10];
    char cYpco[3][10];
    char chpco[3][10];

    char cXpo[2][10];
    char cYpo[2][10];
    char chpo[2][10];
    char cGdb[10];

    char limita_st[3][10];
    char limita_dr[3][10];

    char distanta_min[10];
    char distanta_max[10];

    char cScara_hartii[3];
    char cCaroiaj_x[10][2][10];
    char cCaroiaj_y[10][2][10];  // pentru memorarea caroiajului

//Pozitia_de_tragere : ;

    while(true)
    {        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Introduceti dispozitivul de lupta");
        
        for(int j=0; j<3; ++j)
        {
            misc::cout << U("\n\t  PT Bt ") << j+1 << U(" Art");
            
            misc::cout << U("\n\t  x = ");
            g_control_lucru.control_lucru_getstdin(cXpt[j], 10);
            
            misc::cout << U("\n\t  y = ");            
            g_control_lucru.control_lucru_getstdin(cYpt[j], 10);
            
            misc::cout << U("\n\t  h = ");
            g_control_lucru.control_lucru_getstdin(chpt[j], 10);
        } //for

    
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);
        
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    while(true)
    {
        //
        clrscr();
        misc::cout << U("\n\n");   
        
        for(int j=0; j<3; ++j)
        {            
            misc::cout << U("\n\t  PCO Bt ") << j+1 << U(" Art");
            
            misc::cout << U("\n\t  x = ");
            g_control_lucru.control_lucru_getstdin(cXpco[j], 10);
            
            
            misc::cout << U("\n\t  y = ");
            g_control_lucru.control_lucru_getstdin(cYpco[j], 10);       
            
            misc::cout << U("\n\t  h = ");            
            g_control_lucru.control_lucru_getstdin(chpco[j], 10);       
        }

        
        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);     

        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    
    while(true)
    {
        
        //
        clrscr();
        misc::cout << U("\n\n");               
        
        for(int j=0; j<2; ++j)
        {
            if(j ==0)
            {
                misc::cout << U("\n\t  PO Dn");                
            }
            else
            {
                misc::cout << U("\n\t  POL Dn");
            }

            
            misc::cout << U("\n\t  x = ");
            g_control_lucru.control_lucru_getstdin(cXpo[j], 10);

            misc::cout << U("\n\t  y = ");
            g_control_lucru.control_lucru_getstdin(cYpo[j], 10);
            
            misc::cout << U("\n\t  h = ");
            g_control_lucru.control_lucru_getstdin(chpo[j], 10);
        } //for

        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while



    while(true)
    {
        //
        clrscr();
        misc::cout << U("\n\n");

        misc::cout << U("\n\t  Gdb = ");
        g_control_lucru.control_lucru_getstdin(cGdb, 10);   
        dispozitiv_de_lupta_Gdb = (float)atof(cGdb);


        misc::cout << U("\n\t  scara hartii");
        misc::cout << U("\n\t  1 -> 1:25.000");
        misc::cout << U("\n\t  2 -> 1:50.000");
        misc::cout << U("\n\t  r = ");
        g_control_lucru.control_lucru_getstdin(cScara_hartii, 3);
        dispozitiv_de_lupta_scara_hartii = (float)atof(cScara_hartii);

        misc::cout << U("\n");        
        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    while(true)
    {
        //
        clrscr();
        misc::cout << U("\n\n");
        
        for(int j=0; j<3; ++j)
        {
            misc::cout << U("\n\t  Limitele in directie pt Bt ") << j+1 << U(" Art");
            
            misc::cout << U("\n\t  stanga = ");
            g_control_lucru.control_lucru_getstdin(limita_st[j], 10);       
            
            misc::cout << U("\n\t  dreapta = ");
            g_control_lucru.control_lucru_getstdin(limita_dr[j], 10);       
        } //for

        misc::cout << U("\n\t  distanta min = ");        
        g_control_lucru.control_lucru_getstdin(distanta_min, 10);
        
        misc::cout << U("\n\t  distanta max = ");        
        g_control_lucru.control_lucru_getstdin(distanta_max, 10);   

        
        
        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    while(true)
    {

        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Codificarea hartii pt 10 carouri pe X");        

        for(int j=0; j<10; j++)
        {            
            if(j == 0)
            {                
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe x (ex: 50000) = ");                
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][0], 10);                
                
                misc::cout << U("\n\t  codificare (ex: 15) = "); 
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][1], 10);           
            }
            else if(dispozitiv_de_lupta_scara_hartii ==  1)
            {
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe x (ex: ") << ((float)atof(cCaroiaj_x[0][0]) + (float)(j * 4000)) << U(") = ");                
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][0], 10);
                
                misc::cout << U("\n\t  codificare = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][1], 10);           
            }
            else
            {
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe x (ex: ") << ((float)atof(cCaroiaj_x[0][0])+ (float)(8000 * j)) << U(") = ");                
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][0], 10);
                
                misc::cout << U("\n\t  codificare = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_x[j][1], 10);           
            }
        }

        
        
        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);        
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    while(true)
    {
        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Codificarea hartii pt 10 carouri pe Y");
        

        for(int j=0; j<10; j++)
        {            
            if(j == 0)
            {
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe y (ex: 50000) = ");                   
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][0], 10);           
                                
                misc::cout << U("\n\t  codificare (ex: 15) = "); 
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][1], 10);           
            }
            else if(dispozitiv_de_lupta_scara_hartii ==  1)
            {
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe y (ex: ") << ((float)atof(cCaroiaj_y[0][0])+ (float)(4000 * j)) << U(") = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][0], 10);          
                
                misc::cout << U("\n\t  codificare = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][1], 10);           
            }
            else
            {
                misc::cout << U("\n\t  valoare colt carou ") << j+1 << U(" pe y (ex: ") << ((float)atof(cCaroiaj_y[0][0]) + (float)(8000 * j)) << U(") = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][0], 10);
                                                
                misc::cout << U("\n\t  codificare = ");
                g_control_lucru.control_lucru_getstdin(cCaroiaj_y[j][1], 10);           
            }
        }


        misc::cout << U("\n\t  salvati (d) sau reintroduceti datele ? = ");
        g_control_lucru.control_lucru_getstdin(g, 3);        
        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while


    //  INCEPEREA TRANSFORMARILOR ;

    for(int j=0; j<10; ++j)
    {
        dispozitiv_de_lupta_caroiaj_x[j][0] = (float)atof(cCaroiaj_x[j][0]);
        dispozitiv_de_lupta_caroiaj_x[j][1] = (float)atof(cCaroiaj_x[j][1]);
        dispozitiv_de_lupta_caroiaj_y[j][0] = (float)atof(cCaroiaj_y[j][0]);
        dispozitiv_de_lupta_caroiaj_y[j][1] = (float)atof(cCaroiaj_y[j][1]);
    }

    dispozitiv_de_lupta_distanta_minima = (float)atof(distanta_min);
    dispozitiv_de_lupta_distanta_maxima = (float)atof(distanta_max);

    for(int j=0; j<3; j++)
    {
        dispozitivul_de_lupta_Xpt[j] = (float)atof(cXpt[j]);
        dispozitiv_de_lupta_Ypt[j] = (float)atof(cYpt[j]);
        dispozitiv_de_lupta_hpt[j] = (float)atof(chpt[j]);

        dispozitiv_de_lupta_Xpco[j] = (float)atof(cXpco[j]);
        dispozitiv_de_lupta_Ypco[j] = (float)atof(cYpco[j]);
        dispozitiv_de_lupta_hpco[j] = (float)atof(chpco[j]);

        dispozitiv_de_lupta_limita_stanga[j] = (float)atof(limita_st[j]);
        dispozitiv_de_lupta_limita_dreapta[j] = (float)atof(limita_dr[j]);
    } //for


    for(int j=0; j<2; j++ )
    {
        dispozitiv_de_lupta_Xpo[j] = (float)atof(cXpo[j]);
        dispozitiv_de_lupta_Ypo[j] = (float)atof(cYpo[j]);
        dispozitiv_de_lupta_hpo[j] = (float)atof(chpo[j]);
    }

    g_control_lucru.control_lucru_D_L = 1 ;
    g_control_lucru.control_lucru_stare_date_T_F = 1 ;
    g_control_lucru.control_lucru_stare_date_P_C = 1 ;


    salveaza_dispozitivul_de_lupta();

};

void dispozitiv_de_lupta::afiseaza_dispozitivul_de_lupta()
{

    if(g_control_lucru.control_lucru_D_L == 0)
    {
        dispozitivul_de_lupta_incarca();
    }

       
    
    for(int j=0; j<3; ++j)
    {
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Coordonatele dispozitivului de lupta");

        misc::cout << U("\n\t  PT Bt ") << j+1 << U(" Art");
        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(2) << dispozitivul_de_lupta_Xpt[j];
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_Ypt[j];
        misc::cout << U("\n\t  h = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_hpt[j]; 
        
        misc::cout << U("\n");
        misc::cout << U("\n\t  PCO Bt ") << j+1 << U(" Art");
        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_Xpco[j];
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_Ypco[j];
        misc::cout << U("\n\t  h = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_hpco[j];
               
        getchar();
    }



    //
    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  Coordonatele dispozitivului de lupta");

    for(int j=0; j<2; j++)
    {
        if(j ==0)
        {
            misc::cout << U("\n\t  PO Dn");            
        }
        else
        {
            misc::cout << U("\n");
            misc::cout << U("\n\t  POL Dn");
        }

        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_Xpo[j];
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_Ypo[j];
        misc::cout << U("\n\t  h = ") << std::fixed << std::setprecision(2) << dispozitiv_de_lupta_hpo[j];        
    }
    
    getchar();
    
    //
    clrscr();
    misc::cout << U("\n\n");    
    misc::cout << U("\n\t  Gdb = ") << std::fixed << std::setprecision(0) << dispozitiv_de_lupta_Gdb;    
    
    if(dispozitiv_de_lupta_scara_hartii == 1)
    {
        misc::cout << U("\n\t  Scara hartii 1:25.000");
    }
    else if(dispozitiv_de_lupta_scara_hartii == 2)
    {
        misc::cout << U("\n\t  Scara hartii 1:50.000");
    }
    else
    {
        misc::cout << U("\n\t  Scara hartii necunoscuta");
    }

    
    for(int j=0; j<3; ++j)
    {
        misc::cout << U("\n\t  Limite in directie Bt ") << j+1 << U(" Art");
        misc::cout << U("\n\t  stanga = ") << dispozitiv_de_lupta_limita_stanga[j];
        misc::cout << U("\n\t  dreapta= ") << dispozitiv_de_lupta_limita_dreapta[j];
        misc::cout << U("\n");        
    } //for

    misc::cout << U("\n\t  Limite in bataie");
    misc::cout << U("\n\t  Distanta minima = ") << dispozitiv_de_lupta_distanta_minima;
    misc::cout << U("\n\t  Distanta maxima = ") << dispozitiv_de_lupta_distanta_maxima;


    getchar();
    
    //
    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  Codificarea hartii pt 10 carouri pe axa X");
    
    for(int j=0; j<10; ++j)
    {
        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(0) << dispozitiv_de_lupta_caroiaj_x[j][0] << U(" codificat = ") << dispozitiv_de_lupta_caroiaj_x[j][1];
    }

    misc::cout << U("\n");
    misc::cout << U("\n\t  Codificarea hartii pt 10 carouri pe axa Y");

    for(int j=0; j<10; ++j)
    {
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(0) << dispozitiv_de_lupta_caroiaj_y[j][0] << U(" codificat = ") << dispozitiv_de_lupta_caroiaj_y[j][1];        
    }

    getchar();
};

void  dispozitiv_de_lupta::salveaza_dispozitivul_de_lupta()
{

    FILE *f ;

    const int DL_SIZE = 74;
    misc::string dl_data[DL_SIZE];

    misc::string file(g_control_lucru.control_lucru_get_dispozitiv_path());

    chmod(file.c_str(), S_IREAD|S_IWRITE );

    if((f = fopen(file.c_str(), "w+")) == NULL)
    {
        misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
        perror("");
        abort();
    }

    
    for(int j=0; j<3; j++)
    {
        dl_data[j]    = misc::from_value(dispozitivul_de_lupta_Xpt[j], 2);
        dl_data[j+3]  = misc::from_value(dispozitiv_de_lupta_Ypt[j], 2);
        dl_data[j+6]  = misc::from_value(dispozitiv_de_lupta_hpt[j], 2);
        dl_data[j+9]  = misc::from_value(dispozitiv_de_lupta_Xpco[j], 2);
        dl_data[j+12] = misc::from_value(dispozitiv_de_lupta_Ypco[j], 2);
        dl_data[j+15] = misc::from_value(dispozitiv_de_lupta_hpco[j], 2);
        dl_data[j+18] = misc::from_value(dispozitiv_de_lupta_limita_stanga[j], 2);
        dl_data[j+21] = misc::from_value(dispozitiv_de_lupta_limita_dreapta[j], 2);
    }


    for(int i=0, j=24; j < 26; i++, j++)
    {
        assert(i < 2);
        dl_data[j] = misc::from_value(dispozitiv_de_lupta_Xpo[i], 2);
        dl_data[j+2] = misc::from_value(dispozitiv_de_lupta_Ypo[i], 2);
        dl_data[j+4] = misc::from_value(dispozitiv_de_lupta_hpo[i], 2);
    }


    dl_data[30] = misc::from_value(dispozitiv_de_lupta_distanta_maxima, 2);
    dl_data[31] = misc::from_value(dispozitiv_de_lupta_distanta_minima, 2);
    dl_data[32] = misc::from_value(dispozitiv_de_lupta_Gdb, 2);
    dl_data[33] = misc::from_value(dispozitiv_de_lupta_scara_hartii, 2);


    for(int j=0; j< 10; j++)
    {
        dl_data[j+34]    = misc::from_value(dispozitiv_de_lupta_caroiaj_x[j][0], 2);
        dl_data[j+34+10] = misc::from_value(dispozitiv_de_lupta_caroiaj_x[j][1], 2);
    }


    for(int j=0; j< 10; j++)
    {
        dl_data[j+54]    = misc::from_value(dispozitiv_de_lupta_caroiaj_y[j][0], 2);
        dl_data[j+54+10] = misc::from_value(dispozitiv_de_lupta_caroiaj_y[j][1], 2);
    }


    for (int i=0; i < DL_SIZE; i++)
    {
        fprintf(f, "%s", dl_data[i].c_str());
        fprintf(f, "\n");        
    }

    fclose(f);
    chmod("Dispozitiv.dat", S_IREAD);
};

void dispozitiv_de_lupta::dispozitivul_de_lupta_incarca()
{

    if(g_control_lucru.control_lucru_D_L == 0)
    {
        FILE *f ;
        char dispozitiv[80][12] ;

        misc::string file(g_control_lucru.control_lucru_get_dispozitiv_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE );

        if((f = fopen(file.c_str(), "r")) == NULL)
        {
            misc::cout << U("\n\t Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            getchar();
            exit(EXIT_FAILURE);
        }

        //   transformari in sir de caractere

        for(int j=0; j< 74; j++)
        {
            fscanf(f, "%s", &dispozitiv[j][0]);
        }

        fclose(f);
        chmod("Dispozitiv.dat", S_IREAD);

        for(int j=0; j<3; j++)
        {
            dispozitivul_de_lupta_Xpt[j] = (float)atof(dispozitiv[j]);  // 0-2
            dispozitiv_de_lupta_Ypt[j] = (float)atof(dispozitiv[j+3]);   // 3-5
            dispozitiv_de_lupta_hpt[j] = (float)atof(dispozitiv[j+6]);   // 6-8
            dispozitiv_de_lupta_Xpco[j]= (float)atof(dispozitiv[j+9]);  //  9-11
            dispozitiv_de_lupta_Ypco[j]= (float)atof(dispozitiv[j+12]); //  12-14
            dispozitiv_de_lupta_hpco[j]= (float)atof(dispozitiv[j+15]);  //  15-17
            dispozitiv_de_lupta_limita_stanga[j] = (float)atof(dispozitiv[j+18]);    //  18-20
            dispozitiv_de_lupta_limita_dreapta[j] = (float)atof(dispozitiv[j+21]);   //  21-23
        }


        for(int i=0, j=24; j< 26; i++, j++)
        {
            assert(i < 2);
            dispozitiv_de_lupta_Xpo[i] = (float)atof(dispozitiv[j]);    //  24-25
            dispozitiv_de_lupta_Ypo[i] = (float)atof(dispozitiv[j+2]);  //  26-27
            dispozitiv_de_lupta_hpo[i] = (float)atof(dispozitiv[j+4]);  //  28-29
        }

        dispozitiv_de_lupta_distanta_maxima = (float)atof(dispozitiv[30]);   //        30
        dispozitiv_de_lupta_distanta_minima = (float)atof(dispozitiv[31]);   //        31
        dispozitiv_de_lupta_Gdb = (float)atof(dispozitiv[32]);               //        32
        dispozitiv_de_lupta_scara_hartii = (float)atof(dispozitiv[33]);      //        33

        for(int j=0; j< 10; j++)
        {
            dispozitiv_de_lupta_caroiaj_x[j][0] = (float)atof(dispozitiv[34+j]);   //  34-43
            dispozitiv_de_lupta_caroiaj_x[j][1] = (float)atof(dispozitiv[34+j+10]); //  44-53
        }

        for(int j=0; j< 10; j++)
        {
            dispozitiv_de_lupta_caroiaj_y[j][0] = (float)atof(dispozitiv[54+j]);   //  54-63
            dispozitiv_de_lupta_caroiaj_y[j][1] = (float)atof(dispozitiv[54+j+10]); //  64-73
        }

        //  dispozitivul de lupta este incarcat ;
        g_control_lucru.control_lucru_D_L = 1 ;
    }
};

void dispozitiv_de_lupta::dispozitiv_de_lupta_control()
{ 
    while(true)
    {
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  dispozitivul de lupta\n");
        misc::cout << U("\n\t  1  introducere D.L. de la tastatura");
        misc::cout << U("\n\t  2  afisare D.L.");
        misc::cout << U("\n\t  3  intoarcere\n");
        misc::cout << U("\n\t  optiune (1,2 sau 3) = ");

        int g;
        g_control_lucru.control_lucru_getstdin(g);

        if(g == 1)
            introduce_dispozitivul_de_lupta();
        else if(g == 2)
            afiseaza_dispozitivul_de_lupta();
        else if(g == 3)
            return;
    } // while
};

