all: 01_indexers \
     02_properties \
     03_accessors \
     04_using_indexers_and_properties


01_indexers: 01_indexers.cs Makefile
	mcs 01_indexers.cs

02_properties: 02_properties.cs Makefile
	mcs 02_properties.cs

03_accessors: 03_accessors.cs Makefile
	mcs 03_accessors.cs

04_using_indexers_and_properties: 04_using_indexers_and_properties.cs Makefile
	mcs 04_using_indexers_and_properties.cs


clean:
	rm -v 01_indexers.exe \
          02_properties.exe \
          03_accessors.exe \
          04_using_indexers_and_properties.exe
