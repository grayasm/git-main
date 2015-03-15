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
#include "filename.hpp"
#include "unistd.hpp"
#include "stream.hpp"



//program
#include "conducerea_focului.h"
#include "control_lucru.h"



void copyright()
{

    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\n\t  Conducerea focului artileriei");
    misc::cout << U("\n\n\t  Copyright 2002 by Mihai Vasilian");
    misc::cout << U("\n\n\t  Pt erori scrieti la: grayasm@gmail.com");
    misc::cout << U("\n\n\t  <RET> intrare in program");

    getchar();
    clrscr();
};

int main(int argc, char *argv[])
{
    copyright() ;
    misc::filename pwd(argv[0]);       
    g_control_lucru.control_lucru_PWD = pwd.get_directory();


    conducerea_focului obiect ;    
    obiect.conducerea_focului_control();

    return EXIT_SUCCESS ;
};
