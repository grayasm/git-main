all: 01_unsafe \
     02_fixed \
     03_pointer_arithmetic \
     04_pointer_to_array \
     05_indexing_a_pointer \
     06_pointer_to_string \
     07_pointer_to_pointer \
     08_stackalloc \
     09_nullable_type \
     10_nullable_in_expressions \
     11_the_null_coalescing_operator \
     12_partial_type \
     13_partial_methods \
     14_dynamic_type \
     15_MyClass \
     15_MyDynamic \
     16_readonly \
     17_using \
     18_test1 \
     18_test2 \
     18_extern_Assembly_Alias


01_unsafe: 01_unsafe.cs Makefile
	mcs -unsafe 01_unsafe.cs

02_fixed: 02_fixed.cs Makefile
	mcs -unsafe 02_fixed.cs

03_pointer_arithmetic: 03_pointer_arithmetic.cs Makefile
	mcs -unsafe 03_pointer_arithmetic.cs

04_pointer_to_array: 04_pointer_to_array.cs Makefile
	mcs -unsafe 04_pointer_to_array.cs

05_indexing_a_pointer: 05_indexing_a_pointer.cs Makefile
	mcs -unsafe 05_indexing_a_pointer.cs

06_pointer_to_string: 06_pointer_to_string.cs Makefile
	mcs -unsafe 06_pointer_to_string.cs

07_pointer_to_pointer: 07_pointer_to_pointer.cs Makefile
	mcs -unsafe 07_pointer_to_pointer.cs

08_stackalloc: 08_stackalloc.cs Makefile
	mcs -unsafe 08_stackalloc.cs

09_nullable_type: 09_nullable_type.cs Makefile
	mcs 09_nullable_type.cs

10_nullable_in_expressions: 10_nullable_in_expressions.cs Makefile
	mcs 10_nullable_in_expressions.cs

11_the_null_coalescing_operator: 11_the_null_coalescing_operator.cs Makefile
	mcs 11_the_null_coalescing_operator.cs

12_partial_type: 12_partial_type.cs Makefile
	mcs 12_partial_type.cs

13_partial_methods: 13_partial_methods.cs Makefile
	mcs 13_partial_methods.cs

14_dynamic_type: 14_dynamic_type.cs Makefile
	mcs 14_dynamic_type.cs

15_MyClass: 15_MyClass.cs Makefile
	mcs /t:library 15_MyClass.cs

15_MyDynamic: 15_MyDynamic.cs Makefile
	mcs 15_MyDynamic.cs

16_readonly: 16_readonly.cs Makefile
	mcs 16_readonly.cs

17_using: 17_using.cs Makefile
	mcs 17_using.cs

18_test1: 18_test1.cs Makefile
	mcs /t:library 18_test1.cs

18_test2: 18_test2.cs Makefile
	mcs /t:library 18_test2.cs

18_extern_Assembly_Alias: 18_extern_Assembly_Alias.cs Makefile
	mcs /r:Asm1=18_test1.dll /r:Asm2=18_test2.dll 18_extern_Assembly_Alias.cs



clean:
	rm -v 01_unsafe.exe \
          02_fixed.exe \
          03_pointer_arithmetic.exe \
          04_pointer_to_array.exe \
          05_indexing_a_pointer.exe \
          06_pointer_to_string.exe \
          07_pointer_to_pointer.exe \
          08_stackalloc.exe \
          09_nullable_type.exe \
          10_nullable_in_expressions.exe \
          11_the_null_coalescing_operator.exe \
          12_partial_type.exe \
          13_partial_methods.exe \
          14_dynamic_type.exe \
          15_MyClass.dll \
          15_MyDynamic.exe \
          16_readonly.exe \
          17_using.exe \
          18_extern_Assembly_Alias.exe \
          18_test1.dll \
          18_test2.dll
