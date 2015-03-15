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
#include <stdio.h>
#include <stdlib.h>

//c++


//misc
#include "stream.hpp"


//program
#include "transport_de_foc.h"
#include "control_lucru.h"
#include "dispozitiv_de_lupta.h"






transport_de_foc::transport_de_foc()
{
};

transport_de_foc::~transport_de_foc()
{
};

void transport_de_foc::transport_de_foc_date_control()
{
    while(true)
    {
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  transport de foc\n");
        misc::cout << U("\n\t  1  introducerea datelor pe reperul de tragere");
        misc::cout << U("\n\t  2  afisarea datelor pe reperul de tragere");
        misc::cout << U("\n\t  3  intoarcere\n");
        misc::cout << U("\n\t  optiune (1,2 sau 3) = ");

        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);

        if(g == 1)
        {
            primeste_datele();
            salveaza_datele();
        }
        else if(g == 2)
        {
            afiseaza_datele();
        }
        else if(g == 3)
        {
            return;
        }
    } // while
};

void  transport_de_foc::transport_de_foc_control()
{

    g_control_lucru.control_lucru_T_F = 1 ;  //  activeaza transportul de foc
    g_control_lucru.control_lucru_P_C = 0 ;  //  dezactiveaza pregatirea completa ;

    
    while(true)
    {
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  transport de foc\n");
        misc::cout << U("\n\t  1 -> dispozitivul de lupta al bateriilor (meniu)");
        misc::cout << U("\n\t  2 -> elementele pe reperele de tragere (meniu)");
        misc::cout << U("\n\t  3 -> indicarea obiectivelor (meniu)");
        misc::cout << U("\n\t  4 -> intoarcere\n");
        misc::cout << U("\n\t  optiune (1,2...4) = ");


        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);


        if(g == 1)
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_control();
        else if(g == 2)
            transport_de_foc_date_control();
        else if(g == 3)
            indicarea_obiectivelor();
        else if(g == 4)
            return;

    } // while
};

void transport_de_foc::indicarea_obiectivelor()
{

    if(g_control_lucru.control_lucru_D_L == 0)
    {
        g_dispozitiv_de_lupta.dispozitivul_de_lupta_incarca();
    }

    if(g_control_lucru.control_lucru_date_T_F == 0)
    {
        incarca_datele();            
    }

    if(g_control_lucru.control_lucru_stare_date_T_F == 1)
    {
        registru();
    }

    
    while(true)
    {
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  indicarea obiectivelor\n");
        misc::cout << U("\n\t  1 -> citire si distanta");
        misc::cout << U("\n\t  2 -> gisment si distanta");
        misc::cout << U("\n\t  3 -> din punctele observarii conjugate");
        misc::cout << U("\n\t  4 -> cu harta codificata");
        misc::cout << U("\n\t  5 -> foc de baraj");
        misc::cout << U("\n\t  6 -> cu caroiajul");
        misc::cout << U("\n\t  7 -> prin coordonate rectangulare");
        misc::cout << U("\n\t  8 -> intoarcere\n");
        misc::cout << U("\n\t  optiune (1,2,...,8) = ");


        int g = 0;
        g_control_lucru.control_lucru_getstdin(g);


        if(g == 1)
            m_citire_distanta.citire_distanta_control ();
        else if(g == 2)
            m_gisment_distanta.gisment_distanta_control ();
        else if(g == 3)
            m_observare_conjugata.observare_conjugata_control ();
        else if(g == 4)
            m_harta_codificata.harta_codificata_control ();
        else if(g == 5)
            m_foc_de_baraj.foc_de_baraj_control ();
        else if(g == 6)
            m_caroiaj.caroiaj_control ();
        else if(g == 7)
            m_rectangular.rectangular_control ();
        else if(g == 8)
            return;
    } // while

};


void transport_de_foc::primeste_datele()
{
    char cInc[3][10];
    char cDtRT[3][10];
    char cMdtRT[3][10];
    char cK[3][5];
    char cddirrRT[3][10];
    char g[3] ;

    for(int j=0; j < 3; ++j)
    {
        while(true)
        {
            clrscr();
            misc::cout << U("\n\n");
            misc::cout << U("\n\t  introduceti datele pe reperul de tragere");
            misc::cout << U("\n\t  bateria ") << j+1 << U(" artilerie");
            misc::cout << U("\n\t  incarcatura de tragere (0,1,2,3,4 sau 5) = ");            

            g_control_lucru.control_lucru_getstdin(cInc[j], 10);

            misc::cout << U("\n\t  distanta topografica la R.T. = ");
            g_control_lucru.control_lucru_getstdin(cDtRT[j], 10);

            misc::cout << U("\n\t  modificarea de deriva topo. la R.T. = ");
            g_control_lucru.control_lucru_getstdin(cMdtRT[j], 10);

            misc::cout << U("\n\t  coeficient de tragere (K) = ");
            g_control_lucru.control_lucru_getstdin(cK[j], 5);

            misc::cout << U("\n\t  corectie de reglaj in directie = ");
            g_control_lucru.control_lucru_getstdin(cddirrRT[j], 10);   

            misc::cout << U("\n\t  datele introduse sunt corecte ? (d/n) = ");
            
            g_control_lucru.control_lucru_getstdin(g, 3);            

            if(g[0] == 'd' || g[0] == 'D')
                break;
        } // while
    } // for


    for(int i=0; i < 3; ++i)
    {
        g_conditii_balistice_transport_de_foc.incarcatura_T_F[i] = (float)atof(cInc[i]);
        g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[i]  = (float)atof(cDtRT[i]);
        g_conditii_balistice_transport_de_foc.modificare_deriva_topografica_reper_tragere[i] = (float)atof(cMdtRT[i]);
        g_conditii_balistice_transport_de_foc.coeficient_tragere[i]  =  (float)atof(cK[i]);
        g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[i] =  (float)atof(cddirrRT[i]);
    }

    g_control_lucru.control_lucru_date_T_F = 1 ;

    //indica functiilor <<registru>> PC si TF
    //sa scrie noile date in fisierele de lucru ;

    g_control_lucru.control_lucru_stare_date_T_F = 1 ;
    
};

void transport_de_foc::salveaza_datele()
{

    FILE *f ;
    const int TF_SIZE = 15;
    misc::string tf_date[TF_SIZE];

    for(int j=0; j < 3; ++j)
    {
        tf_date[j]    = misc::from_value(g_conditii_balistice_transport_de_foc.incarcatura_T_F[j], 2);
        tf_date[j+3]  = misc::from_value(g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[j], 2);
        tf_date[j+6]  = misc::from_value(g_conditii_balistice_transport_de_foc.modificare_deriva_topografica_reper_tragere[j], 2);
        tf_date[j+9]  = misc::from_value(g_conditii_balistice_transport_de_foc.coeficient_tragere[j], 2);
        tf_date[j+12] = misc::from_value(g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[j], 2);
    }

    misc::string file(g_control_lucru.control_lucru_get_tf_date_path());

    chmod(file.c_str(), S_IREAD|S_IWRITE );

    if((f = fopen(file.c_str(), "w+")) == NULL)
    {
        clrscr();
        misc::cout << U("\n\n");
        
        misc::cout << U("\n\t  eroare la deschiderea fisierului: ") << file.c_str();
        misc::cout << U("\n");
        perror("");
        getchar();
        exit(EXIT_FAILURE);
    }


    for(int j=0; j < TF_SIZE; j++)
    {
        fprintf(f, "%s\n", tf_date[j].c_str());        
    }


    chmod(file.c_str(), S_IREAD);

    fclose(f);
};

void transport_de_foc::incarca_datele()
{
    if(g_control_lucru.control_lucru_date_T_F == 0)
    {
        FILE *f ;
        char dispozitiv[20][10] ;
        misc::string file(g_control_lucru.control_lucru_get_tf_date_path());
        chmod(file.c_str(), S_IREAD);

        if((f = fopen(file.c_str(), "r")) == NULL)
        {
            misc::cout << U("\n\t  eroare la deschiderea fisierului: ") << file.c_str();
            misc::cout << U("\n");
            perror("");            
            getchar();
            exit(EXIT_FAILURE);
        }

        for(int j=0; j< 15; j++)
        {
            fscanf(f, "%s", &dispozitiv[j][0]);
        }

        fclose(f);

        for(int j=0; j<3; j++)
        {
            g_conditii_balistice_transport_de_foc.incarcatura_T_F[j] = (float)atof(dispozitiv[j]);                                 // 0-2
            g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[j] = (float)atof(dispozitiv[j+3]);            // 3-5
            g_conditii_balistice_transport_de_foc.modificare_deriva_topografica_reper_tragere[j] = (float)atof(dispozitiv[j+6]);   // 6-8
            g_conditii_balistice_transport_de_foc.coeficient_tragere[j] = (float)atof(dispozitiv[j+9]);                            // 9-11
            g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[j] = (float)atof(dispozitiv[j+12]);                     // 12-14
        }

        g_control_lucru.control_lucru_date_T_F  = 1 ;
    }
};

void transport_de_foc::afiseaza_datele()
{

    if(g_control_lucru.control_lucru_date_T_F == 0)
    {
        incarca_datele();
    }



    printf("\n");
    printf("\n                    DATELE PE REPERELE DE TRAGERE   ");
    printf("\n    ------------------------------------------------------------------------");

    for(int j=0; j < 3; ++j)
    {
        printf("\n\n                        BATERIA %d ARTILERIE", j+1);
        printf("\n          Incarcatura de tragere            =  %.0f", g_conditii_balistice_transport_de_foc.incarcatura_T_F[j] );
        printf("\n          Distanta topografica la R.T.      =  %.2f", g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[j] );
        printf("\n          Modificare de deriva topo. la R.T.=  %.2f", g_conditii_balistice_transport_de_foc.modificare_deriva_topografica_reper_tragere[j]);
        printf("\n          Coeficient de tragere (K)         =  %.2f", g_conditii_balistice_transport_de_foc.coeficient_tragere[j]);
        printf("\n          Corectie de reglaj in directie    =  %.2f", g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[j]);
    }


    printf("\n\n    ------------------------------------------------------------------------");
    getchar();

};


void transport_de_foc::registru()
{

    FILE *f ;

    if(g_control_lucru.control_lucru_fisier_cumulat_T_F_I_O == 1 && g_control_lucru.control_lucru_T_F == 1)
    {
        misc::string file(g_control_lucru.control_lucru_get_tf_test_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE);

        if((f = fopen(file.c_str(), "a")) == NULL)
        {
            printf("\n      Eroare la deschiderea fisierului TF_Test.doc : ");
            perror("");
            printf("\n Programul va fi terminat");
            getchar();
            exit(EXIT_FAILURE);
        }

        g_dispozitiv_de_lupta.dispozitivul_de_lupta_incarca();


        fprintf(f, "%s\n", "    ________________________________________________________________________");
        fprintf(f, "%s\n", "                    Dispozitivul de lupta al bateriilor");

        for(int j=0; j < 3; ++j)
        {
            fprintf(f, "           Bateria %d Artilerie\n", j+1);
            fprintf(f, "   Xpt = %.2f", g_dispozitiv_de_lupta.dispozitivul_de_lupta_Xpt[j]);
            fprintf(f, "   Ypt = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypt[j]);
            fprintf(f, "   hpt = %.2f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[j]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");

        for(int j=0; j < 3; ++j)
        {
            fprintf(f, "            Bateria %d Artilerie\n", j+1);
            fprintf(f, "   Xpco = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpco[j]);
            fprintf(f, "   Ypco = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypco[j]);
            fprintf(f, "   hpco = %.2f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpco[j]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");

        for(int j=0; j < 2; ++j)
        {
            if(j ==0)
            {
                fprintf(f, "            Punctul de observare \n");
            }
            else
            {
                fprintf(f, "            Punctul de observare-lateral \n");
            }

            fprintf(f, "    X  = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[j]);
            fprintf(f, "   Y = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[j]);
            fprintf(f, "   h = %.2f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[j]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");
        fprintf(f, "    g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb = %.0f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);

        if(g_dispozitiv_de_lupta.dispozitiv_de_lupta_scara_hartii == 1)
        {
            fprintf(f, "   Scara hartii  1:25.000\n");
        }
        else if(g_dispozitiv_de_lupta.dispozitiv_de_lupta_scara_hartii == 2)
        {
            fprintf(f, "   Scara hartii  1:50.000\n");
        }
        else
        {
            fprintf(f, "   Nu se potriveste Scara hartii\n");
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");

        for(int j=0; j < 3; ++j)
        {
            fprintf(f, "    Limitele in directie pentru Bateria %d Artilerie\n", j+1);
            fprintf(f, "    l. stg.  = %.0f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_limita_stanga[j]);
            fprintf(f, "   l. dr.   = %.0f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_limita_dreapta[j]);

        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");
        fprintf(f, "    Limitele in bataie \n");
        fprintf(f, "    D. min. = %.0f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_distanta_minima);
        fprintf(f, "   D. max. = %.0f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_distanta_maxima);
        fprintf(f, "%s\n", "    ________________________________________________________________________");


        fprintf(f, "    Codificarea hartii pentru 10 carouri pe axa X\n");

        for(int j=0; j < 10; j+=2)
        {
            fprintf(f, "    Axa X = %.0f    cod.= %.0f  Axa X = %.0f    cod.= %.0f\n",
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j][1],
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j+1][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j+1][1]);
        }

        fprintf(f, "    Codificarea hartii pentru 10 carouri pe axa Y\n");

        for(int j=0; j<10; j+=2)
        {
            fprintf(f, "    Axa Y = %.0f    cod.= %.0f  Axa Y = %.0f    cod.= %.0f\n",
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j][1],
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j+1][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j+1][1]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");


        if(g_control_lucru.control_lucru_date_T_F == 0)
        {
            incarca_datele();
        }

        fprintf(f, "                      Datele pe reperele de tragere   ");
        fprintf(f, "%s\n", "    ________________________________________________________________________");


        for(int j=0; j < 3; ++j)
        {

            fprintf(f, "\n                        BATERIA %d ARTILERIE", j+1);

            if(g_conditii_balistice_transport_de_foc.incarcatura_T_F[j] == 0)
            {
                fprintf(f, "\n          Incarcatura Completa" );
            }
            else
            {
                fprintf(f, "\n          Incarcatura  a \"%.0f", g_conditii_balistice_transport_de_foc.incarcatura_T_F[j] );
            }

            fprintf(f, "\n          Distanta topografica la R.T.      =  %.2f", g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[j] );
            fprintf(f, "\n          Modificare de deriva topo. la R.T.=  %.2f", g_conditii_balistice_transport_de_foc.modificare_deriva_topografica_reper_tragere[j]);
            fprintf(f, "\n          Coeficient de tragere (K)         =  %.2f", g_conditii_balistice_transport_de_foc.coeficient_tragere[j]);
            fprintf(f, "\n          Corectie de reglaj in directie    =  %.2f", g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[j]);

        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");

        fclose(f);

        chmod(file.c_str(), S_IREAD);

        g_control_lucru.control_lucru_stare_date_T_F = 0 ;
    }
};
