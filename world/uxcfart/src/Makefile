all: uxcfart

debug = -g -O0

includes = -I. -I../../../lib/misc/src -I../../../lib/cad/src

cflags = -Wall

cxxflags = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC

sources = buletin_meteo.cpp caroiaj.cpp  cfdnart.cpp citire_distanta.cpp \
	conditii_balistice_transport_de_foc.cpp conditii_meteo_balistice.cpp \
	conducerea_focului.cpp control_lucru.cpp dispozitiv_de_lupta.cpp \
	foc_de_baraj.cpp gisment_distanta.cpp harta_codificata.cpp obiectiv.cpp \
	observare_conjugata.cpp pregatire_completa.cpp rectangular.cpp \
	structura_elementelor.cpp tabla_tragere.cpp transport_de_foc.cpp \
	artutil.cpp

libs = -L. -L../../../lib/misc/src -lm  libmisc.a


uxcfart: $(sources)
	g++ -o uxcfart $(sources) $(debug) $(includes) $(cflags) $(cxxflags) $(libs)

clean:
	rm -v uxcfart
