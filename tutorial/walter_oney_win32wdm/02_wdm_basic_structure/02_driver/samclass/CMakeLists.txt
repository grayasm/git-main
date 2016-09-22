#
#	samclass.dll provides icon with tag "WDM Book Samples" in the "Device Manager".
#
set(SRC samclass.cpp
		StdAfx.h
		resource.h
		samclass.rc
		samclass.ico
		samclass.def)
		
add_library(samclass SHARED ${SRC})

target_compile_definitions(samclass PRIVATE 
		_CRT_SECURE_NO_WARNINGS)
		
add_custom_command(TARGET samclass POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetPath)"  "${CMAKE_BINARY_DIR}/install"
		)