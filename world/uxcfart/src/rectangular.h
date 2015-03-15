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



#ifndef __rectangular_h__
#define __rectangular_h__



class rectangular
{
public :
    rectangular();
    ~rectangular();

    void rectangular_control();

private :

    void rectangular_primeste_datele();
    void rectangular_registru();
};



#endif//__rectangular_h__
