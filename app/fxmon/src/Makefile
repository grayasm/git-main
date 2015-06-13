
CC=g++
SRC= main.cpp MonConsoleHandlerPlugin.cpp MonEngine.cpp MonFXCMSession.cpp \
     MonHistoryPriceSession.cpp MonitorApp.cpp MonitorIni.cpp \
     MonNotificationPlugin.cpp MonPriceGeneratorSession.cpp \
     MonQuoteUpdateTimeoutPlugin.cpp MonSession.cpp Test.cpp

OBJ=$(SRC:.cpp=.o)

INCLUDE= -I. -I../../../lib/misc/src -I../../../lib/fxcore/src \
         -I../../../lib/fxcmAdapter/src \
         -I../../../world/ForexConnectAPI/linux/include/

CXXFLAGS= -g -c -std=c++98 -Wall -Wno-long-long -pedantic -DDEBUG -D_GLIBCXX_DEBUG -m64

LDFLAGS= -L../../../world/ForexConnectAPI/linux/lib/ -lForexConnect \
         -lgsexpat -lfxmsg -lgstool3 -llog4cplus -lhttplib -lpdas \
         -L../../../lib/fxcmAdapter/src -l:libfxcmAdapter.a \
         -L../../../lib/fxcore/src -l:libfxcore.a \
         -L../../../lib/misc/src/ -l:libmisc.a \
         -lm -ldl -lpthread

         
#-L$(HOME)/local/cppunit/lib -l:libcppunit.a -L../../misc/src -l:libmisc.a -lm -ldl -lpthread
TARGET=fxmon

all: $(SRC) $(TARGET)

.cpp.o:
	$(CC) $(INCLUDE) $(CXXFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	cp -av ./../../../world/ForexConnectAPI/linux/lib/*.{so,so.*} .
	cp -av ./../../../lib/misc/src/libmisc.a .
	cp -av ./../../../lib/fxcore/src/libfxcore.a .
	cp -av ./../../../lib/fxcmAdapter/src/libfxcmAdapter.a .
	
	
clean:
	rm -v *.o *.so *.so.* fxmon
