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



#include "structura_elementelor.h"


//c
//c++
//misc
#include "math.hpp"
//program
#include "artutil.h"



/* global variable */
structura_elementelor g_structura_elementelor;


structura_elementelor::structura_elementelor()
{
};

structura_elementelor::~structura_elementelor()
{
};


void structura_elementelor::structura_elementelor_date_initiale_tragere()
{
    //date catre motor_cautare_T_T
    int coloana_ref  ;
    float valoarea_ref ;
    int coloana_dor ;

    for(int i=0; i < 3; ++i)
    {

        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        g_tabla_tragere.tabla_tragere_incarca(i);


		SPolar objPolar = Util::rectangular(
			g_dispozitiv_de_lupta.dispozitivul_de_lupta_Xpt[i], 
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypt[i], 
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpt[i],
			g_obiectiv.obiectiv_X_obiectiv[i], 
			g_obiectiv.obiectiv_Y_obiectiv[i], 
			g_obiectiv.obiectiv_h_obiectiv[i],
			g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);


		g_obiectiv.obiectiv_Dt[i]		= objPolar.distanta ;
		g_obiectiv.obiectiv_delta_h[i]	= objPolar.deltah ;
		g_obiectiv.obiectiv_Mdt[i]		= objPolar.modificare_de_deriva ;
		g_obiectiv.obiectiv_gisment_obiectiv[i] = objPolar.gisment_final ;


        if(g_control_lucru.control_lucru_P_C == 1)
        {
            structura_elementelor_calculeaza_corectii(i);
        }
        else if(g_control_lucru.control_lucru_T_F == 1)
        {
            structura__elementelor_corectii_de_reglaj(i);
        }



        if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
        {

            //pt. 0 -> nu s-a produs depasirea graficului
            g_obiectiv.obiectiv_Dc[i] = g_obiectiv.obiectiv_Dt[i] + g_obiectiv.obiectiv_corectie_Bataie[i] ;

            coloana_ref = 0;
            valoarea_ref = g_obiectiv.obiectiv_Dc[i] ;
            coloana_dor = 1;

            g_obiectiv.obiectiv_Ic[i] = g_tabla_tragere.tabla_tragere_cautare(i, coloana_ref, valoarea_ref, coloana_dor);

            coloana_ref = 0;
            valoarea_ref = g_obiectiv.obiectiv_Dc[i] ;
            coloana_dor = 13;

            g_obiectiv.obiectiv_Niv[i] =  3000 +
                (g_obiectiv.obiectiv_delta_h[i]*(g_tabla_tragere.tabla_tragere_cautare(i, coloana_ref, valoarea_ref, coloana_dor)))/100 ;

            if(g_obiectiv.obiectiv_front[i] == 0)
            {
                g_obiectiv.obiectiv_fascicul[i] = 2 ;
            }
            else
            {
                g_obiectiv.obiectiv_fascicul[i] = g_obiectiv.obiectiv_front[i]/(g_obiectiv.obiectiv_Dt[i]*0.001*NRPIESE);
            }

            g_obiectiv.obiectiv_Mdc[i] = g_obiectiv.obiectiv_Mdt[i] + g_obiectiv.obiectiv_corectie_Directie[i] + (NRPIESE -1)*g_obiectiv.obiectiv_fascicul[i]/2 ;


            if(g_obiectiv.obiectiv_nr_directii[i] > -0.00000001 && g_obiectiv.obiectiv_nr_directii[i] < 0.00000001)
                ;
            else if(g_control_lucru.control_lucru_F_B == 1)
            {
                g_obiectiv.obiectiv_consum_piesa[i] = g_obiectiv.obiectiv_norma_consum[i]/(g_obiectiv.obiectiv_nr_directii[i]*NRPIESE);
            }
            else if(g_control_lucru.control_lucru_F_B == 0)
            {
                g_obiectiv.obiectiv_consum_piesa[i] = g_obiectiv.obiectiv_norma_consum[i]/(3*g_obiectiv.obiectiv_nr_directii[i]*NRPIESE);
            }

            if(g_obiectiv.obiectiv_norma_consum[i] != 0)
            {
                g_obiectiv.obiectiv_ritm_de_tragere[i] = ((g_obiectiv.obiectiv_timp_ciocan_de_foc[i] - 0.5)*60)/(g_obiectiv.obiectiv_norma_consum[i] - 16);
            }
            else
            {
                g_obiectiv.obiectiv_ritm_de_tragere[i] = 0 ;
            }
        }
    }
};

int structura_elementelor::structura_elementelor_calculeaza_corectii(int nr_baterie)
{

    char g[3] ;
    float cor_Bat_sup;
    float cor_Bat_inf;
    float cor_Dir_sup;
    float cor_Dir_inf;
    float G_local_deTrag[3];
    float G_local_obiectiv[3];


    //1) testarea limitei in distanta inf. si sup.
    //2) testarea gismentului in functie de lim. inf. si sup.

    if(g_obiectiv.obiectiv_GdeTrag[0] - g_obiectiv.obiectiv_GdeTrag[1] > 3000)
    {
        G_local_deTrag[0] =  g_obiectiv.obiectiv_GdeTrag[0] - 6000 ;
        G_local_deTrag[1] =  g_obiectiv.obiectiv_GdeTrag[1] ;
        G_local_deTrag[2] =  g_obiectiv.obiectiv_GdeTrag[2] ;
    }
    else if(g_obiectiv.obiectiv_GdeTrag[0] - g_obiectiv.obiectiv_GdeTrag[2] > 3000)
    {
        G_local_deTrag[0] =  g_obiectiv.obiectiv_GdeTrag[0] - 6000 ;
        G_local_deTrag[1] =  g_obiectiv.obiectiv_GdeTrag[1] - 6000 ;
        G_local_deTrag[2] =  g_obiectiv.obiectiv_GdeTrag[2] ;
    }
    else
    {
        G_local_deTrag[0] =  g_obiectiv.obiectiv_GdeTrag[0] ;
        G_local_deTrag[1] =  g_obiectiv.obiectiv_GdeTrag[1] ;
        G_local_deTrag[2] =  g_obiectiv.obiectiv_GdeTrag[2] ;
    }


    if((g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie] - G_local_deTrag[0] > 3000) ||
       (g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie] - G_local_deTrag[1] > 3000) ||
       (g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie] - G_local_deTrag[2] > 3000))
    {
        G_local_obiectiv[nr_baterie] = g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie] - 6000 ;
    }
    else
    {
        G_local_obiectiv[nr_baterie] = g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie] ;
    }


    for(int j=0, k=0, p=0; k<3; k++)
    {

        if((g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] > -0.00001) && (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] < 0.00001))
        {
            j++ ;
            continue ;
        }

        if(g_obiectiv.obiectiv_Dt[nr_baterie] <  g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k])
        {
            p = p+1 ;
        }

        if(p == 3)
        {

            printf("\n    ------------------------------------------------------------------------");
            printf("\n             EROARE DE INTRARE IN GRAFICUL CORECTIILOR CALCULATE ");
            printf("\n                         BATERIA %d ARTILERIE", nr_baterie+1 );
            printf("\n             Dist topo obv. = %.2f\n", g_obiectiv.obiectiv_Dt[nr_baterie]);

            //distante
            for(int m=0; m<4; m++)
            {
                //directii
                for(int n=0; n<3; n++)
                {
                    printf("\n             Pt.-> BT %d dist %d dir %d  DISTANTA TOPO = %.2f",
                           (nr_baterie+1), (m+1), (n+1), g_obiectiv.obiectiv_DdeTrag[nr_baterie][m][n]);
                }
            }

            getchar();

            g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] = 1;

            return 0;
        }
    }


    for(int j=3, k=0, p=0; k<3; k++)
    {
        if((g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] > -0.00001) && (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] < 0.00001))
        {
            j-- ;
            continue ;
        }

        if(g_obiectiv.obiectiv_Dt[nr_baterie] >  g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k])
        {
            p = p+1 ;
        }


        if(p == 3)
        {

            printf("\n    ------------------------------------------------------------------------");
            printf("\n             EROARE DE INTRARE IN GRAFICUL CORECTIILOR CALCULATE ");
            printf("\n                         BATERIA %d ARTILERIE", nr_baterie+1 );
            printf("\n             Dist topo obv. = %.2f\n",  g_obiectiv.obiectiv_Dt[nr_baterie]);

            //distante
            for(int m=0; m<4; m++)
            {
                //directii
                for(int n=0; n<3; n++)
                {
                    printf("\n             Pt.-> BT %d dist %d dir %d  DISTANTA TOPO = %.2f",
                           (nr_baterie+1), (m+1), (n+1), g_obiectiv.obiectiv_DdeTrag[nr_baterie][m][n]);
                }
            }

            getchar();

            g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] = 1;

            return 0;
        }
    }


    if(G_local_obiectiv[nr_baterie] < G_local_deTrag[0])
    {

        printf("\n    ------------------------------------------------------------------------");
        printf("\n              EROARE DE INTRARE IN GRAFIC BATERIA %d ARTILERIE", nr_baterie+1);
        printf("\n        Gismentul obiectivului = %.0f",  g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie]);
        printf("\n\n        Gismentul directiei 1  = %.0f", g_obiectiv.obiectiv_GdeTrag[0]);
        printf("\n        Gismentul directiei 2  = %.0f", g_obiectiv.obiectiv_GdeTrag[1]);
        printf("\n        Gismentul directiei 3  = %.0f", g_obiectiv.obiectiv_GdeTrag[2]);
        printf("\n    ------------------------------------------------------------------------");
        printf("\n\n        Doriti calcularea corectiilor cu valoarea ");
        printf("\n        G Obv.  = %.0f   (d/n) ? = ", (g_obiectiv.obiectiv_GdeTrag[0] + 1));



        g_control_lucru.control_lucru_getstdin(g, 3);

        if(g[0] == 'd' || g[0] == 'D')
        {        
            G_local_obiectiv[nr_baterie] = G_local_deTrag[0] + 1 ;
        }
        else
        {
            g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] = 1;
            return 0;
        }        
    }
    else if(G_local_obiectiv[nr_baterie] > G_local_deTrag[2])
    {

        printf("\n    ------------------------------------------------------------------------");
        printf("\n              EROARE DE INTRARE IN GRAFIC BATERIA %d ARTILERIE", nr_baterie+1);
        printf("\n        Gismentul obiectivului = %.0f",  g_obiectiv.obiectiv_gisment_obiectiv[nr_baterie]);
        printf("\n\n        Gismentul directiei 1  = %.0f", g_obiectiv.obiectiv_GdeTrag[0]);
        printf("\n        Gismentul directiei 2  = %.0f", g_obiectiv.obiectiv_GdeTrag[1]);
        printf("\n        Gismentul directiei 3  = %.0f", g_obiectiv.obiectiv_GdeTrag[2]);
        printf("\n    ------------------------------------------------------------------------");
        printf("\n\n        Doriti calcularea corectiilor cu valoarea ");
        printf("\n        G Obv.  = %.0f   (d/n) ? = ", (g_obiectiv.obiectiv_GdeTrag[2] - 1));


        g_control_lucru.control_lucru_getstdin(g, 3);



        if(g[0] == 'd' || g[0] == 'D')
        {
            G_local_obiectiv[nr_baterie] = G_local_deTrag[2] - 1 ;
        }
        else
        {
            g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] = 1;
            return 0;
        }
    }


    //distante
    for(int j=1; j < 4; ++j)
    {
        //directii
        for(int k=1; k < 3; ++k)
        {

            if(g_obiectiv.obiectiv_Dt[nr_baterie] <= g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] && G_local_obiectiv[nr_baterie] <=  G_local_deTrag[k])
            {           

                cor_Bat_sup = g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j][k] - (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] - g_obiectiv.obiectiv_Dt[nr_baterie])*
                    (g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j][k] - g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j-1][k])/
                    (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] - g_obiectiv.obiectiv_DdeTrag[nr_baterie][j-1][k]);

                cor_Bat_inf =  g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j][k-1] - (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k-1] - g_obiectiv.obiectiv_Dt[nr_baterie])*
                    (g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j][k-1] - g_obiectiv.obiectiv_corectii_calculate_bataie[nr_baterie][j-1][k-1])/
                    (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k-1] - g_obiectiv.obiectiv_DdeTrag[nr_baterie][j-1][k-1]);


                g_obiectiv.obiectiv_corectie_Bataie[nr_baterie] =  cor_Bat_sup - (G_local_deTrag[k] - G_local_obiectiv[nr_baterie])*
                    (cor_Bat_sup - cor_Bat_inf)/(G_local_deTrag[k] - G_local_deTrag[k-1]);


                cor_Dir_sup =  g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j][k] - (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] - g_obiectiv.obiectiv_Dt[nr_baterie])*
                    (g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j][k] - g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j-1][k])/
                    (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k] - g_obiectiv.obiectiv_DdeTrag[nr_baterie][j-1][k]);

                cor_Dir_inf =  g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j][k-1] - (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k-1] - g_obiectiv.obiectiv_Dt[nr_baterie])*
                    (g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j][k-1] - g_obiectiv.obiectiv_corectii_calculate_directie[nr_baterie][j-1][k-1])/
                    (g_obiectiv.obiectiv_DdeTrag[nr_baterie][j][k-1] - g_obiectiv.obiectiv_DdeTrag[nr_baterie][j-1][k-1]);


                g_obiectiv.obiectiv_corectie_Directie[nr_baterie] =   cor_Dir_sup - (G_local_deTrag[k] - G_local_obiectiv[nr_baterie])*
                    (cor_Dir_sup - cor_Dir_inf)/(G_local_deTrag[k] - G_local_deTrag[k-1]);



                return 1;
            }
        }
    }

    return 1;
};

int  structura_elementelor::structura__elementelor_corectii_de_reglaj(int nr_baterie)
{

    //date catre motor_cautare_T_T
    int coloana_ref  ;
    float valoarea_ref ;
    int coloana_dor ;

    float dZnou;
    float dZvechi;

    g_obiectiv.obiectiv_corectie_Bataie[nr_baterie] = g_obiectiv.obiectiv_Dt[nr_baterie] * g_conditii_balistice_transport_de_foc.coeficient_tragere[nr_baterie]/100 ;

    coloana_ref = 0;  valoarea_ref = g_obiectiv.obiectiv_Dt[nr_baterie] ; coloana_dor = 5;
    dZnou = g_tabla_tragere.tabla_tragere_cautare (nr_baterie, coloana_ref, valoarea_ref, coloana_dor);

    if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] == 1)
        return 0;

    valoarea_ref = g_conditii_balistice_transport_de_foc.distanta_topografica_reper_tragere[nr_baterie] ;
    dZvechi = g_tabla_tragere.tabla_tragere_cautare(nr_baterie, coloana_ref, valoarea_ref, coloana_dor);

    if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[nr_baterie] == 1)
        return 0;

    g_obiectiv.obiectiv_corectie_Directie[nr_baterie] = g_conditii_balistice_transport_de_foc.corectie_reglaj_directie[nr_baterie] +  dZnou - dZvechi ;

    return 1;
};

void structura_elementelor::structura_elementelor_coeficienti_si_date()
{

    //date catre motor_cautare_T_T
    int coloana_ref  ;
    float valoarea_ref ;
    int coloana_dor ;


    for(int i=0; i < 3; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        g_tabla_tragere.tabla_tragere_incarca(i);

        //  SE CALCULEAZA PENTRU PUNCTELE DE COMANDA-OBSERVARE ;

        SPolar objPolar = Util::rectangular(g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpco[i], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypco[i], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpco[i],
            g_obiectiv.obiectiv_X_obiectiv[i], 
            g_obiectiv.obiectiv_Y_obiectiv[i], 
            g_obiectiv.obiectiv_h_obiectiv[i],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);
              

        g_obiectiv.obiectiv_Do_pco[i] = objPolar.distanta;
        g_obiectiv.obiectiv_To_pco[i] =  objPolar.modificare_de_deriva ;



        //  calculeaza p;
        if(g_obiectiv.obiectiv_To_pco[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p[i] = g_obiectiv.obiectiv_To_pco[i] - g_obiectiv.obiectiv_Mdt[i] ;

            if(g_obiectiv.obiectiv_p[i] < 0)
            {
                g_obiectiv.obiectiv_p[i] = g_obiectiv.obiectiv_p[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_pco[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p[i] = g_obiectiv.obiectiv_To_pco[i] - g_obiectiv.obiectiv_Mdt[i] ;

            if(g_obiectiv.obiectiv_p[i] < 0)
            {
                g_obiectiv.obiectiv_p[i] = g_obiectiv.obiectiv_p[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_pco[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p[i] = (-1)*g_obiectiv.obiectiv_To_pco[i] + g_obiectiv.obiectiv_Mdt[i] ;
        }
        else if(g_obiectiv.obiectiv_To_pco[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p[i] = g_obiectiv.obiectiv_To_pco[i] + (-1)*g_obiectiv.obiectiv_Mdt[i] ;
        }


        //  SE CALCULEAZA PENTRU PUNCTELE DE OBSERVARE ;
        //  PUNCTUL DE OBSERVARE

        SPolar objPolar2 = Util::rectangular(g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[0], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[0], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[0],
            g_obiectiv.obiectiv_X_obiectiv[i], 
            g_obiectiv.obiectiv_Y_obiectiv[i], 
            g_obiectiv.obiectiv_h_obiectiv[i],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);


        g_obiectiv.obiectiv_Do_po[i] = objPolar2.distanta;
        g_obiectiv.obiectiv_To_po[i] =  objPolar2.modificare_de_deriva ;


        //  calculeaza p;
        if(g_obiectiv.obiectiv_To_po[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p_po[i] = g_obiectiv.obiectiv_To_po[i] - g_obiectiv.obiectiv_Mdt[i] ;
            if(g_obiectiv.obiectiv_p_po[i] < 0)
            {
                g_obiectiv.obiectiv_p_po[i] = g_obiectiv.obiectiv_p_po[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_po[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p_po[i] = g_obiectiv.obiectiv_To_po[i] - g_obiectiv.obiectiv_Mdt[i] ;
            if(g_obiectiv.obiectiv_p_po[i] < 0)
            {
                g_obiectiv.obiectiv_p_po[i] = g_obiectiv.obiectiv_p_po[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_po[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p_po[i] = (-1)*g_obiectiv.obiectiv_To_po[i] + g_obiectiv.obiectiv_Mdt[i] ;
        }
        else if(g_obiectiv.obiectiv_To_po[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p_po[i] = g_obiectiv.obiectiv_To_po[i] + (-1)*g_obiectiv.obiectiv_Mdt[i] ;
        }


        //  PUNCTUL DE OBSERVARE-LATERAL ;
        
        SPolar objPolar3 = Util::rectangular(g_dispozitiv_de_lupta.dispozitiv_de_lupta_Xpo[1], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Ypo[1], 
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_hpo[1],
            g_obiectiv.obiectiv_X_obiectiv[i], 
            g_obiectiv.obiectiv_Y_obiectiv[i], 
            g_obiectiv.obiectiv_h_obiectiv[i],
            g_dispozitiv_de_lupta.dispozitiv_de_lupta_Gdb);


        g_obiectiv.obiectiv_Do_pol[i] = objPolar3.distanta;
        g_obiectiv.obiectiv_To_pol[i] =  objPolar3.modificare_de_deriva ;


        //  calculeaza p;
        if(g_obiectiv.obiectiv_To_pol[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p_pol[i] = g_obiectiv.obiectiv_To_pol[i] - g_obiectiv.obiectiv_Mdt[i] ;
            if(g_obiectiv.obiectiv_p_pol[i] < 0)
            {
                g_obiectiv.obiectiv_p_pol[i] = g_obiectiv.obiectiv_p_pol[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_pol[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p_pol[i] = g_obiectiv.obiectiv_To_pol[i] - g_obiectiv.obiectiv_Mdt[i] ;
            if(g_obiectiv.obiectiv_p_pol[i] < 0)
            {
                g_obiectiv.obiectiv_p_pol[i] = g_obiectiv.obiectiv_p_pol[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_pol[i] <= 0 && g_obiectiv.obiectiv_Mdt[i] >= 0)
        {
            g_obiectiv.obiectiv_p_pol[i] = (-1)*g_obiectiv.obiectiv_To_pol[i] + g_obiectiv.obiectiv_Mdt[i] ;
        }
        else if(g_obiectiv.obiectiv_To_pol[i] >= 0 && g_obiectiv.obiectiv_Mdt[i] <= 0)
        {
            g_obiectiv.obiectiv_p_pol[i] = g_obiectiv.obiectiv_To_pol[i] + (-1)*g_obiectiv.obiectiv_Mdt[i] ;
        }

        //  SA CALCULEAZA GAMA ;
        if(g_obiectiv.obiectiv_To_po[i] >= 0 && g_obiectiv.obiectiv_To_pol[i] >= 0)
        {
            g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_p_po[i] - g_obiectiv.obiectiv_p_pol[i] ;
            if(g_obiectiv.obiectiv_gama[i] < 0)
            {
                g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_gama[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_po[i] <= 0 && g_obiectiv.obiectiv_To_pol[i] <= 0)
        {
            g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_p_po[i] - g_obiectiv.obiectiv_p_pol[i] ;
            if(g_obiectiv.obiectiv_gama[i] < 0)
            {
                g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_gama[i]*(-1);
            }
        }
        else if(g_obiectiv.obiectiv_To_po[i] <= 0 && g_obiectiv.obiectiv_To_pol[i] >= 0)
        {
            g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_p_po[i] + g_obiectiv.obiectiv_p_pol[i] ;
        }
        else if(g_obiectiv.obiectiv_To_po[i] >= 0 && g_obiectiv.obiectiv_To_pol[i] <= 0)
        {
            g_obiectiv.obiectiv_gama[i] = g_obiectiv.obiectiv_p_po[i] + g_obiectiv.obiectiv_p_pol[i] ;
        }


        if(g_obiectiv.obiectiv_gama[i] > -0.0000000000001 && g_obiectiv.obiectiv_gama[i] < 0.0000000000001)
        {
            g_obiectiv.obiectiv_gama[i] = 0.0000001 ;
        }

        g_obiectiv.obiectiv_Dpo_peGama[i] =  g_obiectiv.obiectiv_Do_po[i] / g_obiectiv.obiectiv_gama[i] ;
        g_obiectiv.obiectiv_Dpol_peGama[i] = g_obiectiv.obiectiv_Do_pol[i] / g_obiectiv.obiectiv_gama[i] ;

        if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
        {

            coloana_ref = 0;
            valoarea_ref = g_obiectiv.obiectiv_Dc[i] ;
            coloana_dor = 4;

            g_obiectiv.obiectiv_Apb[i] = g_tabla_tragere.tabla_tragere_cautare(i, coloana_ref, valoarea_ref, coloana_dor);

            coloana_dor = 3;
            g_obiectiv.obiectiv_dXmiime[i] = g_tabla_tragere.tabla_tragere_cautare(i, coloana_ref, valoarea_ref, coloana_dor);


            if(g_obiectiv.obiectiv_p[i] < 500)
            {
                g_obiectiv.obiectiv_Kd[i] =  g_obiectiv.obiectiv_Do_pco[i] / g_obiectiv.obiectiv_Dt[i] ;
                g_obiectiv.obiectiv_Sd[i] =  g_obiectiv.obiectiv_p[i] / (0.01*g_obiectiv.obiectiv_Dt[i]);
            }
            else
            {
                if( !(g_obiectiv.obiectiv_p[i] > -0.00001 && g_obiectiv.obiectiv_p[i] < 0.00001)  && !(g_obiectiv.obiectiv_p[i] > 2999.999999 && g_obiectiv.obiectiv_p[i] < 3000.000001))
                {
                    g_obiectiv.obiectiv_Kb[i] =  (g_obiectiv.obiectiv_Do_pco[i]*0.001)/(g_obiectiv.obiectiv_dXmiime[i]*(sin(g_obiectiv.obiectiv_p[i]*M2D*math::DEG2RAD)));
                }


                if( !(g_obiectiv.obiectiv_p[i] > 1499.99999 && g_obiectiv.obiectiv_p[i] < 1500.00001)  && !(g_obiectiv.obiectiv_p[i] > 4499.999999 && g_obiectiv.obiectiv_p[i] < 4500.000001))
                {
                    g_obiectiv.obiectiv_Ka[i] = (g_obiectiv.obiectiv_Dt[i]*0.001)/(g_obiectiv.obiectiv_dXmiime[i]*(tan(g_obiectiv.obiectiv_p[i]*M2D*math::DEG2RAD)));
                }
            }


            if(g_obiectiv.obiectiv_dXmiime[i] != 0)
            {
                g_obiectiv.obiectiv_furcuta[i] = 4*g_obiectiv.obiectiv_Apb[i]/g_obiectiv.obiectiv_dXmiime[i] ;
            }


            if(g_obiectiv.obiectiv_adancime[i] == 0 && g_obiectiv.obiectiv_Dc[i] <= ((30*g_tabla_tragere.tabla_tragere_v5[g_tabla_tragere.tabla_tragere_plafon-1][0])/100))
            {
                if(g_obiectiv.obiectiv_dXmiime[i] != 0)
                {
                    g_obiectiv.obiectiv_salt[i] =  4*g_obiectiv.obiectiv_Apb[i]/g_obiectiv.obiectiv_dXmiime[i] ;
                }

                g_obiectiv.obiectiv_val_salt_m[i] = 4*g_obiectiv.obiectiv_Apb[i] ;
            }
            else if(g_obiectiv.obiectiv_adancime[i] == 0 && g_obiectiv.obiectiv_Dc[i] <= ((60*g_tabla_tragere.tabla_tragere_v5[g_tabla_tragere.tabla_tragere_plafon-1][0])/100))
            {
                if(g_obiectiv.obiectiv_dXmiime[i] != 0)
                {
                    g_obiectiv.obiectiv_salt[i] =  3*g_obiectiv.obiectiv_Apb[i]/g_obiectiv.obiectiv_dXmiime[i] ;
                }

                g_obiectiv.obiectiv_val_salt_m[i] = 3*g_obiectiv.obiectiv_Apb[i] ;
            }
            else
            {
                if(g_obiectiv.obiectiv_dXmiime[i] != 0)
                {
                    g_obiectiv.obiectiv_salt[i] =  2*g_obiectiv.obiectiv_Apb[i]/g_obiectiv.obiectiv_dXmiime[i] ;
                }

                g_obiectiv.obiectiv_val_salt_m[i] = 2*g_obiectiv.obiectiv_Apb[i] ;
            }

            if(g_obiectiv.obiectiv_adancime[i] > 0)
            {
                if(g_obiectiv.obiectiv_dXmiime[i] != 0)
                {
                    g_obiectiv.obiectiv_salt[i] = (g_obiectiv.obiectiv_adancime[i]/3)/g_obiectiv.obiectiv_dXmiime[i] ;
                }

                g_obiectiv.obiectiv_val_salt_m[i] = g_obiectiv.obiectiv_adancime[i]/3 ;
            }
        }
    }
};

void structura_elementelor::afiseaza_date_initiale_tragere()
{

    for(int i=0; i < 3; ++i)
    {
        if(g_obiectiv.obiectiv_btno[i] == 0)
            continue ;

        //
        clrscr();
        printf("\n\n                            ELEMENTE DE TRAGERE");
        printf("\n    ------------------------------------------------------------------------");
        printf("\n                           BATERIA %d ARTILERIE", i+1);

        if( math::is_eq(g_tabla_tragere.tabla_tragere_incarcatura[i], 0.f) )
        {
            printf("\n\n                 Inc   Completa");
        }
        else
        {
            printf("\n\n                 Inc = %.0f", g_tabla_tragere.tabla_tragere_incarcatura[i]);
        }

        printf("\n                 Dt  = %.2f", g_obiectiv.obiectiv_Dt[i]);

        if(g_obiectiv.obiectiv_delta_h[i] > 0)
        {
            printf("\n                 dh  = + %.2f", g_obiectiv.obiectiv_delta_h[i]);
        }
        else
        {
            printf("\n                 dh  = %.2f", g_obiectiv.obiectiv_delta_h[i]);
        }


        if(g_obiectiv.obiectiv_Mdt[i] > 0)
        {
            printf("\n                 Mdt = + %.0f", g_obiectiv.obiectiv_Mdt[i]);
        }
        else
        {
            printf("\n                 Mdt = %.0f", g_obiectiv.obiectiv_Mdt[i]);
        }


        if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
        {

            if(g_obiectiv.obiectiv_corectie_Bataie[i] > 0)
            {
                printf("\n                 dD  = + %.2f", g_obiectiv.obiectiv_corectie_Bataie[i]);
            }
            else
            {
                printf("\n                 dD  = %.2f", g_obiectiv.obiectiv_corectie_Bataie[i]);
            }


            printf("\n                 Dc  = %.2f", g_obiectiv.obiectiv_Dc[i]);
            printf("\n                 Ic  = %.0f", g_obiectiv.obiectiv_Ic[i]);

            if(g_control_lucru.control_lucru_F_B == 0)
            {
                printf("\n                 salt= %.0f (%.2f m)", g_obiectiv.obiectiv_salt[i], g_obiectiv.obiectiv_val_salt_m[i]);
            }

            printf("\n                 Niv = %.0f", g_obiectiv.obiectiv_Niv[i]);

            if(g_obiectiv.obiectiv_corectie_Directie[i] > 0)
            {
                printf("\n                 ddir= + %.0f", g_obiectiv.obiectiv_corectie_Directie[i]);
            }
            else
            {
                printf("\n                 ddir= %.0f", g_obiectiv.obiectiv_corectie_Directie[i]);
            }


            if(g_obiectiv.obiectiv_Mdc[i] > 0)
            {
                printf("\n                 Mdc = + %.0f", g_obiectiv.obiectiv_Mdc[i]);
            }
            else
            {
                printf("\n                 Mdc = %.0f", g_obiectiv.obiectiv_Mdc[i]);
            }


            printf("\n                 f   = %.0f", g_obiectiv.obiectiv_fascicul[i]);
            printf("\n                 nr_directii  = %.0f", g_obiectiv.obiectiv_nr_directii[i]);
            printf("\n                 consum piesa = %.0f", g_obiectiv.obiectiv_consum_piesa[i]);

            if(g_obiectiv.obiectiv_norma_consum[i] == 0)
            {
                printf("\n                 vijelie INCARCATI (FOC!)");
            }
            else if(g_obiectiv.obiectiv_norma_consum[i] > 0)
            {
                printf("\n                 ritm  = %.0f sec.", g_obiectiv.obiectiv_ritm_de_tragere[i]);
            }
        }

        printf("\n    ------------------------------------------------------------------------");
        getchar();

        //
        clrscr();
        printf("\n                           DATE SI COEFICIENTI");
        printf("\n    ------------------------------------------------------------------------");
        printf("\n                          BATERIA %d ARTILERIE", i+1);
        printf("\n\n                 Do   = %.2f", g_obiectiv.obiectiv_Do_pco[i]);

        if(g_obiectiv.obiectiv_To_pco[i] > 0)
        {
            printf("\n                 To   = + %.0f", g_obiectiv.obiectiv_To_pco[i]);
        }
        else
        {
            printf("\n                 To   = %.0f", g_obiectiv.obiectiv_To_pco[i]);
        }

        printf("\n                 p    = %.0f", g_obiectiv.obiectiv_p[i]);


        if(g_obiectiv.obiectiv_p[i] < 500)
        {
            printf("\n                 Kd   = %.2f", g_obiectiv.obiectiv_Kd[i]);
            printf("\n                 Sd   = %.0f", g_obiectiv.obiectiv_Sd[i]);
        }
        else
        {
            printf("\n                 Kb   = %.2f", g_obiectiv.obiectiv_Kb[i]);
            printf("\n                 Ka   = %.2f", g_obiectiv.obiectiv_Ka[i]);
        }

        printf("\n\n                 Do(PODn) = %.2f", g_obiectiv.obiectiv_Do_po[i]);

        if(g_obiectiv.obiectiv_To_po[i] > 0)
        {
            printf("\n                 To(PODn) = + %.0f", g_obiectiv.obiectiv_To_po[i]);
        }
        else
        {
            printf("\n                 To(PODn) = %.0f", g_obiectiv.obiectiv_To_po[i]);
        }

        printf("\n                 p(PODn)  = %.0f",  g_obiectiv.obiectiv_p_po[i]);
        printf("\n                 Do(POL)  = %.2f", g_obiectiv.obiectiv_Do_pol[i]);

        if(g_obiectiv.obiectiv_To_pol[i] > 0)
        {
            printf("\n                 To(POL)  = + %.0f", g_obiectiv.obiectiv_To_pol[i]);
        }
        else
        {
            printf("\n                 To(POL)  = %.0f", g_obiectiv.obiectiv_To_pol[i]);
        }


        printf("\n                 p(POL)   = %.0f",  g_obiectiv.obiectiv_p_pol[i]);
        printf("\n                 gama     = %.1f", g_obiectiv.obiectiv_gama[i]);
        printf("\n                 Do(PODn)/gama = %.1f", g_obiectiv.obiectiv_Dpo_peGama[i]);
        printf("\n                 Do(POL)/gama  = %.1f", g_obiectiv.obiectiv_Dpol_peGama[i]);

        if(g_control_lucru.control_lucru_intrerupe_calcul_depasire_limite[i] == 0)
        {
            printf("\n\n                 furcuta  = %.0f", g_obiectiv.obiectiv_furcuta[i]);
            printf("\n                 Apb      = %.0f", g_obiectiv.obiectiv_Apb[i]);
            printf("\n                 dXmiime  = %.0f", g_obiectiv.obiectiv_dXmiime[i]);
        }

        printf("\n    ------------------------------------------------------------------------");
        getchar();
    }
};


void structura_elementelor::structura_elementelor_control()
{
    structura_elementelor_date_initiale_tragere();

    structura_elementelor_coeficienti_si_date();

    afiseaza_date_initiale_tragere();
};
