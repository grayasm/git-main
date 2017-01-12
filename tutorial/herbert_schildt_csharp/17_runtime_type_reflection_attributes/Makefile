all: 01_runtime_type_identification \
     02_reflection \
     03_using_reflection \
     04_attributes \
     05_builtin_attributes


01_runtime_type_identification: 01_runtime_type_identification.cs Makefile
	mcs 01_runtime_type_identification.cs

02_reflection: 02_reflection.cs Makefile
	mcs 02_reflection.cs

03_using_reflection: 03_using_reflection.cs Makefile
	mcs 03_using_reflection.cs

04_attributes: 04_attributes.cs Makefile
	mcs 04_attributes.cs

05_builtin_attributes: 05_builtin_attributes.cs Makefile
	mcs 05_builtin_attributes.cs


clean:
	rm -v 01_runtime_type_identification.exe \
          02_reflection.exe \
          03_using_reflection.exe \
          04_attributes.exe \
          05_builtin_attributes.exe
