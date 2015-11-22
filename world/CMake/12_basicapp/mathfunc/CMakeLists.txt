#
#
add_library (MathFunctions mysqrt.cxx)

#
# add INSTALL target
# from Visual Studio build INSTALL
# from linux terminal: make install [DESTDIR=...]
install (TARGETS MathFunctions DESTINATION bin)
install (FILES   mysqrt.h      DESTINATION include)
