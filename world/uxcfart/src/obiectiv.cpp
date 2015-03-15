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
#include "unistd.hpp"
#include "string.hpp"
#include "stream.hpp"

//program
#include "obiectiv.h"


/* global variable */
obiectiv g_obiectiv;


obiectiv::obiectiv()
{
};

obiectiv::~obiectiv()
{
};

void obiectiv::obiectiv_primeste_bateria()
{
    char m_cNrBt[3][20] ;


    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  indicati cu (d/n) bateria care trage in sector/obiectiv");


    for(int i=0; i < 3 ; ++i)
    {        
        misc::cout << U("\n\t  bateria ") << i+1 << U(" trage ? (d/n) = ");

        getstdin2(m_cNrBt[i], 20);        

        if(m_cNrBt[i][0] == 'd' || m_cNrBt[i][0] == 'D')
            obiectiv_btno[i] = i+1 ;
        else
            obiectiv_btno[i] = 0;
    }
};

void obiectiv::obiectiv_primeste_datele(int bt)
{
    char g[3] ;
    while(true)
    {
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Indicarea obiectivului pt Bt ") << bt+1 << U(" art");
        misc::cout << U("\n\t  Nr. obiectiv = ");        
        getstdin2(obiectiv_nr_obiectiv[bt], 5);
        
        misc::cout << U("\n\t  Front = ");
        getstdin2(obiectiv_front[bt]);

        misc::cout << U("\n\t  Adancime = ");
        getstdin2(obiectiv_adancime[bt]);

        misc::cout << U("\n\t  Consum/Bt = ");
        getstdin2(obiectiv_norma_consum[bt]);

        misc::cout << U("\n\t  Nr directii = ");
        getstdin2(obiectiv_nr_directii[bt]);

        misc::cout << U("\n\t  Ciocan de foc (min) = ");
        getstdin2(obiectiv_timp_ciocan_de_foc[bt]);

        misc::cout << U("\n\t  Salvati (d) sau reintroduceti datele ? = ");        
        getstdin2(g, 3);

        if(g[0] == 'd' || g[0] == 'D')
            break;
    } // while
};



void getstdin2(char* buff, unsigned int size)
{
    std::cin.getline(buff, size);
    if( std::cin.fail() )
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
    }
};


void getstdin2(float& val)
{
    char buf[30]="";
    getstdin2(buf, 30);
    val = (float)atof(buf);
};

void getstdin2(int& val)
{
    char buf[30]="";
    getstdin2(buf, 30);
    val = atoi(buf);
};

void getstdin2(long& val)
{
    char buf[30]="";
    getstdin2(buf, 30);
    val = atol(buf);
};