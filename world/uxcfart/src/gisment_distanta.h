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




#ifndef __gisment_distanta_h__
#define __gisment_distanta_h__


class gisment_distanta
{

public :
    gisment_distanta() ;
    ~gisment_distanta() ;

    void  gisment_distanta_control() ;

private :
    float Dap[3];
    float G[3];
    float To[3];
    float tct[3];
    float ho[3];
    int g[3];

    void primeste_datele();
    void afiseaza_datele();
    void registru();
};



#endif//__gisment_distanta_h__
