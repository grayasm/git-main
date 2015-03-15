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


#ifndef __transport_de_foc_h__
#define __transport_de_foc_h__



#include "citire_distanta.h"
#include "gisment_distanta.h"
#include "observare_conjugata.h"
#include "harta_codificata.h"
#include "foc_de_baraj.h"
#include "caroiaj.h"
#include "rectangular.h"



class transport_de_foc
{
public :
    transport_de_foc();
    ~transport_de_foc();

    void  transport_de_foc_control();

private :
    void indicarea_obiectivelor();
    void primeste_datele();
    void salveaza_datele();
    void incarca_datele();
    void afiseaza_datele();
    void transport_de_foc_date_control();
    void registru();


private:
    citire_distanta         m_citire_distanta;
    gisment_distanta        m_gisment_distanta;    
    observare_conjugata     m_observare_conjugata;    
    harta_codificata        m_harta_codificata;
    foc_de_baraj            m_foc_de_baraj;
    caroiaj                 m_caroiaj;    
    rectangular             m_rectangular;

};


#endif//__transport_de_foc_h__
