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



#ifndef __harta_codificata_h__
#define __harta_codificata_h__



class harta_codificata
{

public :
    harta_codificata();
    ~harta_codificata();

    void harta_codificata_control();

private:
    void primeste_datele();
    void afiseaza_datele();
    void registru();
        
private :
    float ncaroux[3];
    float ncarouy[3];
    float nx[3];
    float ny[3];
    float ho[3];
};


#endif//__harta_codificata_h__
