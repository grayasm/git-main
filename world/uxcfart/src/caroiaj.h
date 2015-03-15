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



#ifndef __caroiaj_h__
#define __caroiaj_h__



class caroiaj
{
public :
    caroiaj();
    ~caroiaj();

    void caroiaj_control();

private :
    float colt_carou_x[3];
    float colt_carou_y[3];
    float ho[3];
    float unghi[3];

    //  coordonate colt carou ;
    float nx[3];
    float ny[3];


    void caroiaj_introduce_obiectiv();
    void caroiaj_calculeaza();
    void caroiaj_afiseaza();
    void registru();
} ;



#endif // __caroiaj_h__
