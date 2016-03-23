
1)	For Visual Studio projects the source files will show up in the IDE as usual, but any header
	files the project uses will not be there. To have the header files show up as well you simply
	add them to the list of source files for the executable or library. Any of the generators that
	do not use the header files directly (e.g. Makefile based generators) will simply ignore them.

2)  04.02 for regular expressions
3)  04.03 for moudules and packages
4)  04.04 for policies
5)  04.07 for installing files
          there should be multiple subfolders with different type of files
          to be installed and CMake should pick all and put them into the right location.
