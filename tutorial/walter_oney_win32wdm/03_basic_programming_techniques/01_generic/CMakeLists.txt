# This is GENERIC.SYS project file

set(SRC control.cpp
		devqueue.cpp
		DriverEntry.cpp
		plugplay.cpp
		power.cpp
		RemoveLock.cpp
		stdcls.cpp
		driver.h
		generic.h
		GenericPower.h
		stdcls.h
		version.h
		Driver.rc
		generic.htm
		Generic.chm
		)

set(WDMINC "c:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0")
set(WDMLIB "c:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0")
set(WDMBIN "c:/Program Files (x86)/Windows Kits/10/bin")

add_executable(generic ${SRC})
target_include_directories(	generic PUBLIC
							"${WMDINC}/shared"
							"${WMDINC}/km")

target_compile_definitions(	generic PUBLIC
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
							
target_compile_options(	generic PUBLIC
						/Od		# no optimization
						/Oi		# intrinsics
						/GF		# enable string pooling
						/EHsc	# enable c++ exceptions
						/MTd	# multithreaded debug
						/Gy		# enable function level linking
						/Gz		# _stdcall calling convention
						/Oy		# omit frame pointers
						/Zp8	# struct member aligment
						# FORCE INCLUDES
						)


target_link_libraries(	generic PUBLIC
						"${WDMLIB}/km/x64/ntoskrnl.lib"
						"${WDMLIB}/km/x64/hal.lib"
						"${WDMLIB}/km/x64/wdm.lib"
						"${WDMLIB}/km/x64/wmilib.lib")


set_property(TARGET generic APPEND_STRING PROPERTY LINK_FLAGS 
					   "/OUT:$(ProjectDir)/$(ConfigurationName)/generic.sys		\
						/INCREMENTAL:NO /NOLOGO /NODEFAULTLIB					\
						/STACK:262144,4096										\
						/SUBSYSTEM:NATIVE 										\
						/DRIVER:WDM /ENTRY:DriverEntry							\
						/MANIFESTUAC:NO											\
						/RELEASE /BASE:0x10000									\
						/MERGE:_TEXT=.text ")

add_custom_command(TARGET generic POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetDir)/generic.sys"  "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/generic.inf"  "${CMAKE_BINARY_DIR}/install"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/generic.htm"  "${CMAKE_BINARY_DIR}/install"
		# create a catalog file for the driver package (type inf2cat /?  to see the supported operating systems)
		COMMAND "${WDMBIN}/x86/Inf2Cat.exe" driver:"${CMAKE_BINARY_DIR}/install" /os:10_x64
		# see README.txt for how to sign the catalog
		)
		
		
# remove /RTC1 or /RTCs or /RTCu from compiler flags
# remove /DYNAMICBASE or /DYNAMICBASE:NO from linker flags
# remove /NXCOMPAT from linker flags
# remove /MANIFEST from linker flags
# embed manifest no

						



