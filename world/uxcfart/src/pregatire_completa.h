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



#ifndef __pregatire_completa_h__
#define __pregatire_completa_h__



#include "citire_distanta.h"
#include "gisment_distanta.h"
#include "observare_conjugata.h"
#include "harta_codificata.h"
#include "foc_de_baraj.h"
#include "caroiaj.h"
#include "rectangular.h"




//local
#include "math.hpp"
#include "string.hpp"






class pregatire_completa
{
public :

    pregatire_completa () ;
    ~pregatire_completa () ;
    void pregatire_completa_control () ;

    
private:    
    void primeste_datele() ;
    void salveaza_datele() ;
    void incarca_datele() ;
    void afiseaza_datele() ;
    void indicarea_obiectivelor() ;
    void registru() ;
    
private :
    //altitudinea de intrare in B.M.M.  (sageata)
    float ybul;

    //pres. atmosf si temp. la nivelul statiei meteo
    long Hsma;
    long Tasma;
    long hsma;

    float Taybul;
    float Gw;
    float Vw;

    float Ta[3][4];
    float Hpt[3];
    float Xw[3][4][3];
    float Yw[3][4][3]; //3 baterii, 4 distante, 3 directii ;

    float Gob;
    float Uw;

    float distanta_topo[3][4][3];

    float dDw[3][4][3];
    float dDH[3][4];
    float dDTa[3][4];
    float dDVo[3][4];
    float dDTi[3][4];
    float dDq[3][4];
    float dDvop[3][4];
    float dDcalc[3][4][3];
    float ddcalc[3][4][3];

    float dvoinc;
    float dvo[3];
    float dtinc[3][4];
    float dXw[3][4];
    float dXH[3][4];
    float dXTa[3][4];
    float dXVo[3][4];
    float dXTi[3][4];
    float dXq[3][4];
    float dYw[3][4];
    float derivatie[3][4];


    void sageata(int *, float *) ;
    float Taerybul(int *n) ;
    float Gwy(int *n ) ;
    float Vwy(int *n) ;
    float SB() ;
    //nr_bat, nr_dist, nr_dir ;
    void calculeaza_conditiile_meteo(int *, int *, int *) ;
    void calculeaza_corectii_calculate() ;
    void afiseaza_corectii_calculate() ;

    misc::string sDGdTrag[7];
    float DdTrag[4];
    float GdTrag[3];     


private:
    citire_distanta         m_citire_distanta;
    gisment_distanta        m_gisment_distanta;    
    observare_conjugata     m_observare_conjugata;    
    harta_codificata        m_harta_codificata;
    foc_de_baraj            m_foc_de_baraj;
    caroiaj                 m_caroiaj;    
    rectangular             m_rectangular;


};



#endif//__pregatire_completa_h__
