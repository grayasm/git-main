all: 01_namespace \
     02_namespace_conflict \
     03_using \
     04_using_alias \
     05_namespace_additive \
     06_namespace_nested \
     07_double_colon_qualifier \
     08_global_alias \
     09_preprocessor_define \
     10_preprocessor_if \
     11_preprocessor_else \
     12_preprocessor_elif \
     13_access_modifier_internal


01_namespace: 01_namespace.cs Makefile
	mcs 01_namespace.cs

02_namespace_conflict: 02_namespace_conflict.cs Makefile
	mcs 02_namespace_conflict.cs

03_using: 03_using.cs Makefile
	mcs 03_using.cs

04_using_alias: 04_using_alias.cs Makefile
	mcs 04_using_alias.cs

05_namespace_additive: 05_namespace_additive.cs Makefile
	mcs 05_namespace_additive.cs

06_namespace_nested: 06_namespace_nested.cs Makefile
	mcs 06_namespace_nested.cs

07_double_colon_qualifier: 07_double_colon_qualifier.cs Makefile
	mcs 07_double_colon_qualifier.cs

08_global_alias: 08_global_alias.cs Makefile
	mcs 08_global_alias.cs

09_preprocessor_define: 09_preprocessor_define.cs Makefile
	mcs 09_preprocessor_define.cs

10_preprocessor_if: 10_preprocessor_if.cs Makefile
	mcs 10_preprocessor_if.cs

11_preprocessor_else: 11_preprocessor_else.cs Makefile
	mcs 11_preprocessor_else.cs

12_preprocessor_elif: 12_preprocessor_elif.cs Makefile
	mcs 12_preprocessor_elif.cs

13_access_modifier_internal: 13_access_modifier_internal.cs Makefile
	mcs 13_access_modifier_internal.cs


clean:
	rm -v 01_namespace.exe \
          02_namespace_conflict.exe \
          03_using.exe \
          04_using_alias.exe \
          05_namespace_additive.exe \
          06_namespace_nested.exe \
          07_double_colon_qualifier.exe \
          08_global_alias.exe \
          09_preprocessor_define.exe \
          10_preprocessor_if.exe \
          11_preprocessor_else.exe \
          12_preprocessor_elif.exe \
          13_access_modifier_internal.exe
