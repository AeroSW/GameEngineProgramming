AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/exceptions
INC_DIRS= $(MY_INC)

INC 	= ../../include/exceptions

SRC	= ../../src/exceptions

CFLAGS	= -c -g -std=c++11 $(INC_DIRS)

FILES	= ParseException.o SceneException.o RenderException.o GameException.o LevelException.o

default	: all
all	: $(FILES)

GameException.o		: $(SRC)/GameException.cpp $(INC)/GameException.h
	$(CC) $(CFLAGS) -o GameException.o $(SRC)/GameException.cpp

ParseException.o	: $(SRC)/ParseException.cpp $(INC)/ParseException.h
	$(CC) $(CFLAGS) -o ParseException.o $(SRC)/ParseException.cpp

SceneException.o	: $(SRC)/SceneException.cpp $(INC)/SceneException.h
	$(CC) $(CFLAGS) -o SceneException.o $(SRC)/SceneException.cpp

RenderException.o	: $(SRC)/RenderException.cpp $(INC)/RenderException.h
	$(CC) $(CFLAGS) -o RenderException.o $(SRC)/RenderException.cpp

LevelException.o	: $(SRC)/LevelException.cpp $(INC)/LevelException.h
	$(CC) $(CFLAGS) -o LevelException.o $(SRC)/LevelException.cpp
	
clean	:
	$(RM) ./*.o