
#include <time.h>

#include "stream.hpp"
#include "Varianta.hpp"
#include "Combinatie.hpp"
#include "Extrageri.hpp"
#include "Statistica.hpp"
#include "Filtru.hpp"
#include "Aleator.hpp"
#include "Rhino.hpp"


int main(int argc, char** argv)
{	
	//citeste extragerile din fisier
	Extrageri extrageri;
	misc::ifstream input("c:\\tmp\\000extrageri.txt");
	if(input.is_open())
	{
		input >> extrageri;
	}



	//////////////////////////////////////////////////////////////////////////
	{
		//statistici pe extragerile actuale
		Statistica::MapaAparitii mapa_aparitii;
		Statistica::NumarAparitii(((const Extrageri&)extrageri).GetArrayBegin(), ((const Extrageri&)extrageri).GetArrayEnd(), mapa_aparitii);
		misc::ofstream faparitii("c:\\tmp\\001aparitii.txt");
		faparitii << mapa_aparitii ;
		faparitii.close();

		//statistica pe extrageri : scrie numerele in ordinea descrescatoare a aparitiilor
		misc::ofstream ftopdownstream("c:\\tmp\\002aparitii_desc.txt");
		Statistica::Write(ftopdownstream, mapa_aparitii, Statistica::WM_TOP_DOWN);
		ftopdownstream.close();


		//statistica pe extrageri : scrie numerele in ordinea crescatoare a aparitiilor
		misc::ofstream fdowntopstream("c:\\tmp\\003aparitii_cresc.txt");
		Statistica::Write(fdowntopstream, mapa_aparitii, Statistica::WM_DOWN_TOP);
		fdowntopstream.close();
	}
	//////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////

	//alegere numere
	misc::cout << "Loterie" << std::endl;
	Combinatie::Numbers numere;

	misc::cout << "Am ales numerele: ";

	size_t nr_generate = 8;
	size_t min = 1, max = 49;
	numere = Aleator::Generate(nr_generate, min, max);

	for(size_t i=0; i<nr_generate; ++i)
		misc::cout << numere[i] << " ";
	misc::cout << std::endl;



	//creaza toate combinatiile posibile de 'numere' luate cate 7
	Combinatie comb(numere, 7);
	Combinatie::Numbers sortedNum = comb.GetNumbers();

	{
		//check returned result
		if(sortedNum.size() != numere.size())
			throw misc::exception("numbers doesn't match!");
		for(size_t i=0; i<sortedNum.size(); ++i)
			if( std::find(numere.begin(), numere.end(), sortedNum[i]) == numere.end() )
				throw misc::exception("numbers doesn't match!");


		misc::ofstream file("c:\\tmp\\004combinatie.txt", std::ios_base::trunc);
		if( !file.is_open() )  return 0;

		file << "#Numere alese : ";
		for(size_t i = 0; i<sortedNum.size(); i++) file << misc::from_value(sortedNum[i]).c_str() << " " ;
		file << "\n#In total s-au ales : " << sortedNum.size() << " numere";
		file << "\n#In total sunt " << comb.GetSize() << " combinatii";
		file << "\n#Combinatiile sunt urmatoarele : \n" ;

		file << comb ;
		file.close();
	}
	//////////////////////////////////////////////////////////////////////////

	



	//////////////////////////////////////////////////////////////////////////
	{
		//filtreaza datele pentru a reduce variantele la un numar convenabil	
		Combinatie::Array combinatii = comb.GetArray();
		Filtru::Numere preferentiale;


		//StergeConsecutive(comb, interval, consecutive, preferentiale);

		//  41  42  43
		Filtru::StergeConsecutive(combinatii, 1, 3, preferentiale);		

		//  22 24 26
		Filtru::StergeConsecutive(combinatii, 2, 3, preferentiale);

		//  30  33  36
		Filtru::StergeConsecutive(combinatii, 3, 4, preferentiale);

		//  20  24  28
		Filtru::StergeConsecutive(combinatii, 4, 5, preferentiale);

		//
		Combinatie::Array combinatii2 = combinatii;	
		//preferentiale = Aleator::Generate(2, 40, 49);

		Filtru::StergeIdenticeCrescator(combinatii, 3, preferentiale);
		Filtru::StergeIdenticeAleator(combinatii2, 3, preferentiale);

	}
	//////////////////////////////////////////////////////////////////////////
	
	

	
	//pregatire pentru statistica
	Extrageri::Array variante = extrageri.GetArray();

	{//probabilitati nr. pare si impare in toate extragerile din baza de date
		size_t gasite[7];
		size_t total[7];
		double prob_pare[7];
		double prob_impare[7];
		for(size_t i=1; i<=7; ++i)
		{		
			Statistica::NumerePare(variante.begin(), variante.end(), i, i, gasite[i-1], total[i-1]);
			prob_pare[i-1] = (double) gasite[i-1] / (double) total[i-1];

			Statistica::NumereImpare(variante.begin(), variante.end(), i, i, gasite[i-1], total[i-1]);
			prob_impare[i-1] = (double) gasite[i-1] / (double) total[i-1];
		}//for

		gasite[0]=0;//break;

		/*
		prob. pt 3 nr pare + prob. pt 3 nr impare = 1 :)
		*/
	}
	

	
	{//in cate variante apar numere "nrpref" (1,2)
		size_t gasite;
		size_t total;	
		unsigned short nrpref[2] = {1,2};
		Varianta preferentiale(Varianta::Array(nrpref, nrpref+2));
		Statistica::NumerePreferentiale(variante.begin(), variante.end(), preferentiale, gasite, total);
		double prob = (double) gasite / (double) total;
		prob += 0.;//break;
	}




	{//se creaza grafic in format Rhino pentru fiecare nr. [1,49] si probabilitatea aparitiei pe cate 50 extrageri
		//de la primul set [0,49] pana la ultimul set [sz-set,sz]

		misc::ofstream out(U("c:\\tmp\\rhino_1.log"), std::ios_base::trunc | std::ios_base::out);
		Rhino log;
		int clr[3]={0, 0, 0};

		//pentru fiecare numar posibil a fi extras
		for(unsigned short nr = 1; nr < 50; ++nr)
		{
			std::vector<Pt3d> pt3dArray;
			const size_t set = 10;//se foloseste setul de x extrageri consecutive pt analiza probabilitatii
			size_t sz = variante.size();
			if(sz < set)
				throw misc::exception("not possible");

			//mark on this layer, with small circles the positions where current numbers was extracted
			std::vector<Circle> circArray;


			for(size_t i=0; i<sz-set+1; ++i)
			{
				Extrageri::Array::const_iterator beg = variante.begin();
				std::advance(beg, i);
				Extrageri::Array::const_iterator end = beg;
				std::advance(end, set);

				size_t gasite;
				size_t total;					
				Varianta preferentiale(Varianta::Array(1, nr));
				Statistica::NumerePreferentiale(beg, end, preferentiale, gasite, total);
				float prob = (float) gasite / (float) total;
				pt3dArray.push_back(Pt3d((float)i, (float)nr, (float)gasite));


				//calculate circle position, if true
				Extrageri::Array::const_iterator Ite = end;
				--Ite;

				const Varianta::Array& varray = (*Ite).GetArray();
				if(std::find(varray.begin(), varray.end(), nr) != varray.end())
				{
					Pt3d p1((float)i, (float)nr, (float)gasite+0.5f);
					Pt3d p2((float)i-0.5f, (float)nr, (float)gasite);
					Pt3d p3((float)i, (float)nr, (float)gasite-0.5f);
					circArray.push_back(Circle(p1,p2,p3));
				}
			}//for(i)

			//logare format Rhino
			misc::string layout("nr_");
			layout += misc::from_value(nr);
			log.Log(out, layout, clr, pt3dArray );
			log.Log(out, layout, clr, circArray);
		}//for(nr)	
		
		out.close();
	}




	return 0;
}
