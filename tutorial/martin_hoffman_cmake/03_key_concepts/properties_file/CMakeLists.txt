# Just because I want to access the source files properties I need to add the
# cmake minimum version
cmake_minimum_required(VERSION 3.4)


project (Hello)

# CMake Variables
set (SRC File1.c)

add_executable (Hello ${SRC})




# Now we look at source file File1.c properties as defined here:
# https://cmake.org/cmake/help/v3.4/manual/cmake-properties.7.html

get_source_file_property(FILE1_ABSTRACT                   File1.c ABSTRACT)
get_source_file_property(FILE1_AUTOUIC_OPTIONS            File1.c AUTOUIC_OPTIONS)
get_source_file_property(FILE1_AUTORCC_OPTIONS            File1.c AUTORCC_OPTIONS)
get_source_file_property(FILE1_COMPILE_DEFINITIONS        File1.c COMPILE_DEFINITIONS)
get_source_file_property(FILE1_COMPILE_FLAGS              File1.c COMPILE_FLAGS)
get_source_file_property(FILE1_EXTERNAL_OBJECT            File1.c EXTERNAL_OBJECT)
get_source_file_property(FILE1_Fortran_FORMAT             File1.c Fortran_FORMAT)
get_source_file_property(FILE1_GENERATED                  File1.c GENERATED)
get_source_file_property(FILE1_HEADER_FILE_ONLY           File1.c HEADER_FILE_ONLY)
get_source_file_property(FILE1_KEEP_EXTENSION             File1.c KEEP_EXTENSION)
get_source_file_property(FILE1_LABELS                     File1.c LABELS)
get_source_file_property(FILE1_LANGUAGE                   File1.c LANGUAGE)
get_source_file_property(FILE1_LOCATION                   File1.c LOCATION)
get_source_file_property(FILE1_MACOSX_PACKAGE_LOCATION    File1.c MACOSX_PACKAGE_LOCATION)
get_source_file_property(FILE1_OBJECT_DEPENDS             File1.c OBJECT_DEPENDS)
get_source_file_property(FILE1_OBJECT_OUTPUTS             File1.c OBJECT_OUTPUTS)
get_source_file_property(FILE1_SYMBOLIC                   File1.c SYMBOLIC)
get_source_file_property(FILE1_VS_DEPLOYMENT_CONTENT      File1.c VS_DEPLOYMENT_CONTENT)
get_source_file_property(FILE1_VS_DEPLOYMENT_LOCATION     File1.c VS_DEPLOYMENT_LOCATION)
get_source_file_property(FILE1_VS_SHADER_ENTRYPOINT       File1.c VS_SHADER_ENTRYPOINT)
get_source_file_property(FILE1_VS_SHADER_FLAGS            File1.c VS_SHADER_FLAGS)
get_source_file_property(FILE1_VS_SHADER_MODEL            File1.c VS_SHADER_MODEL)
get_source_file_property(FILE1_VS_SHADER_TYPE             File1.c VS_SHADER_TYPE)
get_source_file_property(FILE1_VS_XAML_TYPE               File1.c VS_XAML_TYPE)
get_source_file_property(FILE1_WRAP_EXCLUDE               File1.c WRAP_EXCLUDE)
get_source_file_property(FILE1_XCODE_EXPLICIT_FILE_TYPE   File1.c XCODE_EXPLICIT_FILE_TYPE)
get_source_file_property(FILE1_XCODE_LAST_KNOWN_FILE_TYPE File1.c XCODE_LAST_KNOWN_FILE_TYPE)


# Let's print them to see what we got.
message ("Properties on Source Files (e.g. File1.c)")
message ("ABSTRACT=${FILE1_ABSTRACT}")
message ("AUTOUIC_OPTIONS=${FILE1_AUTOUIC_OPTIONS}")
message ("AUTORCC_OPTIONS=${FILE1_AUTORCC_OPTIONS}")
message ("COMPILE_DEFINITIONS=${FILE1_COMPILE_DEFINITIONS}")
message ("COMPILE_FLAGS=${FILE1_COMPILE_FLAGS}")
message ("EXTERNAL_OBJECT=${FILE1_EXTERNAL_OBJECT}")
message ("Fortran_FORMAT=${FILE1_Fortran_FORMAT}")
message ("GENERATED=${FILE1_GENERATED}")
message ("HEADER_FILE_ONLY=${FILE1_HEADER_FILE_ONLY}")
message ("KEEP_EXTENSION=${FILE1_KEEP_EXTENSION}")
message ("LABELS=${FILE1_LABELS}")
message ("LANGUAGE=${FILE1_LANGUAGE}")
message ("LOCATION=${FILE1_LOCATION}")
message ("MACOSX_PACKAGE_LOCATION=${FILE1_MACOSX_PACKAGE_LOCATION}")
message ("OBJECT_DEPENDS=${FILE1_OBJECT_DEPENDS}")
message ("OBJECT_OUTPUTS=${FILE1_OBJECT_OUTPUTS}")
message ("SYMBOLIC=${FILE1_SYMBOLIC}")
message ("VS_DEPLOYMENT_CONTENT=${FILE1_VS_DEPLOYMENT_CONTENT}")
message ("VS_DEPLOYMENT_LOCATION=${FILE1_VS_DEPLOYMENT_LOCATION}")
message ("VS_SHADER_ENTRYPOINT=${FILE1_VS_SHADER_ENTRYPOINT}")
message ("VS_SHADER_FLAGS=${FILE1_VS_SHADER_FLAGS}")
message ("VS_SHADER_MODEL=${FILE1_VS_SHADER_MODEL}")
message ("VS_SHADER_TYPE=${FILE1_VS_SHADER_TYPE}")
message ("VS_XAML_TYPE=${FILE1_VS_XAML_TYPE}")
message ("WRAP_EXCLUDE=${FILE1_WRAP_EXCLUDE}")
message ("XCODE_EXPLICIT_FILE_TYPE=${FILE1_XCODE_EXPLICIT_FILE_TYPE}")
message ("XCODE_LAST_KNOWN_FILE_TYPE=${FILE1_XCODE_LAST_KNOWN_FILE_TYPE}")
