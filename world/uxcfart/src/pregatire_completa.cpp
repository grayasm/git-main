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
#include "pregatire_completa.h"
#include "artutil.h"
#include "control_lucru.h"
#include "buletin_meteo.h"
#include "dispozitiv_de_lupta.h"
#include "conditii_meteo_balistice.h"
#include "tabla_tragere.h"
#include "obiectiv.h"





extern float sb[13][11];
extern float xw[16][9];
extern float yw[16][9];
extern char grupa[16][20];






pregatire_completa::pregatire_completa()
{
};

pregatire_completa::~pregatire_completa()
{
};


void pregatire_completa::pregatire_completa_control()
{

    g_control_lucru.control_lucru_P_C = 1 ;  //  activeaza pregatirea completa ;
    g_control_lucru.control_lucru_T_F = 0 ;  //   dezactiveaza transportul de foc    

    while(true)
    {
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  pregatire completa\n");
        misc::cout << U("\n\t  1 -> introduceti distantele si gismentele de trg.");
        misc::cout << U("\n\t  2 -> afisarea distantelor si gismentelor de trg.");
        misc::cout << U("\n\t  3 -> buletin meteo mediu (meniu separat)");
        misc::cout << U("\n\t  4 -> conditii meteo si balistice (meniu separat)");
        misc::cout << U("\n\t  5 -> dispozitivul de lupta al bateriilor (meniu)");
        misc::cout << U("\n\t  6 -> afisare corectii calculate");
        misc::cout << U("\n\t  7 -> indicare obiectivelor");
        misc::cout << U("\n\t  8 -> intoarcere\n");
        misc::cout << U("\n\t  optiune (1,2,...8) = ");


        int g;
        g_control_lucru.control_lucru_getstdin(g);


        if(g == 1)
            primeste_datele ();
        else if(g == 2)
            afiseaza_datele ();
        else if(g == 3)
            g_buletin_meteo.buletin_meteo_control();
        else if(g == 4)
            g_conditii_meteo_balistice.conditii_meteo_balistice_control ();
        else if(g == 5)
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_control();        
        else if(g == 6)
        {
            calculeaza_corectii_calculate ();
            afiseaza_corectii_calculate ();
        }
        else if(g == 7)
            indicarea_obiectivelor();
        else if(g == 8)
            return;
        
    } // while
};


void pregatire_completa::primeste_datele()
{
    

    float var[7];
        
    //
    clrscr();

    misc::cout << U("\n\t  Introduceti distantele de tragere");
    misc::cout << U("\n\t  Dtrag 1 = ");
    g_control_lucru.control_lucru_getstdin(var[0]);
    DdTrag[0] = var[0];

    misc::cout << U("\n\t  Dtrag 2 = ");    
    g_control_lucru.control_lucru_getstdin(var[1]);
    DdTrag[1] = var[1];

    misc::cout << U("\n\t  Dtrag 3 = ");
    g_control_lucru.control_lucru_getstdin(var[2]);
    DdTrag[2] = var[2];

    
    misc::cout << U("\n\t  Dtrag 4 = ");
    g_control_lucru.control_lucru_getstdin(var[3]);
    DdTrag[3] = var[3];

    

    misc::cout << U("\n\t  Introduceti gismentele de tragere");    
    misc::cout << U("\n\t  Gtrag 1 = ");
    g_control_lucru.control_lucru_getstdin(var[4]);
    GdTrag[0] = var[4];

    misc::cout << U("\n\t  Gtrag 2 = ");
    g_control_lucru.control_lucru_getstdin(var[5]);
    GdTrag[1] = var[5];

    
    misc::cout << U("\n\t  Gtrag 3 = ");
    g_control_lucru.control_lucru_getstdin(var[6]);
    GdTrag[2] = var[6];
        

    for(int z=0 ; z < 4 ; ++z)
    {
        if(DdTrag[z] < 0 || DdTrag[z] > 17230)
        {
            misc::cout << U("\n\t  distanta de tragere ") << z+1 << U(" = ") << std::fixed
                    << std::setprecision(2) << DdTrag[z] << U(" m este eronata."); 
            misc::cout << U("\n\t  Programul va fi terminat");
            getchar();
            exit(EXIT_FAILURE);
        }
    }
    

    for(int z=0; z < 3; ++z)
    {
        if(GdTrag[z] < 0 && GdTrag[z] > 6000)
        {
            misc::cout << U("\n\t  Gdt ") << z+1 << U(" = ") << GdTrag[z] << U(" incorect.");            
            misc::cout << U("\n\t  Programul va fi terminat");
            getchar();
            exit(EXIT_FAILURE);
        }
    }

    g_control_lucru.control_lucru_D_G = 1 ; //distantele si gismentele sunt incarcate in  program ;
    g_control_lucru.control_lucru_C_C = 0 ; //s-au introd. ale distante si gismente ?

    //  corectiile calculate trebuie firesc recalculate ;

    for(int i=0; i < 7; ++i)
    {
        sDGdTrag[i] = misc::from_value(var[i], 2);
    }

    salveaza_datele ();
};

void pregatire_completa::salveaza_datele()
{
    misc::string file(g_control_lucru.control_lucru_get_dgt_path());

    chmod(file.c_str(), S_IREAD|S_IWRITE);

    FILE *fisier ;

    if((fisier = fopen(file.c_str(), "w+")) == NULL)
    {
        misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") <<  file.c_str();
        perror("");
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }

    for(int i=0; i < 7; ++i)
    {
        fprintf(fisier, "%s", sDGdTrag[i].c_str());
        fprintf(fisier, "\n");
    }

    fclose(fisier);
    chmod(file.c_str(), S_IREAD);
};

void pregatire_completa::incarca_datele()
{
    if(g_control_lucru.control_lucru_D_G == 0)
    {
        misc::string file(g_control_lucru.control_lucru_get_dgt_path());

        FILE *fisier;

        if((fisier = fopen(file.c_str(), "r")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            misc::cout << U("\n\t  Programul va fi terminat");
            getchar();
            exit(EXIT_FAILURE);
        }

        for (int i=0; i<7; i++ )
        {
            char buf[100];
            sDGdTrag[i] = fgets(buf, 100, fisier);
        }

        fclose(fisier);

        for(int j=0; j<4; j++)
        {
            misc::to_value(sDGdTrag[j], DdTrag[j]);
        }

        for(int i=0, j=4; j<7; j++, i++)
        {
            misc::to_value(sDGdTrag[j], GdTrag[i]);
        }

        g_control_lucru.control_lucru_D_G = 1 ;
    }
};

void pregatire_completa::afiseaza_datele()
{

    if(g_control_lucru.control_lucru_D_G == 0)
    {
        incarca_datele();
    }


    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  Distante de tragere");
    std::cout.precision(2);
    misc::cout << U("\n\t  Distanta 1 = ") << std::fixed << DdTrag[0] ;
    misc::cout << U("\n\t  Distanta 2 = ") << std::fixed << DdTrag[1] ;
    misc::cout << U("\n\t  Distanta 3 = ") << std::fixed << DdTrag[2] ;
    misc::cout << U("\n\t  Distanta 4 = ") << std::fixed << DdTrag[3] ;
    misc::cout << U("\n");
    misc::cout << U("\n\t  Gismente de tragere");
    misc::cout << U("\n\t  Gisment  1 = ") << std::fixed << GdTrag[0] ;
    misc::cout << U("\n\t  Gisment  2 = ") << std::fixed << GdTrag[1] ;
    misc::cout << U("\n\t  Gisment  3 = ") << std::fixed << GdTrag[2] ;
    
    getchar();
};

void pregatire_completa::indicarea_obiectivelor()
{
    if(g_control_lucru.control_lucru_C_C == 0)
    {
        calculeaza_corectii_calculate();
    }

    if(g_control_lucru.control_lucru_D_L == 0)
    {
        g_dispozitiv_de_lupta.dispozitivul_de_lupta_incarca();
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


void pregatire_completa::registru()
{
    FILE *f ;

    if(g_control_lucru.control_lucru_fisier_cumulat_P_C_I_O == 1 && g_control_lucru.control_lucru_P_C == 1)
    {
        misc::string file(g_control_lucru.control_lucru_get_pc_test_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE);

        if((f = fopen(file.c_str(), "a")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            getchar();
            exit(EXIT_FAILURE);
        }

        g_dispozitiv_de_lupta.dispozitivul_de_lupta_incarca();


        fprintf(f, "%s\n", "    ________________________________________________________________________");
        fprintf(f, "%s\n", "                    Dispozitivul de lupta al bateriilor");

        for(int j=0; j < 3; ++j)
        {
            fprintf(f, "           Bateria %d Artilerie\n", j+1);
            fprintf(f, "    Xpt = %.2f", g_dispozitiv_de_lupta.dispozitivul_de_lupta_Xpt[j]);
            fprintf(f, "   Ypt = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypt[j]);
            fprintf(f, "   hpt = %.2f\n", g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[j]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");

        for(int j=0; j < 3; ++j)
        {
            fprintf(f, "            Bateria %d Artilerie\n", j+1);
            fprintf(f, "    Xpco = %.2f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpco[j]);
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
        fprintf(f, "    Gdb = %.0f", g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);

        if(g_dispozitiv_de_lupta.dispozitiv_de_lupta_scara_hartii == 1)
        {
            fprintf(f, "   Scara hartii  1:25.000\n");
        }
        else if(g_dispozitiv_de_lupta.dispozitiv_de_lupta_scara_hartii == 2)
        {
            fprintf(f, "   Scara hartii  1:50.000\n")  ;
        }
        else
        {
            fprintf(f, "   Nu se potriveste Scara hartii\n")  ;
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
            fprintf(f, "    Axa  X = %.0f    cod.= %.0f  Axa  X = %.0f    cod.= %.0f\n",
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j][1],
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j+1][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_x[j+1][1]);
        }

        fprintf(f, "    Codificarea hartii pentru 10 carouri pe axa Y\n");

        for(int j=0; j < 10; j+=2)
        {
            fprintf(f, "    Axa  Y = %.0f    cod.= %.0f  Axa  Y = %.0f    cod.= %.0f\n",
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j][1],
                    g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j+1][0], g_dispozitiv_de_lupta.dispozitiv_de_lupta_caroiaj_y[j+1][1]);
        }

        fprintf(f, "%s\n", "    ________________________________________________________________________");
        fprintf(f, "%s\n", "                    Date necesare executarii pregatirii complete");
        fprintf(f,         "    distante  %.0f, %.0f, %.0f, %.0f\n",
                (DdTrag[0]*0.001), (DdTrag[1]*0.001),
                (DdTrag[2]*0.001), (DdTrag[3]*0.001));

        fprintf(f,         "    gismente  %.0f, %.0f, %.0f\n\n", GdTrag[0], GdTrag[1], GdTrag[2]);
        fprintf(f,         "    B.M.M. : ");


        for(int i=0, k=0, j=-1 ; i < 300; i++, k++, j++)
        {
            if(k == 0)
            {
                fprintf(f, " - %s ", g_buletin_meteo.buletin_meteo_ch[i]);

                if(atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
                {
                    i = 400 ;
                }
                else if(j == 4)
                {
                    j = 0 ;
                    fprintf(f, "\n");
                    fprintf(f, "%s", "        ");
                }
            }
            else if(k > 0 && k < 4)
            {
                fprintf(f, " - %s - %s", grupa[k], g_buletin_meteo.buletin_meteo_ch[i]);

                if(atol(grupa[k]) == 3030 || atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
                {
                    i = 400 ;
                }
                else if(j == 4)
                {
                    j = 0 ;
                    fprintf(f, "\n");
                    fprintf(f, "%s", "        ");
                }
            }
            else
            {
                fprintf(f, " - %s", g_buletin_meteo.buletin_meteo_ch[i++]);

                if(atol(g_buletin_meteo.buletin_meteo_ch[i-1]) == 3030)
                {
                    i = 400 ;
                    continue ;
                }

                fprintf(f, " - %s", g_buletin_meteo.buletin_meteo_ch[i]);

                if(j == 4)
                {
                    j = 0 ;
                    fprintf(f, "\n");
                    fprintf(f, "%s", "        ");
                }
            }

            if(atol(g_buletin_meteo.buletin_meteo_ch[i]) == 3030)
            {
                i = 400 ;
                continue ;
            }
        }

        for(int i=0; i < 3; ++i)
        {

            fprintf(f, "%s\n", "    ________________________________________________________________________");
            fprintf(f, "    Conditii meteo si balistice \n");
            fprintf(f, "    Bateria %d ARTILERIE\n", i+1); ;
            fprintf(f, "    Ob. cal. 152 mm md.'81 ");
            fprintf(f, "    Pr. OF-540");

            if(g_conditii_meteo_balistice.conditii_meteo_balistice_voppr[i][0] == 'D')
            {
                fprintf(f, " - vopsit\n");
            }
            else
            {
                fprintf(f, " - nevopsit\n");
            }

            if(g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] == 0)
            {
                fprintf(f, "    Incarcatura \"C\"\n");
            }
            else
            {
                fprintf(f, "    Incarcatura  \"%.0f\"-a\n", g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] );
            }

            fprintf(f, "    vop = %.2f %%", g_conditii_meteo_balistice.conditii_meteo_balistice_vop[i]);
            fprintf(f, "    voinc = %.0f m/s\n" , g_conditii_meteo_balistice.conditii_meteo_balistice_voinc[i]);
            fprintf(f, "    Tinc = %.2f oC", g_conditii_meteo_balistice.conditii_meteo_balistice_tinc[i] );
            fprintf(f, "    q    = %.0f\n", g_conditii_meteo_balistice.conditii_meteo_balistice_q[i]);

        }

        fclose(f);
        chmod(file.c_str(), S_IREAD);

    }

    if(g_control_lucru.control_lucru_fisier_cumulat_P_CRez_C_O_D_Coef  == 1 && g_control_lucru.control_lucru_P_C == 1)
    {

        misc::string file(g_control_lucru.control_lucru_get_pc_test_rezolvare_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE);

        if((f = fopen(file.c_str(), "a")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            exit(EXIT_FAILURE);
        }


        for(int i=0; i < 3; i++)
        {
            for(int j=0; j < 4; j++)
            {
                for(int k=0; k < 3; k++)
                {

                    fprintf(f, "%s\n", "    ________________________________________________________________________");
                    fprintf(f, "\n    CORECTII CALCULATE BATERIA %d ARTILERIE", i+1);

                    fprintf(f, "\n            DISTANTA %d (%.2f)  GISMENT %d (%.0f)",j+1, DdTrag[j], k+1, GdTrag[k]);
                    if (g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] == 0)
                    {
                        fprintf(f, "\n        Distanta   = %.2f           Incarcatura \"C\"", DdTrag[j] );
                    }
                    else
                    {
                        fprintf(f, "\n        Distanta   = %.2f           Incarcatura a \"%.0f\" -a", DdTrag[j], g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] );
                    }

                    if(k ==0)
                    {
                        fprintf(f, "\n        dDw  =  Xw   *  dXw = rezultat ;");
                    }

                    fprintf(f, "\n        dDw  = (%.2f)*(%.2f) = %.2f m", Xw[i][j][k], dXw[i][j],dDw[i][j][k]);
                    fprintf(f, "\n        dDH  = (%.2f)*(%.2f) = %.2f m", Hpt[i], dXH[i][j], dDH[i][j]);
                    fprintf(f, "\n        dDTa = (%.2f)*(%.2f) = %.2f m",Ta[i][j], dXTa[i][j], dDTa[i][j] );
                    fprintf(f, "\n        dDVo = (%.2f)*(%.2f) = %.2f m",dvo[i] , dXVo[i][j], dDVo[i][j] );
                    fprintf(f, "\n        dDTi = (%.2f)*(%.2f) = %.2f m", dtinc[i][j], dXTi[i][j] ,dDTi[i][j]);
                    fprintf(f, "\n        dDq  = (%.2f)*(%.2f) = %.2f m", g_conditii_meteo_balistice.conditii_meteo_balistice_q[i], dXq[i][j], dDq[i][j]);
                    fprintf(f, "\n        dDvopsea             = %.2f m", dDvop[i][j]);
                    fprintf(f, "\n        -----------------------------------------------");
                    fprintf(f, "\n        dDcalc =             = %.2f", dDcalc[i][j][k]);
                    fprintf(f, "\n        distanta topo. (%.2f) = Dcalc(%.2f) - dDcalc(%.2f)", distanta_topo[i][j][k],  DdTrag[j], dDcalc[i][j][k]);
                    fprintf(f, "\n        CORECTII IN DIRECTIE :");
                    fprintf(f, "\n        Yw = %.2f   dYw = %.2f    derivatie = %.0f", Yw[i][j][k] , dYw[i][j], derivatie[i][j]);
                    fprintf(f, "\n        ddcalc = (%.2f)*(%.2f) + (%.0f) = %.0f", Yw[i][j][k], dYw[i][j], derivatie[i][j], ddcalc[i][j][k]);
                    fprintf(f, "%s\n", "    ________________________________________________________________________");

                }
            }
        }

        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }
};


void pregatire_completa::sageata(int *nr_bat, float *dist)
{
    g_tabla_tragere.tabla_tragere_incarca(*nr_bat);

    int i ;

    if (*dist > g_tabla_tragere.tabla_tragere_v5[g_tabla_tragere.tabla_tragere_plafon-1 ][0])
    {

        misc::cout << U("\n\t  Incarcatura ") << g_conditii_meteo_balistice.conditii_meteo_balistice_inc[0]
                << U(" nu asigura bataia materialului la distanta topografica = ")
                << std::fixed << std::setprecision(2) << *dist;
        
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }

    for(i=0; i < g_tabla_tragere.tabla_tragere_plafon ; ++i)
    {
        if ((*dist >= g_tabla_tragere.tabla_tragere_v5[i][0] ) && (*dist < (g_tabla_tragere.tabla_tragere_v5[i][0] + 100)))
        {
            ybul = g_tabla_tragere.tabla_tragere_v5[i][14];
            i = g_tabla_tragere.tabla_tragere_plafon +1 ;
        }
        else if ((*dist >= (g_tabla_tragere.tabla_tragere_v5[i][0] + 100)) && (*dist < g_tabla_tragere.tabla_tragere_v5[i+1][0]))
        {
            ybul = g_tabla_tragere.tabla_tragere_v5[i+1][14];
            i = g_tabla_tragere.tabla_tragere_plafon +1 ;
        }
    }
};

float pregatire_completa::Taerybul(int *n)
{

    long n1, m ;
    char f[10];
    float r ;

    n1 = atol(g_buletin_meteo.buletin_meteo_ch[*n]);
    m = n1/10000 ;

    gcvt((long)m, 0, f);

    r = (float)atof(f);
    if (r >= 50 )
        r = (-1)*(r -50);

    return(r);
};

float pregatire_completa::Gwy(int *n )
{
    long n1, m, k ;
    char f[10];
    float r ;

    n1 = atol(g_buletin_meteo.buletin_meteo_ch[*n]);
    m = n1/10000 ;         //  primele 2 cifre ;
    k =  (n1 - m*10000)/100 ;  //  cifrele de la mijloc 2 buc.

    gcvt((long)k, 0, f);
    r = (float)atof(f);
    return(r);
    //  functia intoarce valoarea redusa 12 inseamna 1200
    //  sau 9 = 900
};

float pregatire_completa::Vwy(int *n)
{
    long n1, m, k, l ;
    char f[10];
    float r ;

    n1 = atol(g_buletin_meteo.buletin_meteo_ch[*n]);           //  se da o grupa de 6 cifre = 010230
    m = n1/10000 ;                //  m = 1;
    k =  (n1 - m*10000)/100 ;     //  k = 2
    l =  n1 - m*10000 - k*100 ;   //  l = 30

    gcvt((long) l, 0, f);
    r = (float)atof(f);
    return(r);
};

float pregatire_completa::SB(void)
{

    int indexH1, indexH2 ;
    int indexTa1, indexTa2 ;
    long var_Hsma ;
    long var_Tasma;
    int x, j ;
    float sbhTa1, sbhTa2  ;
    float sb1;


    for(int i=0; i < 14; ++i)
    {
        if (Hsma >= sb[i][0] )
        {
            if (Hsma == sb[i][0])
            {
                indexH1 = i;
                j = 0;
                i = 20 ;
            }
            else
            {
                indexH1 = i-1 ;
                indexH2 = i ;
                j = 1 ;
                i = 20 ;
            }
        }
    }

    if(Tasma == 0)
    {
        indexTa1 = 4;
        x = 0 ;
    }
    else if(Tasma > 0)
    {
        indexTa1 = (-1)*(Tasma - (Tasma%10)) + 4 ;
        indexTa2 = (-1)*(Tasma - (Tasma%10)) + 4 -1 ;
        x = 1;
    }
    else
    {
        indexTa1 = (-1)*(Tasma - (Tasma%10)) + 4 +1 ;
        indexTa2 = (-1)*(Tasma - (Tasma%10)) + 4 ;
        x = 1;
    }

    if(j==0 && x==0)
    {
        sb1 = sb[indexH1][4];
    }
    else if(j == 1 && x== 0)
    {
        var_Hsma = Hsma - (long)sb[indexH1][0];
        sb1 = sb[indexH1][indexTa1] +
            (var_Hsma * (sb[indexH2][indexTa1] - sb[indexH1][indexTa1])) / 25.f ;
    }
    else if(j == 0 && x == 1)
    {
        if(Tasma < 0 )
        {
            var_Tasma = Tasma -  (Tasma + (Tasma % 10));
        }
        else
        {
            var_Tasma = Tasma -  (Tasma - (Tasma % 10));
        }

        sb1 = sb[indexH1][indexTa1] +
            (var_Tasma * (sb[indexH1][indexTa2] - sb[indexH1][indexTa1])) / 10.f ;
    }
    else  if(j == 1 && x == 1)
    {
        var_Hsma = Hsma - (long)sb[indexH1][0];
        sbhTa2 = sb[indexH1][indexTa2] +
            (var_Hsma * (sb[indexH2][indexTa2] - sb[indexH1][indexTa2])) / 25.f ;

        sbhTa1 = sb[indexH1][indexTa1] +
            (var_Hsma * (sb[indexH2][indexTa1] - sb[indexH1][indexTa2])) / 25.f ;


        if(Tasma < 0 )
        {
            var_Tasma = Tasma -  (Tasma + (Tasma % 10));
        }
        else
        {
            var_Tasma = Tasma -  (Tasma - (Tasma % 10));
        }

        sb1 = sbhTa1 + (var_Tasma*(sbhTa2 - sbhTa1)) / 10.f ;
    }
    return (sb1);
};

void pregatire_completa::calculeaza_conditiile_meteo(int *nr_bat, int *nr_dist, int *nr_dir)
{

    g_buletin_meteo.buletin_meteo_incarca();
    g_dispozitiv_de_lupta.dispozitivul_de_lupta_incarca();

    hsma = atol(g_buletin_meteo.buletin_meteo_ch[2]);
    size_t n1 = strlen(g_buletin_meteo.buletin_meteo_ch[3]);

    if(n1 > 5 || n1 < 3)
    {

        misc::cout << U("\n\t  Eroare in BMM, grupa 4, valoarea = ") << g_buletin_meteo.buletin_meteo_ch[3];
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }

    long m1;

    m1 = atol(g_buletin_meteo.buletin_meteo_ch[3]);
    Hsma = m1/100 ;
    Tasma =  m1 - Hsma*100 ;

    if(Hsma >= 500)
        Hsma = 500 - Hsma  ;

    if (Tasma > 50 || Tasma == 50)
        Tasma = 50 - Tasma ;


    incarca_datele();


    sageata (&(*nr_bat), &DdTrag[*nr_dist]);

    if(Hsma > 49.9 || Hsma < -249.9)
    {

        misc::cout << U("\n\t  Eroare in program. ");
        misc::cout << U("\n\t  B.M.M. contine in grupa 4 DHsma= ") << Hsma << U(" mm");
        misc::cout << U("\n\t  Intervalul pt. interpolare este : ( -250 , +50 ) mm ");
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }


    if(Tasma >29.9 || Tasma < -59.9)
    {
        misc::cout << U("\n\t  Eroare in program. ");
        misc::cout << U("\n\t  B.M.M. contine in grupa 4 DTsma= ") << Tasma;
        misc::cout << U("\n\t  Intervalul pt. interpolare este : ( -60 , +30 ) gr.C ");
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }



    for (int i=0; i < 500 ; ++i)
    {
        if(ybul <= 200 )
        {
            int w= 5 ;
            Taybul = Taerybul(&w);
            Gw = Gwy(&w);
            Gw = Util::round(Gw)*100 ;
            Vw = Vwy(&w);
            break;
        }


        if( strlen(g_buletin_meteo.buletin_meteo_ch[i]) >= 4 && strncmp(g_buletin_meteo.buletin_meteo_ch[i], "3030", 4) == 0 )
        {
            misc::cout << U("\n\t  Sageata ybul = ") << std::fixed << std::setprecision(2) << ybul << U(" m depaseste y max din B.M.M.");
            misc::cout << U("\n\t  Programul va fi terminat.");
            getchar();
            exit(EXIT_FAILURE);
        }


        if(i>= 6 && i%2 == 0)
        {
            //tratarea grupelor de altitudine
            //char temp[10];
            float a ;
            long m2 ;

            m1 = atol(g_buletin_meteo.buletin_meteo_ch[i]);
            m2 = (long) ((float)m1 / 100.f);

            //gcvt((long)m2, 0, temp);
            //a = (float)atof(temp);
            a = (float) m2;

            //a = altitudinea in metri standard B.M.M.;
            a= a*100 ;


            if( math::is_eq(ybul, a) )
            {
                // ybul -> altitudinea din T.T. cal. 152 mm .
                //  i = grupa urmatoare care detine DTa, Gw, Vw ;
                i = i+1 ;
                Taybul = Taerybul(&i);
                Gw = Gwy(&i);
                Gw = Util::round(Gw)*100 ;
                Vw = Vwy(&i);
                break;
            }
            else if(ybul < a )
            {

                //  sageata noastra este sub sageata standard <metri>
                int max_ ;
                int min_ ;

                //max_ = grupa DTa, Gw, Vw superioara ;
                max_ = i+1 ;

                //min_ = grupa DTa, Gw, Vw inferioara ;
                min_ = i-1 ;

                float ybulinf;
                float ybulsup;
                float ybuldif;
                float ybulmij;

                m1 = atol(g_buletin_meteo.buletin_meteo_ch[i-2]);
                m2 = (long)((float)m1 / 100.f);

                //gcvt((long) m2, 0, temp);
                //ybulinf = (float)atof(temp);
                ybulinf = (float) m2;

                //reprezinta altitudinea in metri ;
                ybulinf = ybulinf * 100.f ;


                m1 = atol(g_buletin_meteo.buletin_meteo_ch[i]);
                m2 = (long)((float)m1 / 100.f) ;

                //gcvt((long) m2, 0, temp);
                //ybulsup = (float)atof(temp);
                ybulsup = (float) m2;

                //reprezinta altitudinea superioara in metri
                ybulsup = ybulsup * 100.f ;


                // implementarea cazului de NEinterpolare Ta, Gw, Vw
                // din grupa cea mai apropiata||mijl = limita SUP ;

                ybuldif = ybulsup - ybulinf;
                ybulmij = ybulinf + ybuldif / 2.f ;

                if(ybul < ybulmij)
                {
                    Taybul = Taerybul(&min_);
                    Taybul =  Util::round (Taybul);
                    Gw = Gwy(&min_);
                    Gw =  Util::round (Gw)*100 ;
                    Vw = Vwy(&min_);
                    Vw =  Util::round (Vw);

                }
                else if(ybul >= ybulmij && ybul < ybulsup)
                {
                    Taybul = Taerybul(&max_);
                    Taybul =  Util::round(Taybul);
                    Gw = Gwy(&max_);
                    Gw =  Util::round(Gw)*100 ;
                    Vw = Vwy(&max_);
                    Vw =  Util::round(Vw);
                }
                else
                {
                    misc::cout << U("\n\t  Eroare in altitudinea de intrare in B.M.M = ") << std::fixed
                            << std::setprecision(2) << ybul;
                    misc::cout << U("\n\t  Programul va fi terminat");
                    getchar();
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
    } //for


    if ((hsma - g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[*nr_bat]) > -200  && (hsma - g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[*nr_bat]) < 200)
    {
        Ta[*nr_bat][*nr_dist] = Taybul ;
        Hpt[*nr_bat] = Hsma + ((hsma - g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[*nr_bat])/10);
    }
    else
    {
        Ta[*nr_bat][*nr_dist] = Taybul + 0.006f * ((float)hsma - g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[*nr_bat]);
        Hpt[*nr_bat] = Hsma + ((hsma - g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[*nr_bat]) / SB() );
    }

    //Subsecventa a functiei :  "calculeaza_conditiile_meteo(int *)"
    //care determina valorile Xw si Yw ";

    int  semnx;
    int semny;

    float var_Vw ;
    float var_Uw ;
    int indexiVw;
    int indexsVw;
    int indexiUw;
    int indexsUw ;


    if(GdTrag[*nr_dir] < 0 || GdTrag[*nr_dir] > 6000 || Gw < 0 || Gw > 6000)
    {
        misc::cout << U("\n\t  Eroare la descompunerea vantului in componente");
        misc::cout << U("\n\t  Gisment de tragere = ") << std::fixed << std::setprecision(0) << GdTrag[*nr_dir];
        misc::cout << U("\n\t  Gismentul vantului = ") << std::fixed << std::setprecision(0) << Gw;
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }


    Gob = GdTrag[*nr_dir];

    if(Gob < Gw)
        Gob += 6000 ;

    Uw = Gob - Gw ;

    if(Uw >= 0 && Uw < 1500)
    {
        semnx = -1 ;
        semny = 1 ;
    }
    else if(Uw >= 1500 && Uw < 3000)
    {
        Uw = 3000 - Uw;
        semnx = 1;
        semny = 1 ;
    }
    else if(Uw >= 300 && Uw < 4500)
    {
        Uw = Uw - 3000 ;
        semnx = 1;
        semny = -1 ;
    }
    else if(Uw >= 4500 && Uw <= 6000)
    {
        Uw = 6000 - Uw ;
        semnx = -1 ;
        semny = -1 ;
    }



    if(Gw < 0 || Gw > 6000)
    {
        misc::cout << U("\n\t  Eroare in program");
        misc::cout << U("\n\t  Grupa din buletin corespunzatoare cu Dtrag= ") << std::fixed << std::setprecision(2) << DdTrag[*nr_dist] << U(" m");
        misc::cout << U("\n\t  si Ybul = ") << std::fixed << std::setprecision(0) << ybul << U(" m, contine Gw = ") << Gw;
        misc::cout << U("\n\t  Valoare gismentului nu este reala");
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }


    if(Vw < 0 || Vw > 13.9)
    {
        misc::cout << U("\n\t  Eroare in program");
        misc::cout << U("\n\t  Grupa din buletin corespunzatoare cu Dtrag= ") << std::fixed << std::setprecision(2)
                << DdTrag[*nr_dist] << U(" m");
        misc::cout << U("\n\t  si Ybul = ") << std::fixed << std::setprecision(0) << ybul << U(" m, contine Vw = ") << Vw << U(" m/s");
        misc::cout << U("\n\t  Viteza vantului nu este reala");
        misc::cout << U("\n\t  Programul va fi terminat");
        getchar();
        exit(EXIT_FAILURE);
    }


    for(int i=2; i < 8; ++i)
    {
        if(Vw <= xw[0][i])
        {
            var_Vw = Vw - xw[0][i-1];
            indexiVw = i-1 ;
            indexsVw = i ;
            i = 20 ;
        }
    }

    for (int i=1; i < 16; ++i)
    {
        if(Uw <= xw[i][0])
        {
            var_Uw = Uw - xw[i-1][0];
            indexiUw = i-1 ;
            indexsUw = i  ;
            i = 20 ;
        }
    }

    float x;
    float y;
    float z;

    float xUVsw, xUViw ;
    float yUVsw, yUViw ;


    x = ((var_Uw)*(xw[indexsUw][indexsVw] - xw[indexiUw][indexsVw]))/100 ;
    xUVsw = xw[indexiUw][indexsVw] + x ;

    y = (var_Uw*(xw[indexsUw][indexiVw] - xw[indexiUw][indexiVw]))/100 ;
    xUViw = xw[indexiUw][indexiVw] + y ;

    z = (var_Vw*(xUVsw - xUViw))/2 ;
    Xw[*nr_bat][*nr_dist][*nr_dir] = xUViw + z ;

    x = (var_Uw*(yw[indexsUw][indexsVw] - yw[indexiUw][indexsVw]))/100 ;
    yUVsw =  yw[indexiUw][indexsVw] + x ;

    y = (var_Uw*(yw[indexsUw][indexiVw] - yw[indexiUw][indexiVw]))/100 ;
    yUViw = yw[indexiUw][indexiVw] + y ;

    z = (var_Vw*(yUVsw - yUViw))/2 ;
    Yw[*nr_bat][*nr_dist][*nr_dir] = yUViw + z ;

    Xw[*nr_bat][*nr_dist][*nr_dir] = semnx*(Xw[*nr_bat][*nr_dist][*nr_dir]);
    Yw[*nr_bat][*nr_dist][*nr_dir] = semny*(Yw[*nr_bat][*nr_dist][*nr_dir]);

};

void pregatire_completa::calculeaza_corectii_calculate()
{
    int lsup;
    int linf;
    float var_Dt;

    for(int i=0; i < 3; ++i)
    {    //  3 BATERII

        for(int j =0; j < 4; ++j)
        {  //  4 DISTANTE ;

            for(int k=0; k < 3; ++k)
            {  //  3 DIRECTII

                //se calc conditiile meteo pt. Bt i, Dist j, Dir k .
                calculeaza_conditiile_meteo(&i, &j, &k);

                for(int a=0; a < g_tabla_tragere.tabla_tragere_plafon ; a++)
                {
                    if(DdTrag[j] <= g_tabla_tragere.tabla_tragere_v5[a][0])
                    {
                        lsup = a;
                        linf = a-1 ;
                        a = 100 ;
                    }
                }


                dvoinc =  ((g_conditii_meteo_balistice.conditii_meteo_balistice_voinc[i] - g_tabla_tragere.tabla_tragere_vi)*100)/g_tabla_tragere.tabla_tragere_vi;
                dvo[i] = g_conditii_meteo_balistice.conditii_meteo_balistice_vop[i] +  dvoinc ;
                dtinc[i][j] = g_conditii_meteo_balistice.conditii_meteo_balistice_tinc[i] - 15 ;

                var_Dt = DdTrag[j] - g_tabla_tragere.tabla_tragere_v5[linf][0];


                float interval = 200.00 ;
                dXw[i][j] =  Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][7],
                    g_tabla_tragere.tabla_tragere_v5[lsup][7], 
                    interval) / 10.f;


                dDw[i][j][k] = (Xw[i][j][k])*(dXw[i][j]);

                dXH[i][j] = Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][8],
                    g_tabla_tragere.tabla_tragere_v5[lsup][8], 
                    interval) / 10.f;

                dDH[i][j] = Hpt[i] * dXH[i][j];

                dXTa[i][j] = Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][9],
                    g_tabla_tragere.tabla_tragere_v5[lsup][9],
                    interval) / 10.f;

                dDTa[i][j] = Ta[i][j] * dXTa[i][j];

                dXVo[i][j] =  Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][10],
                    g_tabla_tragere.tabla_tragere_v5[lsup][10], 
                    interval);

                dDVo[i][j] =  dvo[i] * dXVo[i][j];

                dXTi[i][j] =  Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][11],
                    g_tabla_tragere.tabla_tragere_v5[lsup][11], 
                    interval) / 10.f;

                dDTi[i][j] = dtinc[i][j] * dXTi[i][j];

                dXq[i][j] = Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][12],
                    g_tabla_tragere.tabla_tragere_v5[lsup][12], 
                    interval);

                dDq[i][j] = g_conditii_meteo_balistice.conditii_meteo_balistice_q[i] * dXq[i][j];

                switch(g_conditii_meteo_balistice.conditii_meteo_balistice_voppr[i][0])
                {
                case 'N' :
                    dDvop[i][j] = Util::interpoleaza(
                                            var_Dt, 
                                            g_tabla_tragere.tabla_tragere_v5[linf][8],                                                     
                                            g_tabla_tragere.tabla_tragere_v5[lsup][8], 
                                            interval);
                    break;

                default :
                    dDvop[i][j] = 0;
                    break ;
                } //switch



                //------------Dtcalc --------------------------------

                dDcalc[i][j][k] = dDw[i][j][k] + dDH[i][j] + dDTa[i][j] +
                    dDVo[i][j] + dDTi[i][j] + dDq[i][j] + dDvop[i][j];

                distanta_topo[i][j][k] = DdTrag[j] - dDcalc[i][j][k];

                dYw[i][j] =  Util::interpoleaza(                    
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][6], 
                    g_tabla_tragere.tabla_tragere_v5[lsup][6], 
                    interval) / 10.f;

                derivatie[i][j] = Util::interpoleaza(
                    var_Dt, 
                    g_tabla_tragere.tabla_tragere_v5[linf][5], 
                    g_tabla_tragere.tabla_tragere_v5[lsup][5], 
                    interval);

                ddcalc[i][j][k] = derivatie[i][j] + dYw[i][j] * Yw[i][j][k];


                g_obiectiv.obiectiv_DdeTrag[i][j][k] = distanta_topo[i][j][k];
                g_obiectiv.obiectiv_GdeTrag[k] = GdTrag[k];
                g_obiectiv.obiectiv_corectii_calculate_bataie[i][j][k] = dDcalc[i][j][k];
                g_obiectiv.obiectiv_corectii_calculate_directie[i][j][k] = ddcalc[i][j][k];
            }
        }
    }

    g_control_lucru.control_lucru_C_C = 1 ;

    registru();
};

void pregatire_completa::afiseaza_corectii_calculate()
{
    for(int i=0; i<3; i++) 
    {
        for(int j=0; j<4; j++) 
        {
            for(int k=0; k<3; k++) 
            {

                //
                clrscr();
                misc::cout << U("\n\n");
                printf("\n        ----------------------------------------");
                misc::cout << U("\n\t  Corectii calculate pt Bt. ") << i+1 << U(" Art");                                       
                printf("\n            DISTANTA %d (%.2f)  GISMENT %d (%.0f)\n",j+1, DdTrag[j], k+1, GdTrag[k]);
                printf("\n        ----------------------------------------");
                if (g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] == 0)
                    printf("\n        Distanta   = %.2f           Incarcatura = COMPLETA" , DdTrag[j] );
                else
                    printf("\n        Distanta   = %.2f           incarcatura = a %.0f -a" , DdTrag[j], g_conditii_meteo_balistice.conditii_meteo_balistice_inc[i] );
                printf("\n        dDw  =  Xw   *  dXw = rezultat ;");
                printf("\n        dDw  = (%.2f)*(%.2f) = %.2f m",Xw[i][j][k], dXw[i][j], dDw[i][j][k]);
                printf("\n        dDH  = (%.2f)*(%.2f) = %.2f m", Hpt[i], dXH[i][j], dDH[i][j]);
                printf("\n        dDTa = (%.2f)*(%.2f) = %.2f m",Ta[i][j], dXTa[i][j], dDTa[i][j] );
                printf("\n        dDVo = (%.2f)*(%.2f) = %.2f m",dvo[i] , dXVo[i][j], dDVo[i][j] );
                printf("\n        dDTi = (%.2f)*(%.2f) = %.2f m", dtinc[i][j], dXTi[i][j], dDTi[i][j]);
                printf("\n        dDq  = (%.2f)*(%.2f) = %.2f m", g_conditii_meteo_balistice.conditii_meteo_balistice_q[i], dXq[i][j], dDq[i][j]);
                printf("\n        dDvopsea             = %.2f m", dDvop[i][j]);
                printf("\n        ----------------------------------------");
                printf("\n        dDcalc =             = %.2f", dDcalc[i][j][k]);
                printf("\n        distanta topo. (%.2f) = Dcalc(%.2f) - dDcalc(%.2f)",
                       distanta_topo[i][j][k],  DdTrag[j], dDcalc[i][j][k]);

                printf("\n\n        CORECTII IN DIRECTIE :");
                printf("\n\n        Yw = %.2f   dYw = %.2f    derivatie = %.0f", \
                       Yw[i][j][k] , dYw[i][j], derivatie[i][j]);
                printf("\n        ddcalc = (%.2f)*(%.2f) + (%.0f) = %.0f", Yw[i][j][k],\
                       dYw[i][j], derivatie[i][j], ddcalc[i][j][k]);
                printf("\n        ------------------------------------------------------");

                getchar();
            }
        }
    }
};


