1.	CMake computes and maintains dependency information. The CMake executables must always
	be availalbe when make or an IDE is being run on CMake generated files. This means that
	if a CMake input file changes on disk, your build system will automatically re-run CMake
	and produce up-to-date build files. For this reason you generally should not generate
	Makefiles or projects with CMake and move them to another machine that does not have
	CMake installed.
	
