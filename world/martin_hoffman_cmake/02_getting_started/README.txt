#
#
    1.CMake computes and maintains dependency information.
      The CMake executables must always be availalbe when make or an IDE
      is being run on CMake generated files.

      This means that if a CMake input file changes on disk, your build system
      will automatically re-run CMake and produce up-to-date build files.
      For this reason you generally should not generate Makefiles or projects
      with CMake and move them to another machine that does not have CMake
      installed.

    2.Configure and generate projects with:
        cmake-gui QT interface for Window/Linux
        ccmake    curses interface for UNIX platforms
    3.Configure and generate project interactively from command line with:
        $ cmake -i -G "NMake Makefiles" ../CMake
        Would you like to see advanced options? [No]:
        Please wait while cmake processes CMakeLists.txt files ...
        Variable Name: CMAKE_INSTALL_PREFIX
        Description: Install path prefix, prepended onto install directories.
        Current Value: C:/Program Files/CMake
        New Value (Enter to keep current value):
        ...
