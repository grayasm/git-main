1)	add_library (foo STATIC foo1.c foo2.c)
	The name of foo is available  for use as a library name everywhere else in the project
	and CMake will know how to expand the name into the library when needed. Libraries can
	be declared to be of a particular type such as STATIC, SHARED, MODULE or left undeclared.
	STATIC indicates that the library must be built as a static library.
	SHARED indicate that the library must be built as a shared library.
	MODULE indicates that the library must be created so that it can be dynamically loaded
	into an executable. On may operating systems this is the same as SHARED, but on other
	systems such as Mac OS X it is different.
	If none of these options are specified this indicates that the library could be built
	as either SHARED or STATIC. In that case CMake uses the setting of the variable
	BUILD_SHARED_LIBS to determine if the library should be SHARED or STATIC. If it is not
	set, then CMake defaults to building static libraries.
	
2)	target_link_libraries (foobar foolib)
	Targets store a list of libraries that they link against which are set using the above
	command.
	
3)	target_link_libraries (foo bar)
	target_link_libraries (foobar foo)
	Since static libraries do not link to the libraries on which they depend, it is important
	for CMake to keep track of the libraries so they can be specified on the link line of
	the executable being created.
	
4)	set (F00 1)
	set (INC /usr/include /home/foo/include /usr/local/include)
	Variables are used to store values for later use, and can be single value or a list.

5)	add_subdirectory (dir1)
	Add a subdirectory dir1 to the build.
	dir1 specifies the directory in which the source CMakeLists.txt and code files are located.
	
6)	include (file1.cmake)
	Load and run CMake code from a file or module. If a module is specified instead of a file,
	the file with name <modulename>.cmake is searched first in CMAKE_MODULE_PATH,
	then in the CMake module directory.
	
	
	
	
	
	
	
	
	
	
	