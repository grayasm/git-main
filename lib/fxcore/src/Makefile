all: fxcore

#On Windows with codeblocks and mingw g++ compiler
#CC=mingw32-g++.exe
CC=g++
AR=ar
SRC = Currency.cpp Deserializer.cpp ExponentialMovingAverage.cpp FixGridPositionStub.cpp \
    MarketDummyPlugin.cpp MarketPlugin.cpp Position.cpp Price.cpp PriceGenerator.cpp Serializer.cpp \
    SimpleMovingAverage.cpp Strategy2FixGrid.cpp Strategy2HedgeFixGrid.cpp StrategyFixGrid.cpp \
    StrategyHedgeFixGrid.cpp StrategyJNemRenko.cpp Transaction.cpp

OBJ = Currency.o Deserializer.o ExponentialMovingAverage.o FixGridPositionStub.o \
    MarketDummyPlugin.o MarketPlugin.o Position.o Price.o PriceGenerator.o Serializer.o \
    SimpleMovingAverage.o Strategy2FixGrid.o Strategy2HedgeFixGrid.o StrategyFixGrid.o \
    StrategyHedgeFixGrid.o StrategyJNemRenko.o Transaction.o

INCLUDE=-I. -I../../misc/src

CXXFLAGS= -g -O0 -Wall -Wno-long-long -std=c++98 -pedantic -DDEBUG -D_GLIBCXX_DEBUG -m64
# -pedantic-errors

fxcore: $(SRC)
	$(CC)  $(INCLUDE) -c $(CXXFLAGS) $(SRC)
	$(AR)  rcs libfxcore.a $(OBJ)

	$(CC)  $(INCLUDE) -c $(CXXFLAGS) -fPIC $(SRC)
	$(CC)  $(INCLUDE) $(CXXFLAGS) -shared -Wl,-soname,libfxcore.so.1 -o libfxcore.so.1.0.1 $(OBJ)
	ln -sf libfxcore.so.1.0.1  libfxcore.so.1

clean:
	rm *.o libfxcore.a libfxcore.so*
