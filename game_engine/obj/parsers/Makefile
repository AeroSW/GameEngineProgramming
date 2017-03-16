AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../managers -I../../exceptions
INC_DIRS= $(MY_INC)

INC 	= ../../include/parsers

SRC	= ../../src/parsers

CFLAGS	= -c -std=c++11 $(INC_DIRS)

FILES	= LevelParser.o GameParser.o tinyxml2.o

default	: all
all	: $(FILES)

LevelParser.o	: $(SRC)/LevelParser.cpp $(INC)/LevelParser.h
	$(CC) $(CFLAGS) -o LevelParser.o $(SRC)/LevelParser.cpp

GameParser.o	: $(SRC)/GameParser.cpp $(INC)/GameParser.h
	$(CC) $(CFLAGS) -o GameParser.o $(SRC)/GameParser.cpp

tinyxml2.o	: $(SRC)/tinyxml2.cpp $(INC)/tinyxml2.h
	$(CC) $(CFLAGS) -o tinyxml2.o $(SRC)/tinyxml2.cpp

clean	:
	$(RM) ./*.o