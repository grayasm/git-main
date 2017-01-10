all: 01_namespaces \
     02_preprocessor \
     03_assemblies


01_namespaces: 01_namespaces.cs Makefile
	mcs 01_namespaces.cs

02_preprocessor: 02_preprocessor.cs Makefile
	mcs 02_preprocessor.cs

03_assemblies: 03_assemblies.cs Makefile
	mcs 03_assemblies.cs


clean:
	rm -v 01_namespaces.exe \
          02_preprocessor.exe \
          03_assemblies.exe
