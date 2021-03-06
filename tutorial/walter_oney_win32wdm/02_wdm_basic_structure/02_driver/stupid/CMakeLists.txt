# This is the "stupid.sys" CMake file.
set(SRC DriverEntry.cpp
		stddcls.cpp
		Driver.h
		guids.h
		stddcls.h
		version.h
		driver.rc
		sources
		makefile
		stupid.inf)

set(WDMINC "c:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0")
set(WDMLIB "c:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0")
set(WDMBIN "c:/Program Files (x86)/Windows Kits/10/bin")

add_executable(stupid ${SRC})
target_include_directories(	stupid PUBLIC 
						"${WDMINC}/shared"
						"${WDMINC}/km")
			
target_compile_definitions( stupid PUBLIC
							CONDITION_HANDLING=1
							DBG=1
							DEVL=1
							DRIVER
							FPO=0
							NT_INST=0
							NT_UP=1
							RDRDBG
							SRVDBG
							STD_CALL
							_DLL=1
							_IDWBUILD
							#_X86_
							_AMD64_
							)

target_compile_options(	stupid PUBLIC
						/Od		# no optimization
						/Oi		# intrinsics
						/GF		# enable string pooling
						/EHsc	# enable c++ exceptions
						/MTd	# multithreaded debug
						/Gy		# enable function level linking
						/Gz		# _stdcall calling convention
						/Oy		# omit frame pointers
						/Zp8	# struct member aligment
						)

target_link_libraries(	stupid PUBLIC
						"${WDMLIB}/km/x64/ntoskrnl.lib"
						"${WDMLIB}/km/x64/hal.lib"
						"${WDMLIB}/km/x64/wdm.lib"
						"${WDMLIB}/km/x64/wmilib.lib")
					   #"${WDMLIB}/um/x64/kernel32.lib"
		
set_property(TARGET stupid APPEND_STRING PROPERTY LINK_FLAGS 
					   "/OUT:$(ProjectDir)/$(ConfigurationName)/stupid.sys		\
						/INCREMENTAL:NO /NOLOGO /NODEFAULTLIB					\
						/STACK:262144,4096										\
						/SUBSYSTEM:NATIVE 										\
						/DRIVER:WDM /ENTRY:DriverEntry							\
						/MANIFESTUAC:NO											\
						/RELEASE /BASE:0x10000									\
						/MERGE:_TEXT=.text ")

add_custom_command(TARGET stupid POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetDir)/stupid.sys"  "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/stupid.inf"  "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/stupid.htm"  "${CMAKE_BINARY_DIR}/install"
		# create a catalog file for the driver package (type inf2cat /?  to see the supported operating systems)
		COMMAND "${WDMBIN}/x86/Inf2Cat.exe" driver:"${CMAKE_BINARY_DIR}/install" /os:10_x64
		# see README.txt for how to sign the catalog
		)
		
		
# remove /RTC1 or /RTCs or /RTCu from compiler flags
# remove /DYNAMICBASE or /DYNAMICBASE:NO from linker flags
# remove /NXCOMPAT from linker flags
# remove /MANIFEST from linker flags
# embed manifest no

						
