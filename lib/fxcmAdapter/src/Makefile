all: fxcmAdapter

#On Windows with codeblocks and mingw g++ compiler
#CC=mingw32-g++.exe
CC=g++
AR=ar
SRC = fxcmHistory.cpp fxcmIniParams.cpp fxcmMarketPlugin.cpp fxcmOrderMonitor.cpp \
      fxcmPermission.cpp fxcmPipCost.cpp fxcmResponseListener.cpp fxcmSession.cpp \
      fxcmSessionHelper.cpp fxcmSessionListener.cpp fxcmTradingSettings.cpp

OBJ = fxcmHistory.o fxcmIniParams.o fxcmMarketPlugin.o fxcmOrderMonitor.o \
      fxcmPermission.o fxcmPipCost.o fxcmResponseListener.o fxcmSession.o \
      fxcmSessionHelper.o fxcmSessionListener.o fxcmTradingSettings.o

INCLUDE=-I. -I../../misc/src -I../../fxcore/src -I../../../world/ForexConnectAPI/linux/include/

CXXFLAGS= -g -O0 -Wall -Wno-long-long -std=c++98 -pedantic -DDEBUG -D_GLIBCXX_DEBUG -m64
# -pedantic-errors
LDFLAGS = -L../../../world/ForexConnectAPI/linux/lib/ -l libForexConnect.so

fxcmAdapter: $(SRC)
	$(CC)  $(INCLUDE) -c $(CXXFLAGS) $(SRC)
	$(AR)  rcs libfxcmAdapter.a $(OBJ)

	$(CC)  $(INCLUDE) -c $(CXXFLAGS) -fPIC $(SRC)
	$(CC)  $(INCLUDE) $(CXXFLAGS) -shared -Wl,-soname,libfxcmAdapter.so.1 -o libfxcmAdapter.so.1.0.1 $(OBJ)
	ln -sf libfxcmAdapter.so.1.0.1  libfxcmAdapter.so.1

clean:
	rm *.o libfxcmAdapter.a libfxcmAdapter.so*
