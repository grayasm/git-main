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



#ifndef __structura_elementelor_h__
#define __structura_elementelor_h__


#include "dispozitiv_de_lupta.h"
#include "obiectiv.h"
#include "artutil.h"



class structura_elementelor
{

public :

    structura_elementelor();
    ~structura_elementelor();
 

private:

    void structura_elementelor_coeficienti_si_date();     //  date si coeficienti de tragere pe obiective
    void structura_elementelor_date_initiale_tragere();  //  I, Niv, Md, f, Con, II dir, Ritm trg ;
    int structura_elementelor_calculeaza_corectii(int );    //  corectii calculate  ;
    int  structura__elementelor_corectii_de_reglaj(int);   //  calculeaza corectiile de reglaj ;
    void afiseaza_date_initiale_tragere()  ;

public:
    void structura_elementelor_control();


};



extern structura_elementelor g_structura_elementelor;

#endif//__structura_elementelor_h__
