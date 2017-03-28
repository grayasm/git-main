all: 01_runtime_is \
     02_runtime_as \
     03_runtime_typeof \
     04_reflection_methods_info \
     05_reflection_methods_invoke \
     06_reflection_constructor_invoke \
     07_MyClasses \
     08_reflection_MyClasses_known \
     09_reflection_MyClasses_unknown \
     10_attribute_builtin_AttributeUsage \
     11_attribute_parameter \
     12_attribute_property \
     13_attribute_builtin_Conditional \
     14_attribute_builtin_Obsolete


01_runtime_is: 01_runtime_is.cs Makefile
	mcs 01_runtime_is.cs

02_runtime_as: 02_runtime_as.cs Makefile
	mcs 02_runtime_as.cs

03_runtime_typeof: 03_runtime_typeof.cs Makefile
	mcs 03_runtime_typeof.cs

04_reflection_methods_info: 04_reflection_methods_info.cs Makefile
	mcs 04_reflection_methods_info.cs

05_reflection_methods_invoke: 05_reflection_methods_invoke.cs Makefile
	mcs 05_reflection_methods_invoke.cs

06_reflection_constructor_invoke: 06_reflection_constructor_invoke.cs Makefile
	mcs 06_reflection_constructor_invoke.cs

07_MyClasses: 07_MyClasses.cs Makefile
	mcs 07_MyClasses.cs

08_reflection_MyClasses_known: 08_reflection_MyClasses_known.cs Makefile
	mcs 08_reflection_MyClasses_known.cs

09_reflection_MyClasses_unknown: 09_reflection_MyClasses_unknown.cs Makefile
	mcs 09_reflection_MyClasses_unknown.cs

10_attribute_builtin_AttributeUsage: 10_attribute_builtin_AttributeUsage.cs Makefile
	mcs 10_attribute_builtin_AttributeUsage.cs

11_attribute_parameter: 11_attribute_parameter.cs Makefile
	mcs 11_attribute_parameter.cs

12_attribute_property: 12_attribute_property.cs Makefile
	mcs 12_attribute_property.cs

13_attribute_builtin_Conditional: 13_attribute_builtin_Conditional.cs Makefile
	mcs 13_attribute_builtin_Conditional.cs

14_attribute_builtin_Obsolete: 14_attribute_builtin_Obsolete.cs Makefile
	mcs 14_attribute_builtin_Obsolete.cs


clean:
	rm -v 01_runtime_is.exe \
          02_runtime_as.exe \
          03_runtime_typeof.exe \
          04_reflection_methods_info.exe \
          05_reflection_methods_invoke.exe \
          06_reflection_constructor_invoke.exe \
          07_MyClasses.exe \
          08_reflection_MyClasses_known.exe \
          09_reflection_MyClasses_unknown.exe \
          10_attribute_builtin_AttributeUsage.exe \
          11_attribute_parameter.exe \
          12_attribute_property.exe \
          13_attribute_builtin_Conditional.exe \
          14_attribute_builtin_Obsolete.exe
