all: 01_one_dimensional_indexer \
     02_indexer_overloading \
     03_example_indexer_without_array \
     04_multidimensional_indexer \
     05_properties \
     06_example_readonly_property \
     07_autoimplemented_properties \
     08_private_accessor \
     09_example_readonly_autoimpl_props \
     10_example_indexers_and_properties


01_one_dimensional_indexer: 01_one_dimensional_indexer.cs Makefile
	mcs 01_one_dimensional_indexer.cs

02_indexer_overloading: 02_indexer_overloading.cs Makefile
	mcs 02_indexer_overloading.cs

03_example_indexer_without_array: 03_example_indexer_without_array.cs Makefile
	mcs 03_example_indexer_without_array.cs

04_multidimensional_indexer: 04_multidimensional_indexer.cs Makefile
	mcs 04_multidimensional_indexer.cs

05_properties: 05_properties.cs Makefile
	mcs 05_properties.cs

06_example_readonly_property: 06_example_readonly_property.cs Makefile
	mcs 06_example_readonly_property.cs

07_autoimplemented_properties: 07_autoimplemented_properties.cs Makefile
	mcs 07_autoimplemented_properties.cs

08_private_accessor: 08_private_accessor.cs Makefile
	mcs 08_private_accessor.cs

09_example_readonly_autoimpl_props: 09_example_readonly_autoimpl_props.cs Makefile
	mcs 09_example_readonly_autoimpl_props.cs

10_example_indexers_and_properties: 10_example_indexers_and_properties.cs Makefile
	mcs 10_example_indexers_and_properties.cs


clean:
	rm -v 01_one_dimensional_indexer.exe \
          02_indexer_overloading.exe \
          03_example_indexer_without_array.exe \
          04_multidimensional_indexer.exe \
          05_properties.exe \
          06_example_readonly_property.exe \
          07_autoimplemented_properties.exe \
          08_private_accessor.exe \
          09_example_readonly_autoimpl_props.exe \
          10_example_indexers_and_properties.exe
