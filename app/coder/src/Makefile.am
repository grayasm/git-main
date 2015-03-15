bin_PROGRAMS = coder
coder_SOURCES = main.cpp	Alias.cpp	Delay.cpp Discard.cpp EbnfGrammar.cpp False.cpp GramReader.cpp \
								GramWriter.cpp Group.cpp	Has.cpp	HasNot.cpp	\
								InputFile.cpp	Integer.cpp	IsEq.cpp	IsNotEq.cpp	Lexer.cpp	\
								Null.cpp Optional.cpp	Quote.cpp	Range.cpp	Repeat.cpp RepeatRange.cpp Repetition.cpp	\
								Report.cpp True.cpp

coder_CFLAGS=-g -O
coder_CXXFLAGS=-g -O
coder_CPPFLAGS=-g -O -I./ -I../../../lib/k1/src
CFLAGS=
CXXFLAGS=
CPPFLAGS=

coder_LDFLAGS=-lk1 -lm -L../../../lib/k1/src
