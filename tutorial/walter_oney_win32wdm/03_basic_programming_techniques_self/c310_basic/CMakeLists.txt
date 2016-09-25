#
#	c3_basic.sys project setup.
#	Programming the Microsoft Windows Driver Model 2nd ed.
#	Before any real work on chapter 3, write a basic driver.
#
cmake_minimum_required(VERSION 3.2)
project(c3_proj)

set(SRC DriverEntry.cpp)

set(WDMINC "c:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0")
set(WDMLIB "c:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0")
set(WDMBIN "c:/Program Files (x86)/Windows Kits/10/bin")

add_executable(c3_basic ${SRC})

target_include_directories(c3_basic PUBLIC
                            "${WDMINC}/shared"
							"${WDMINC}/km")
  
target_compile_definitions(	c3_basic PUBLIC
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

target_compile_options(	c3_basic PUBLIC
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


target_link_libraries(	c3_basic PUBLIC
						"${WDMLIB}/km/x64/ntoskrnl.lib"
						"${WDMLIB}/km/x64/wdm.lib"
						"${WDMLIB}/km/x64/wmilib.lib")


set_property(TARGET c3_basic APPEND_STRING PROPERTY LINK_FLAGS 
					   "/OUT:$(ProjectDir)/$(ConfigurationName)/c3_basic.sys	\
						/INCREMENTAL:NO /NOLOGO /NODEFAULTLIB						\
						/STACK:262144,4096											\
						/SUBSYSTEM:NATIVE 											\
						/DRIVER:WDM /ENTRY:DriverEntry								\
						/MANIFEST:NO												\
						/MANIFESTUAC:NO												\
						/RELEASE /BASE:0x10000										\
						/MERGE:_TEXT=.text ")

add_custom_command(TARGET c3_basic POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/install-c3_basic"
		COMMAND "${CMAKE_COMMAND}" -E copy  "\$(TargetDir)/c3_basic.sys"  "${CMAKE_BINARY_DIR}/install-c3_basic"
		COMMAND "${CMAKE_COMMAND}" -E copy  "${CMAKE_CURRENT_SOURCE_DIR}/c3_basic.inf"  "${CMAKE_BINARY_DIR}/install-c3_basic"
		)
		

#	I.	Either run "fix_vcxproj.bat" to fix the generated settings or do it manually as below:
#
# remove /RTC1 or /RTCs or /RTCu from compiler flags
# remove /DYNAMICBASE or /DYNAMICBASE:NO from linker flags
# remove /NXCOMPAT from linker flags
# remove /MANIFEST from linker flags
# embed manifest no


#	II.	Either run "sign_driver_as_administrator.bat" or run these commands manually.
#		Some other .SYS and .DLL files may be required depending on c3_basic.inf
#
# ${WDMBIN}/x86/Inf2Cat.exe  driver:${CMAKE_BINARY_DIR}/install /os:10_x64
# start c3_basic_amd64.cat
# open VS command tool
# signtool sign /s ModuleWorksCertStore /n "ModuleWorks - for test use only"
#				 /t http://timestamp.verisign.com/scripts/timestamp.dll
#				 c3_basic_amd64.cat
# start c3_basic_amd64.cat






