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



#include "observare_conjugata.h"


//c
#include <assert.h>
//c++
//misc
#include "stream.hpp"
#include "math.hpp"
//program
#include "control_lucru.h"
#include "obiectiv.h"
#include "structura_elementelor.h"
#include "artutil.h"




observare_conjugata::observare_conjugata()
{
};

observare_conjugata::~observare_conjugata()
{
};


void observare_conjugata::observare_conjugata_control()
{
    primeste_datele();

    calculeaza_datele();

    afiseaza_datele();

    g_structura_elementelor.structura_elementelor_control();

    registru();
};

void observare_conjugata::primeste_datele()
{

    g_control_lucru.control_lucru_indicarea_obiectivelor_zero();


    char cha[10];
    char cCla[10];
    char cClb[10];

    g_obiectiv.obiectiv_primeste_bateria();

    for(int i=0; i < 3 ; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        //critical condition
        assert(g_obiectiv.obiectiv_btno[i] == i+1);



        g_obiectiv.obiectiv_primeste_datele(i);

        
        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Bt ") << g_obiectiv.obiectiv_btno[i];
        misc::cout << U("\n\t  Indicarea obiectiului prin citire si distanta");
        
        misc::cout << U("\n\t  Citire din PO Dn la Obv = ");
        g_control_lucru.control_lucru_getstdin(cClb, 10);
        Clb[i] = (float)atof(cClb);
        
        misc::cout << U("\n\t  Citire din POL Dn la Obv = ");
        g_control_lucru.control_lucru_getstdin(cCla, 10);
        Cla[i] = (float)atof(cCla);
        
        
        misc::cout << U("\n\t  h = ");
        g_control_lucru.control_lucru_getstdin(cha, 10);
        ho[i] = (float)atof(cha);
    }

};

void observare_conjugata::calculeaza_datele()
{
    for(int i=0; i < 3 ; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        float Gap = g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb - Cla[i] ;

        //  Transformarea citirii lunetei in gisment;
        Gap = Util::transform3000(Gap);

        //  Transformarea citirii lunetei in gisment;
        float Gbp = g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb - Clb[i] ;
        Gbp = Util::transform3000(Gbp);



        //  CALCULEAZA DISTANTA SI GISMENTUL INTRE PO SI POL
        //  calculul directiei si distantei intre A->B
        float G_virtual = 0. ;
        /*
        g_structura_elementelor.structura_elementelor_calculeaza_rectangular(
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[0],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[0],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[0],
            G_virtual);
        */
        
        SPolar objPolar = Util::rectangular(g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[1],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[0],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[0],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[0],
            G_virtual);


        //float Dab = g_structura_elementelor.distanta ;
        //float Gab = g_structura_elementelor.gisment_final ;

        float Dab = objPolar.distanta;
        float Gab = objPolar.gisment_final;

        //  Calculam unghiurile alfa, beta si gama ;
        float alfa = Gab - Gap ;
        alfa = Util::normalize6000(alfa);

        float beta = Gbp - Gab ;
        beta = Util::transform3000(beta);

        float gama = 3000 - alfa - beta ;
        gama = Util::normalize6000(gama);

        // sin theorm
        float Dap = Dab * (float)sin(beta*M2D*math::DEG2RAD) / (float)sin(gama*math::DEG2RAD*M2D);
        float Dbp = Dab * (float)sin(alfa*M2D*math::DEG2RAD) / (float)sin(gama*math::DEG2RAD*M2D);

        //SE CUNOSC Gap, Dap, Gbp, Dbp ; => Xp(a), Yp(a);
        //                               => Xp(b), Yp(b);

        float tct_a = 0.;
        float tct_b = 0. ;

		cad::TPoint3d<float> objPos = Util::polar(
			    g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[0], 
			    g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[0], 
			    g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[0],
			    Dbp, 
			    Gbp,
			    tct_b, 
			    G_virtual);
		
		float Xp_b = objPos.x();
		float Yp_b = objPos.y();

		objPos = Util::polar(
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[1], 
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[1], 
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[1],
			Dap, 
			Gap,
			tct_a, 
			G_virtual);

		float Xp_a = objPos.x();
		float Yp_a = objPos.y();

        g_obiectiv.obiectiv_X_obiectiv[i] = (Xp_a + Xp_b) / 2.;
        g_obiectiv.obiectiv_Y_obiectiv[i] = (Yp_a + Yp_b) / 2.;
        g_obiectiv.obiectiv_h_obiectiv[i] = ho[i];

    } //for

};

void observare_conjugata::afiseaza_datele()
{
    for(int i=0; i < 3; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        //
        clrscr();
        misc::cout << U("\n\n");
        misc::cout << U("\n\t  Coordonatele obiectivului = ") << g_obiectiv.obiectiv_nr_obiectiv[i];
        misc::cout << U("\n\t  Bt ") << g_obiectiv.obiectiv_btno[i];
        
        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_X_obiectiv[i];
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_Y_obiectiv[i];
        misc::cout << U("\n\t  h = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_h_obiectiv[i];

        getchar();
    }    
};

void observare_conjugata::registru()
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


        for(int i=0; i < 3; ++i)
        {
            if(g_obiectiv.obiectiv_btno[i] == 0 )
                continue ;

            time_t t ;
            time(&t);
            fprintf(f, "%s\n", "________________________________________________________________________________\n");
            fprintf(f, "%s %d %s %s" , "    Bateria " , i+1,  "  Artilerie          Data sistemului  : ",  ctime(&t));

            if(g_control_lucru.control_lucru_P_C == 1)
            {
                fprintf(f, "%s", "      Pregatire Completa");
            }
            else
            {
                fprintf(f, "%s", "      Transport de foc");
            }

            fprintf(f, "%s %s\n", "       Obiectiv : ",  g_obiectiv.obiectiv_nr_obiectiv[i]);
            fprintf(f, "      PODn Citire = %.0f    POL Citire = %.0f\n", Clb[i], Cla[i] );

            fprintf(f, "%s %.2f\n", "   Altitudine : ",  g_obiectiv.obiectiv_h_obiectiv[i]);
            fprintf(f, "%s %.0f %s %.0f\n", "   Front : ", 
                g_obiectiv.obiectiv_front[i], "    Adancime : ",   g_obiectiv.obiectiv_adancime[i]);
            fprintf(f, "%s %.0f %s %.0f minute\n",
                    "    Consum : ", g_obiectiv.obiectiv_norma_consum[i],
                    "    Ciocan de foc : ", g_obiectiv.obiectiv_timp_ciocan_de_foc[i]);

            fprintf(f, "%s", "________________________________________________________________________________\n");
        } //for


        fclose(f);
        chmod(file.c_str(), S_IREAD);

    } //if


    if(g_control_lucru.control_lucru_fisier_cumulat_T_F_I_O == 1 && g_control_lucru.control_lucru_T_F == 1)
    {
        misc::string file(g_control_lucru.control_lucru_get_tf_test_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE);

        if((f = fopen(file.c_str(), "a")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            exit(EXIT_FAILURE);
        }


        for(int i=0; i < 3; ++i)
        {
            if(g_obiectiv.obiectiv_btno[i] == 0 )
                continue ;

            time_t t ;
            time(&t);
            fprintf(f, "%s\n", "________________________________________________________________________________\n");
            fprintf(f, "%s %d %s %s" , "    Bateria " , i+1, "  Artilerie          Data sistemului  : ",  ctime(&t));

            if(g_control_lucru.control_lucru_P_C == 1)
            {
                fprintf(f, "%s", "      Pregatire Completa");
            }
            else
            {
                fprintf(f, "%s", "      Transport de foc");
            }

            fprintf(f, "%s %s\n", "       Obiectiv : ",  g_obiectiv.obiectiv_nr_obiectiv[i]);
            fprintf(f, "    PODn Citire = %.0f    POL Citire = %.0f\n", Clb[i], Cla[i] );

            fprintf(f, "%s %.2f\n", "   Altitudine : ",  g_obiectiv.obiectiv_h_obiectiv[i]);
            fprintf(f, "%s %.0f %s %.0f\n", "   Front : ", g_obiectiv.obiectiv_front[i], "    Adancime : ",   g_obiectiv.obiectiv_adancime[i]);

            fprintf(f, "%s %.0f %s %.0f minute\n", "    Consum : ",  g_obiectiv.obiectiv_norma_consum[i], "    Ciocan de foc : ", g_obiectiv.obiectiv_timp_ciocan_de_foc[i]);

            fprintf(f, "%s", "________________________________________________________________________________\n");
        } //for


        fclose(f);
        chmod(file.c_str(), S_IREAD);
    } //if


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


        for(int i=0; i < 3; ++i)
        {
            if(g_obiectiv.obiectiv_btno[i] == 0)
                continue ;

            time_t t ;
            time(&t);
            fprintf(f, "%s\n", "________________________________________________________________________________\n");
            fprintf(f, "    Bateria %d Artilerie          Data sistemului  : %s\n",i+1,  ctime(&t));
            fprintf(f, "%s\n", "   *Elemente topografice, elemente calculate, date si coeficienti de tragere*\n");

            if(g_control_lucru.control_lucru_P_C == 1)
            {
                fprintf(f, "      Pregatire Completa\n");
            }
            else
            {
                fprintf(f, "      Transport de foc\n");
            }


            fprintf(f, "    Indicarea obiectivului din punctele observarii conjugate\n");
            fprintf(f, "%s %s\n", "    Obiectiv = ",  g_obiectiv.obiectiv_nr_obiectiv[i]);
            fprintf(f, "    X = %.2f  Y = %.2f   h = %.2f\n",
                    g_obiectiv.obiectiv_X_obiectiv[i], 
                    g_obiectiv.obiectiv_Y_obiectiv[i], 
                    g_obiectiv.obiectiv_h_obiectiv[i]);

            if( math::is_eq(g_tabla_tragere.tabla_tragere_incarcatura[i], 0.f) )
            {
                fprintf(f, "%s\n", "    Incarcatura   Completa");
            }
            else
            {
                fprintf(f, "%s %.0f\n", "    Incarcatura   ", g_tabla_tragere.tabla_tragere_incarcatura[i]);
            }

            fprintf(f, "%s %.2f", "    Dt  = ", g_obiectiv.obiectiv_Dt[i]);

            if(g_obiectiv.obiectiv_delta_h[i] > 0)
            {
                fprintf(f, "%s %.2f\n", "    dh  = + ", g_obiectiv.obiectiv_delta_h[i]);
            }
            else
            {
                fprintf(f, "%s %.2f\n", "    dh  = ", g_obiectiv.obiectiv_delta_h[i]);
            }

            if(g_obiectiv.obiectiv_Mdt[i] > 0)
            {
                fprintf(f, "%s %.0f\n", "    Mdt = + ", g_obiectiv.obiectiv_Mdt[i]);
            }
            else
            {
                fprintf(f, "%s %.0f\n", "    Mdt = ", g_obiectiv.obiectiv_Mdt[i]);
            }


            if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
            {
                fprintf(f, "%s %.2f m ", "    Dc  = ", g_obiectiv.obiectiv_Dc[i]);

                if(g_obiectiv.obiectiv_corectie_Bataie[i] > 0)
                {
                    fprintf(f, "%s %.2f m",   "  dD  = + ", g_obiectiv.obiectiv_corectie_Bataie[i]);
                }
                else
                {
                    fprintf(f, "%s %.2f m",   "  dD  =  ", g_obiectiv.obiectiv_corectie_Bataie[i]);
                }

                fprintf(f, "%s %.0f\n",   "  Ic  = ", g_obiectiv.obiectiv_Ic[i]);

                if(g_control_lucru.control_lucru_F_B == 0)
                {
                    fprintf(f, "%s %.0f %s %.2f %s", "    salt= ", g_obiectiv.obiectiv_salt[i], "(", g_obiectiv.obiectiv_val_salt_m[i], ")");
                }

                fprintf(f, "%s %.0f",     "  Niv = ", g_obiectiv.obiectiv_Niv[i]);

                if(g_obiectiv.obiectiv_corectie_Directie[i] > 0)
                {
                    fprintf(f, "%s %.0f\n",     "  ddir= + ", g_obiectiv.obiectiv_corectie_Directie[i]);
                }
                else
                {
                    fprintf(f, "%s %.0f\n",     "  ddir= ", g_obiectiv.obiectiv_corectie_Directie[i]);
                }

                if(g_obiectiv.obiectiv_Mdc[i] > 0)
                {
                    fprintf(f, "%s %.0f", "    Mdc = + ", g_obiectiv.obiectiv_Mdc[i]);
                }
                else
                {
                    fprintf(f, "%s %.0f", "    Mdc = ", g_obiectiv.obiectiv_Mdc[i]);
                }

                fprintf(f, "%s %.0f", "    f = ", g_obiectiv.obiectiv_fascicul[i]);
                fprintf(f, "%s %.0f\n", "    nr_directii  = ", g_obiectiv.obiectiv_nr_directii[i]);

                fprintf(f, "%s %.0f", "    consum piesa = ", g_obiectiv.obiectiv_consum_piesa[i]);

                if(g_obiectiv.obiectiv_norma_consum[i] == 0)
                {
                    fprintf(f, "%s\n", "   vijelie INCARCATI(FOC!)");
                }
                else if(g_obiectiv.obiectiv_norma_consum[i] > 0)
                {
                    fprintf(f, "%s %.1f\n", "    ritm  = ", g_obiectiv.obiectiv_ritm_de_tragere[i]);
                }
            } //if


            fprintf(f, "%s\n", "________________________________________________________________________________\n");


            fprintf(f, "%s\n", "                           DATE SI COEFICIENTI");

            fprintf(f, "%s %.2f", "    Do = ", g_obiectiv.obiectiv_Do_pco[i]);

            if(g_obiectiv.obiectiv_To_pco[i] > 0)
            {
                fprintf(f, "%s %.0f", "    To = + ", g_obiectiv.obiectiv_To_pco[i]);
            }
            else
            {
                fprintf(f, "%s %.0f", "    To = ", g_obiectiv.obiectiv_To_pco[i]);
            }

            fprintf(f, "%s %.0f\n", "    p  = ", g_obiectiv.obiectiv_p[i]);

            if(g_obiectiv.obiectiv_p[i] < 500)
            {
                fprintf(f, "%s %.2f", "    Kd = ", g_obiectiv.obiectiv_Kd[i]);
                fprintf(f, "%s %.0f\n", "    Sd = ", g_obiectiv.obiectiv_Sd[i]);
            }
            else
            {
                fprintf(f, "%s %.2f", "    Kb   = ", g_obiectiv.obiectiv_Kb[i]);
                fprintf(f, "%s %.2f\n", "    Ka   = ", g_obiectiv.obiectiv_Ka[i]);
            }

            fprintf(f, "%s %.2f", "    Do(PODn) = ", g_obiectiv.obiectiv_Do_po[i]);

            if(g_obiectiv.obiectiv_To_po[i] > 0)
            {
                fprintf(f,"%s %.0f", "    To(PODn) = + ", g_obiectiv.obiectiv_To_po[i]);
            }
            else
            {
                fprintf(f,"%s %.0f", "    To(PODn) = ", g_obiectiv.obiectiv_To_po[i]);
            }

            fprintf(f, "%s %.0f\n", "    p(PODn)  = ",  g_obiectiv.obiectiv_p_po[i]);
            fprintf(f, "%s %.2f", "    Do(POL)  = ", g_obiectiv.obiectiv_Do_pol[i]);

            if(g_obiectiv.obiectiv_To_pol[i] > 0)
            {
                fprintf(f, "%s %.0f", "    To(POL)  = + ", g_obiectiv.obiectiv_To_pol[i]);
            }
            else
            {
                fprintf(f, "%s %.0f", "    To(POL)  = ", g_obiectiv.obiectiv_To_pol[i]);
            }

            fprintf(f, "%s %.0f\n", "    p(POL)   = ",  g_obiectiv.obiectiv_p_pol[i]);

            fprintf(f, "%s %.0f", "    gama     = ", g_obiectiv.obiectiv_gama[i]);

            fprintf(f, "%s %.1f",  "    Do(PODn)/gama = ", g_obiectiv.obiectiv_Dpo_peGama[i]);
            fprintf(f, "%s %.1f\n",  "    Do(POL)/gama  = ", g_obiectiv.obiectiv_Dpol_peGama[i]);

            if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
            {
                fprintf(f, "%s %.0f", "    furcuta  = ", g_obiectiv.obiectiv_furcuta[i]);
                fprintf(f, "%s %.0f", "    Apb      = ", g_obiectiv.obiectiv_Apb[i]);
                fprintf(f, "%s %.0f\n", "    dXmiime  = ", g_obiectiv.obiectiv_dXmiime[i]);
            }

            fprintf(f, "%s\n", "________________________________________________________________________________\n");

        } //for


        fclose(f);
        chmod(file.c_str(), S_IREAD);
    } //if


    if(g_control_lucru.control_lucru_fisier_cumulat_T_FRez_C_O_D_Coef  == 1 && g_control_lucru.control_lucru_T_F == 1)
    {
        misc::string file(g_control_lucru.control_lucru_get_tf_test_rezolvare_path());

        chmod(file.c_str(), S_IREAD|S_IWRITE);

        if((f = fopen(file.c_str(), "a")) == NULL)
        {
            misc::cout << U("\n\t  Eroare la deschiderea fisierului: ") << file.c_str();
            perror("");
            exit(EXIT_FAILURE);
        }


        for(int i=0; i < 3; ++i)
        {

            if(g_obiectiv.obiectiv_btno[i] == 0)
                continue ;

            time_t t ;
            time(&t);
            fprintf(f, "%s\n", "________________________________________________________________________________\n");
            fprintf(f, "    Bateria %d Artilerie          Data sistemului  : %s\n", i+1,  ctime(&t));
            fprintf(f, "%s\n", "   *Elemente topografice, elemente calculate, date si coeficienti de tragere*\n");
            fprintf(f, "    Indicarea obiectivului din punctele observarii conjugate\n");
            fprintf(f, "%s %s\n", "    Obiectiv = ",  g_obiectiv.obiectiv_nr_obiectiv[i]);
            fprintf(f, "    X = %.2f  Y = %.2f   h = %.2f\n", g_obiectiv.obiectiv_X_obiectiv[i], g_obiectiv.obiectiv_Y_obiectiv[i], g_obiectiv.obiectiv_h_obiectiv[i]);

            if( math::is_eq(g_tabla_tragere.tabla_tragere_incarcatura[i], 0.f) )
            {
                fprintf(f, "%s\n", "    Incarcatura   Completa");
            }
            else
            {
                fprintf(f, "%s %.0f\n", "    Incarcatura   ", g_tabla_tragere.tabla_tragere_incarcatura[i]);
            }

            fprintf(f, "%s %.2f", "    Dt  = ", g_obiectiv.obiectiv_Dt[i]);

            if(g_obiectiv.obiectiv_delta_h[i] > 0)
            {
                fprintf(f, "%s %.2f\n", "    dh  = + ", g_obiectiv.obiectiv_delta_h[i]);
            }
            else
            {
                fprintf(f, "%s %.2f\n", "    dh  = ", g_obiectiv.obiectiv_delta_h[i]);
            }

            if(g_obiectiv.obiectiv_Mdt[i] > 0)
            {
                fprintf(f, "%s %.0f\n", "    Mdt = + ", g_obiectiv.obiectiv_Mdt[i]);
            }
            else
            {
                fprintf(f, "%s %.0f\n", "    Mdt = ", g_obiectiv.obiectiv_Mdt[i]);
            }


            if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
            {

                fprintf(f, "%s %.2f m ", "    Dc  = ", g_obiectiv.obiectiv_Dc[i]);

                if(g_obiectiv.obiectiv_corectie_Bataie[i] > 0)
                {
                    fprintf(f, "%s %.2f m",   "  dD  = + ", g_obiectiv.obiectiv_corectie_Bataie[i]);
                }
                else
                {
                    fprintf(f, "%s %.2f m",   "  dD  =  ", g_obiectiv.obiectiv_corectie_Bataie[i]);
                }

                fprintf(f, "%s %.0f\n",   "  Ic  = ", g_obiectiv.obiectiv_Ic[i]);

                if(g_control_lucru.control_lucru_F_B == 0)
                {
                    fprintf(f, "%s %.0f %s %.2f %s", "    salt= ", g_obiectiv.obiectiv_salt[i], "(", g_obiectiv.obiectiv_val_salt_m[i], ")");
                }

                fprintf(f, "%s %.0f", "  Niv = ", g_obiectiv.obiectiv_Niv[i]);

                if(g_obiectiv.obiectiv_corectie_Directie[i] > 0)
                {
                    fprintf(f, "%s %.0f\n", "  ddir= + ", g_obiectiv.obiectiv_corectie_Directie[i]);
                }
                else
                {
                    fprintf(f, "%s %.0f\n", "  ddir= ", g_obiectiv.obiectiv_corectie_Directie[i]);
                }


                if(g_obiectiv.obiectiv_Mdc[i] > 0)
                {
                    fprintf(f, "%s %.0f", "    Mdc = + ", g_obiectiv.obiectiv_Mdc[i]);
                }
                else
                {
                    fprintf(f, "%s %.0f", "    Mdc = ", g_obiectiv.obiectiv_Mdc[i]);
                }

                fprintf(f, "%s %.0f", "    f = ", g_obiectiv.obiectiv_fascicul[i]);
                fprintf(f, "%s %.0f\n", "    nr_directii  = ", g_obiectiv.obiectiv_nr_directii[i]);

                fprintf(f, "%s %.0f", "    consum piesa = ", g_obiectiv.obiectiv_consum_piesa[i]);

                if(g_obiectiv.obiectiv_norma_consum[i] == 0)
                {
                    fprintf(f, "%s\n", "   vijelie INCARCATI (FOC!)");
                }
                else if(g_obiectiv.obiectiv_norma_consum[i] > 0)
                {
                    fprintf(f, "%s %.1f\n", "    ritm  = ", g_obiectiv.obiectiv_ritm_de_tragere[i]);
                }
            } //if

            fprintf(f, "%s\n", "________________________________________________________________________________\n");

            fprintf(f, "%s\n", "                           DATE SI COEFICIENTI" );

            fprintf(f, "%s %.2f", "    Do = ", g_obiectiv.obiectiv_Do_pco[i]);


            if(g_obiectiv.obiectiv_To_pco[i] > 0)
            {
                fprintf(f, "%s %.0f", "    To = + ", g_obiectiv.obiectiv_To_pco[i]);
            }
            else
            {
                fprintf(f, "%s %.0f", "    To = ", g_obiectiv.obiectiv_To_pco[i]);
            }

            fprintf(f, "%s %.0f\n", "    p  = ", g_obiectiv.obiectiv_p[i]);

            if(g_obiectiv.obiectiv_p[i] < 500)
            {
                fprintf(f, "%s %.2f", "    Kd = ", g_obiectiv.obiectiv_Kd[i]);
                fprintf(f, "%s %.0f\n", "    Sd = ", g_obiectiv.obiectiv_Sd[i]);
            }
            else
            {
                fprintf(f, "%s %.2f", "    Kb   = ", g_obiectiv.obiectiv_Kb[i]);
                fprintf(f, "%s %.2f\n", "    Ka   = ", g_obiectiv.obiectiv_Ka[i]);
            }

            fprintf(f, "%s %.2f", "    Do(PODn) = ", g_obiectiv.obiectiv_Do_po[i]);

            if(g_obiectiv.obiectiv_To_po[i] > 0)
            {
                fprintf(f,"%s %.0f", "    To(PODn) = + ", g_obiectiv.obiectiv_To_po[i]);
            }
            else
            {
                fprintf(f,"%s %.0f", "    To(PODn) = ", g_obiectiv.obiectiv_To_po[i]);
            }

            fprintf(f, "%s %.0f\n", "    p(PODn)  = ",  g_obiectiv.obiectiv_p_po[i]);
            fprintf(f, "%s %.2f", "    Do(POL)  = ", g_obiectiv.obiectiv_Do_pol[i]);

            if(g_obiectiv.obiectiv_To_pol[i] > 0)
            {
                fprintf(f, "%s %.0f", "    To(POL)  = + ", g_obiectiv.obiectiv_To_pol[i]);
            }
            else
            {
                fprintf(f, "%s %.0f", "    To(POL)  = ", g_obiectiv.obiectiv_To_pol[i]);
            }

            fprintf(f, "%s %.0f\n", "    p(POL)   = ",  g_obiectiv.obiectiv_p_pol[i]);

            fprintf(f, "%s %.0f", "    gama     = ", g_obiectiv.obiectiv_gama[i]);

            fprintf(f, "%s %.1f",  "    Do(PODn)/gama = ", g_obiectiv.obiectiv_Dpo_peGama[i]);
            fprintf(f, "%s %.1f\n",  "    Do(POL)/gama  = ", g_obiectiv.obiectiv_Dpol_peGama[i]);

            if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
            {
                fprintf(f, "%s %.0f", "    furcuta  = ", g_obiectiv.obiectiv_furcuta[i]);
                fprintf(f, "%s %.0f", "    Apb      = ", g_obiectiv.obiectiv_Apb[i]);
                fprintf(f, "%s %.0f\n", "    dXmiime  = ", g_obiectiv.obiectiv_dXmiime[i]);
            }

            fprintf(f, "%s\n", "________________________________________________________________________________\n");

        } //for


        fclose(f);
        chmod(file.c_str(), S_IREAD);

    } //if

    for(int i=0; i<3;i++)
    {
        g_obiectiv.obiectiv_btno[i] = 0 ;
    }
};

