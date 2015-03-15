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


#include "foc_de_baraj.h"

//c
#include <assert.h>
//c++
//misc
#include "stream.hpp"
//program
#include "control_lucru.h"
#include "obiectiv.h"
#include "structura_elementelor.h"



foc_de_baraj::foc_de_baraj()
{
};

foc_de_baraj::~foc_de_baraj()
{
};

void foc_de_baraj::foc_de_baraj_control()
{
    primeste_datele();

    calculeaza_datele();

    afiseaza_datele();

    g_structura_elementelor.structura_elementelor_control();

    registru();
};


void foc_de_baraj::primeste_datele()
{
    g_control_lucru.control_lucru_indicarea_obiectivelor_zero();
    g_control_lucru.control_lucru_F_B = 1;

    g_obiectiv.obiectiv_primeste_bateria();

    
    //
    clrscr();
    misc::cout << U("\n\n");
    misc::cout << U("\n\t  Introduceti coordonatele focului de baraj");
    misc::cout << U("\n\t  Limita dreapta");
    
    misc::cout << U("\n\t  x = ");
    g_control_lucru.control_lucru_getstdin(g_obiectiv.obiectiv_X_dreapta);

    misc::cout << U("\n\t  y = ");
    g_control_lucru.control_lucru_getstdin(g_obiectiv.obiectiv_Y_dreapta);

    misc::cout << U("\n\t  Limita stanga");
    misc::cout << U("\n\t  x = ");
    g_control_lucru.control_lucru_getstdin(g_obiectiv.obiectiv_X_stanga);

    misc::cout << U("\n\t  y = ");
    g_control_lucru.control_lucru_getstdin(g_obiectiv.obiectiv_Y_stanga);

    misc::cout << U("\n\t  h = ");
    g_control_lucru.control_lucru_getstdin(g_obiectiv.obiectiv_h_stanga);

    g_obiectiv.obiectiv_h_dreapta = g_obiectiv.obiectiv_h_stanga ;
};

void foc_de_baraj::calculeaza_datele()
{
    float nr_baterii = 0 ;
    for(int i=0; i<3; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] != 0)
            ++nr_baterii;
    }
    

    float gisment_virtual = 0.f ;

    
    SPolar objPolar = Util::rectangular(g_obiectiv.obiectiv_X_dreapta, 
        g_obiectiv.obiectiv_Y_dreapta, 
        g_obiectiv.obiectiv_h_dreapta,
        g_obiectiv.obiectiv_X_stanga, 
        g_obiectiv.obiectiv_Y_stanga, 
        g_obiectiv.obiectiv_h_stanga,
        gisment_virtual);

    //float Front = g_structura_elementelor.distanta ;
    float Front = objPolar.distanta;
    //float G_final = g_structura_elementelor.gisment_final ;
    float G_final = objPolar.gisment_final;

    G_final = Util::normalize6000(G_final);
    float tct  = 0. ;
    float btcurenta = 0.;

    for(int i=0; i<3; i++)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue;

        //critical condition
        assert(g_obiectiv.obiectiv_btno[i] == i+1);

        float Front_bt = Front / nr_baterii;        
        float dr_centru_bt = (Front_bt / 2.) + (btcurenta * Front_bt);
        ++btcurenta;
        

		cad::TPoint3d<float> objPos = Util::polar(
			g_obiectiv.obiectiv_X_dreapta, 
		    g_obiectiv.obiectiv_Y_dreapta, 
		    g_obiectiv.obiectiv_h_dreapta,
		    dr_centru_bt, 
		    G_final,
		    tct, 
		    gisment_virtual);

		g_obiectiv.obiectiv_X_obiectiv[i] =  objPos.x();
		g_obiectiv.obiectiv_Y_obiectiv[i] =  objPos.y();
		g_obiectiv.obiectiv_h_obiectiv[i] =  objPos.z();

        g_obiectiv.obiectiv_front[i] = Front ;
    } //for
};

void foc_de_baraj::afiseaza_datele()
{      
    for(int i=0; i < 3; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
        {
            continue ;
        }

        
        //
        clrscr();
        misc::cout << U("\n\n");               
        misc::cout << U("\n\t  Coordonate centru FB pt Bt ") << g_obiectiv.obiectiv_btno[i] << U(" Art");      
        misc::cout << U("\n\t  x = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_X_obiectiv[i];
        misc::cout << U("\n\t  y = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_Y_obiectiv[i];
        misc::cout << U("\n\t  h = ") << std::fixed << std::setprecision(2) << g_obiectiv.obiectiv_h_obiectiv[i];

        getchar();
    } //for
};

void foc_de_baraj::registru()
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
        } //if


        for(int i=0; i < 3; ++i)
        {
            if(g_obiectiv.obiectiv_btno[i] == 0)
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
            fprintf(f, "     Foc de baraj\n");
            fprintf(f, "     Limita dreapta X = %.2f Y = .%2f \n", g_obiectiv.obiectiv_X_dreapta, g_obiectiv.obiectiv_Y_dreapta);
            fprintf(f, "        Limita stanga  X = %.2f Y = .%2f \n", g_obiectiv.obiectiv_X_stanga,  g_obiectiv.obiectiv_Y_stanga);
            fprintf(f, "        Altitudine : %.0f\n",  g_obiectiv.obiectiv_h_stanga );

            fprintf(f, "%s %.0f %s %.0f\n", "   Front : ", g_obiectiv.obiectiv_front[i], "    Adancime : ",   g_obiectiv.obiectiv_adancime[i]);
            fprintf(f, "%s %.0f %s %.0f minute\n", "    Consum : ",  g_obiectiv.obiectiv_norma_consum[i], "    Ciocan de foc : ", g_obiectiv.obiectiv_timp_ciocan_de_foc[i]);
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
            if(g_obiectiv.obiectiv_btno[i] == 0)
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
            fprintf(f, "     Foc de baraj\n");
            fprintf(f, "     Limita dreapta X = %.2f Y = %.2f \n", g_obiectiv.obiectiv_X_dreapta, g_obiectiv.obiectiv_Y_dreapta);
            fprintf(f, "        Limita stanga  X = %.2f Y = %.2f \n", g_obiectiv.obiectiv_X_stanga,  g_obiectiv.obiectiv_Y_stanga);
            fprintf(f, "        Altitudine : %.0f\n",  g_obiectiv.obiectiv_h_stanga );

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

            fprintf(f, "    Foc de baraj\n");
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

            if(g_obiectiv.obiectiv_p[i]<500)
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


        for(int i=0; i<3; ++i)
        {
            if(g_obiectiv.obiectiv_btno[i] == 0)
                continue ;


            time_t t ;
            time(&t);
            fprintf(f, "%s\n", "________________________________________________________________________________\n");
            fprintf(f, "    Bateria %d Artilerie          Data sistemului  : %s\n",i+1,  ctime(&t));
            fprintf(f, "%s\n", "   *Elemente topografice, elemente calculate, date si coeficienti de tragere*\n");


            fprintf(f, "    Foc de baraj\n");
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

                if(g_obiectiv.obiectiv_corectie_Bataie[i] >0)
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

        }

        fclose(f);
        chmod(file.c_str(), S_IREAD);
    }

    for(int i=0; i<3;i++)
    {
        g_obiectiv.obiectiv_btno[i] = 0 ;  //  aduce contul bateriilor la zero ;
    }
};

