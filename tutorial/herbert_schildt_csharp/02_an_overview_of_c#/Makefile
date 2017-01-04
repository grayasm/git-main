all: 01_a_first_simple_program \
     02_a_small_variation \
     03_a_second_simple_program \
     04_another_data_type

01_a_first_simple_program: 01_a_first_simple_program.cs Makefile
	mcs 01_a_first_simple_program.cs

02_a_small_variation: 02_a_small_variation.cs Makefile
	mcs 02_a_small_variation.cs

03_a_second_simple_program: 03_a_second_simple_program.cs Makefile
	mcs 03_a_second_simple_program.cs

04_another_data_type: 04_another_data_type.cs Makefile
	mcs 04_another_data_type.cs


clean:
	rm -v 01_a_first_simple_program.exe \
          02_a_small_variation.exe \
          03_a_second_simple_program.exe \
          04_another_data_type.exe
