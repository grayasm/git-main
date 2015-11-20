
1)	For Visual Studio projects the source files will show up in the IDE as usual, but any header
	files the project uses will not be there. To have the header files show up as well you simply
	add them to the list of source files for the executable or library. Any of the generators that
	do not use the header files directly (e.g. Makefile based generators) will simply ignore them.
	
2)	