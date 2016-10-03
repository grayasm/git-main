#	bugcheck.sys project setup

set(SRC DriverEntry.cpp
		Driver.h
		stddcls.h
		version.h
		driver.rc)


set(WDMINC "c:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0")
set(WDMLIB "c:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0")
set(WDMBIN "c:/Program Files (x86)/Windows Kits/10/bin")

add_executable(bugcheck ${SRC})

target_include_directories(bugcheck PUBLIC
                            "${WDMINC}/shared"
							"${WDMINC}/km")
  
target_compile_definitions(	bugcheck PUBLIC
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

target_compile_options(	bugcheck PUBLIC
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


target_link_libraries(	bugcheck PUBLIC
						"${WDMLIB}/km/x64/ntoskrnl.lib"
						"${WDMLIB}/km/x64/hal.lib"
						"${WDMLIB}/km/x64/wdm.lib"
						"${WDMLIB}/km/x64/wmilib.lib")


set_property(TARGET bugcheck APPEND_STRING PROPERTY LINK_FLAGS 
					   "/OUT:$(ProjectDir)/$(ConfigurationName)/bugcheck.sys		\
						/INCREMENTAL:NO /NOLOGO /NODEFAULTLIB					\
						/STACK:262144,4096										\
						/SUBSYSTEM:NATIVE 										\
						/DRIVER:WDM /ENTRY:DriverEntry							\
						/MANIFEST:NO											\
						/MANIFESTUAC:NO											\
						/RELEASE /BASE:0x10000									\
						/MERGE:_TEXT=.text ")

add_custom_command(TARGET bugcheck POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install-bugcheck"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetDir)/bugcheck.sys"  "${CMAKE_BINARY_DIR}/install-bugcheck"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/bugcheck.inf"  "${CMAKE_BINARY_DIR}/install-bugcheck"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/bugcheck.htm"  "${CMAKE_BINARY_DIR}/install-bugcheck"
		)
		
		

#	I.	Either run "fix_vcxproj.bat" to fix the generated settings or do it manually as below:
#
# remove /RTC1 or /RTCs or /RTCu from compiler flags
# remove /DYNAMICBASE or /DYNAMICBASE:NO from linker flags
# remove /NXCOMPAT from linker flags
# remove /MANIFEST from linker flags
# embed manifest no


#	II.	Either run "sign_driver_as_administrator.bat" or run these commands manually.
#		Some other .SYS and .DLL files may be required depending on bugcheck.inf
#
# ${WDMBIN}/x86/Inf2Cat.exe  driver:${CMAKE_BINARY_DIR}/install /os:10_x64
# start bugcheckamd64.cat
# open VS command tool
# signtool sign /s ModuleWorksCertStore /n "ModuleWorks - for test use only"
#				 /t http://timestamp.verisign.com/scripts/timestamp.dll
#				 bugcheckamd64.cat
# start bugcheckamd64.cat



