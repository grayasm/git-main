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
#include "conducerea_focului.h"
#include "control_lucru.h"



conducerea_focului::conducerea_focului()
{
};

conducerea_focului::~conducerea_focului()
{
};

void conducerea_focului::conducerea_focului_control()
{
    while(true)
    {
        clrscr();
        misc::cout << U("\n");
        misc::cout << U("\n\n\t1 -> configurare lucru");
        misc::cout << U("\n\t     optiunea de configurare permite salvarea");
        misc::cout << U("\n\t     datelor calculate la obiective");        
        misc::cout << U("\n\n\t2 -> pregatire completa");
        misc::cout << U("\n\n\t3 -> transport de foc");        
        misc::cout << U("\n\n\t4 -> iesire din program");
        misc::cout << U("\n");
        misc::cout << U("\n\t     optiune (1,2,3 sau 4) = ");

        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);

        if(g == 1)
            g_control_lucru.control_lucru_control();        
        else if(g == 2)
            conducerea_focului_pregatire_completa();
        else if(g == 3)
            conducerea_focului_transport_de_foc();
        else if(g == 4)
            exit(EXIT_SUCCESS);
        
    } // while
};

void conducerea_focului::conducerea_focului_pregatire_completa()
{
   m_pregatire_completa.pregatire_completa_control () ;
};

void   conducerea_focului::conducerea_focului_transport_de_foc()
{
    m_transport_de_foc.transport_de_foc_control() ;
};
