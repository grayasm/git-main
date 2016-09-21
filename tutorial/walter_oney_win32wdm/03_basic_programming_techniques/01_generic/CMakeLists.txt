# This is GENERIC.SYS project file
# Usually this driver acompanies other SYS files, so it doesn't have its own INF file.

set(SRC control.cpp
		devqueue.cpp
		DriverEntry.cpp
		plugplay.cpp
		power.cpp
		RemoveLock.cpp
		driver.h
		generic.h
		GenericPower.h
		stddcls.h
		version.h
		Driver.rc
		sources
		makefile)
		

set(WDMINC "c:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0")
set(WDMLIB "c:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0")
set(WDMBIN "c:/Program Files (x86)/Windows Kits/10/bin")

add_executable(generic ${SRC})

target_include_directories(generic PUBLIC
                            "${WDMINC}/shared"
							"${WDMINC}/km")
  
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
						/GS-	# disable buffer security check
						/EHsc	# enable c++ exceptions
						/MTd	# multithreaded debug
						/Gy		# enable function level linking
						/Gz		# _stdcall calling convention
						/Oy		# omit frame pointers
						/Zp8	# struct member aligment
						/FI"warning.h" # force includes
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
						/MANIFEST:NO											\
						/MANIFESTUAC:NO											\
						/RELEASE /BASE:0x10000									\
						/MERGE:_TEXT=.text ")

add_custom_command(TARGET generic POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install-generic"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetDir)/generic.sys"  "${CMAKE_BINARY_DIR}/install-generic"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/generic.htm"  "${CMAKE_BINARY_DIR}/install-generic"
		)
		

# I.	There should be a .bat file to fix vcxproj (fix_vcxproj.bat) or alternatively change .vcxproj by hand.
# --------------------------------------------------------------------------------------------------------------
#
# remove /RTC1 or /RTCs or /RTCu from compiler flags
# remove /DYNAMICBASE or /DYNAMICBASE:NO from linker flags
# remove /NXCOMPAT from linker flags
# remove /MANIFEST from linker flags
# embed manifest no

# II.	Copy generic.sys to the other driver folder where it is needed.




