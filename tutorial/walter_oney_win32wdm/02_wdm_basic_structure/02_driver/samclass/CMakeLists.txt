# This is the "samclass.dll" for driver settings/Control Panel dialog.
set(SRC samclass.cpp
		StdAfx.h
		resource.h
		samclass.rc
		samclass.ico
		samclass.def)
		
add_library(samclass SHARED ${SRC})

target_compile_definitions(samclass PRIVATE 
		_CRT_SECURE_NO_WARNINGS)
		
message("CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

add_custom_command(TARGET samclass POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetPath)"  "${CMAKE_BINARY_DIR}/install"
		)