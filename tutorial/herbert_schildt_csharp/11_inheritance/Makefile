all: 01_inheritance_basics \
     02_restricted_private_access \
     03_access_to_private_members \
     04_using_protected_access \
     05_constructors_and_inheritance \
     06_call_base_class_constructor \
     07_call_implicit_base_ctor \
     08_member_hidding \
     09_access_hidden_member \
     10_access_hidden_method \
     11_multilevel_hierarchy \
     12_order_of_construction \
     13_reference_to_another_type \
     14_reference_to_derived_type \
     15_use_derived_as_reference_to_base \
     16_overriding_virtual_methods \
     17_virtual_not_overridden \
     18_overriding_in_a_multilevel \
     19_polymorphism \
     20_abstract_classes \
     21_sealed_class \
     22_sealed_method \
     23_the_object_class \
     24_boxing_and_unboxing \
     25_boxing_on_passing_values \
     26_call_methods_on_boxed_value \
     27_object_universal_data_type


01_inheritance_basics: 01_inheritance_basics.cs Makefile
	mcs 01_inheritance_basics.cs

02_restricted_private_access: 02_restricted_private_access.cs Makefile
	#mcs 02_restricted_private_access.cs
	echo "02_restricted_private_access.cs(37,16): error CS0122: 'TwoDShape.Width' is inaccessible due to its protection level"
	echo "02_restricted_private_access.cs(37,24): error CS0122: 'TwoDShape.Height' is inaccessible due to its protection level"
	echo "error CS5001: Program '02_restricted_private_access.exe' does not contain a static 'Main' method suitable for an entry point"


03_access_to_private_members: 03_access_to_private_members.cs Makefile
	mcs 03_access_to_private_members.cs

04_using_protected_access: 04_using_protected_access.cs Makefile
	mcs 04_using_protected_access.cs

05_constructors_and_inheritance: 05_constructors_and_inheritance.cs Makefile
	mcs 05_constructors_and_inheritance.cs

06_call_base_class_constructor: 06_call_base_class_constructor.cs Makefile
	mcs 06_call_base_class_constructor.cs

07_call_implicit_base_ctor: 07_call_implicit_base_ctor.cs Makefile
	mcs 07_call_implicit_base_ctor.cs

08_member_hidding: 08_member_hidding.cs Makefile
	mcs 08_member_hidding.cs

09_access_hidden_member: 09_access_hidden_member.cs Makefile
	mcs 09_access_hidden_member.cs

10_access_hidden_method: 10_access_hidden_method.cs Makefile
	mcs 10_access_hidden_method.cs

11_multilevel_hierarchy: 11_multilevel_hierarchy.cs Makefile
	mcs 11_multilevel_hierarchy.cs

12_order_of_construction: 12_order_of_construction.cs Makefile
	mcs 12_order_of_construction.cs

13_reference_to_another_type: 13_reference_to_another_type.cs Makefile
	#mcs 13_reference_to_another_type.cs
	echo "13_reference_to_another_type.cs(35,14): error CS0029: Cannot implicitly convert type 'Y' to 'X'"

14_reference_to_derived_type: 14_reference_to_derived_type.cs Makefile
	mcs 14_reference_to_derived_type.cs

15_use_derived_as_reference_to_base: 15_use_derived_as_reference_to_base.cs Makefile
	mcs 15_use_derived_as_reference_to_base.cs

16_overriding_virtual_methods: 16_overriding_virtual_methods.cs Makefile
	mcs 16_overriding_virtual_methods.cs

17_virtual_not_overridden: 17_virtual_not_overridden.cs Makefile
	mcs 17_virtual_not_overridden.cs

18_overriding_in_a_multilevel: 18_overriding_in_a_multilevel.cs Makefile
	mcs 18_overriding_in_a_multilevel.cs

19_polymorphism: 19_polymorphism.cs Makefile
	mcs 19_polymorphism.cs

20_abstract_classes: 20_abstract_classes.cs Makefile
	mcs 20_abstract_classes.cs

21_sealed_class: 21_sealed_class.cs Makefile
	#mcs 21_sealed_class.cs
	echo "21_sealed_class.cs(20,7): error CS0509: 'B': cannot derive from sealed type 'A'"

22_sealed_method: 22_sealed_method.cs Makefile
	#mcs 22_sealed_method.cs
	echo "22_sealed_method.cs(23,26): error CS0239: 'X.MyMethod()': cannot override inherited member 'D.MyMethod()' because it is sealed"

23_the_object_class: 23_the_object_class.cs Makefile
	mcs 23_the_object_class.cs

24_boxing_and_unboxing: 24_boxing_and_unboxing.cs Makefile
	mcs 24_boxing_and_unboxing.cs

25_boxing_on_passing_values: 25_boxing_on_passing_values.cs Makefile
	mcs 25_boxing_on_passing_values.cs

26_call_methods_on_boxed_value: 26_call_methods_on_boxed_value.cs Makefile
	mcs 26_call_methods_on_boxed_value.cs

27_object_universal_data_type: 27_object_universal_data_type.cs Makefile
	mcs 27_object_universal_data_type.cs


clean:
	rm -v 01_inheritance_basics.exe \
          02_restricted_private_access.exe \
          03_access_to_private_members.exe \
          04_using_protected_access.exe \
          05_constructors_and_inheritance.exe \
          06_call_base_class_constructor.exe \
          07_call_implicit_base_ctor.exe \
          08_member_hidding.exe \
          09_access_hidden_member.exe \
          10_access_hidden_method.exe \
          11_multilevel_hierarchy.exe \
          12_order_of_construction.exe \
          13_reference_to_another_type.exe \
          14_reference_to_derived_type.exe \
          15_use_derived_as_reference_to_base.exe \
          16_overriding_virtual_methods.exe \
          17_virtual_not_overridden.exe \
          18_overriding_in_a_multilevel.exe \
          19_polymorphism.exe \
          20_abstract_classes.exe \
          21_sealed_class.exe \
          22_sealed_method.exe \
          23_the_object_class.exe \
          24_boxing_and_unboxing.exe \
          25_boxing_on_passing_values.exe \
          26_call_methods_on_boxed_value.exe \
          27_object_universal_data_type.exe
