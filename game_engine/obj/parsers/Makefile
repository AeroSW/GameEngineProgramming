AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/exceptions -I../../include/audio -I../../include/scripts
INC_DIRS= $(MY_INC)

INC 	= ../../include/parsers

SRC	= ../../src/parsers

CFLAGS	= -c -g -std=c++11 $(INC_DIRS)

FILES	= AudioParser.o LevelParser.o GameParser.o tinyxml2.o GUIParser.o Parser.o ScriptParser.o PhysicsParser.o

default	: all
all	: $(FILES)

AudioParser.o	: $(SRC)/AudioParser.cpp $(INC)/AudioParser.h
	$(CC) $(CFLAGS) -o AudioParser.o $(SRC)/AudioParser.cpp

LevelParser.o	: $(SRC)/LevelParser.cpp $(INC)/LevelParser.h
	$(CC) $(CFLAGS) -o LevelParser.o $(SRC)/LevelParser.cpp

GameParser.o	: $(SRC)/GameParser.cpp $(INC)/GameParser.h
	$(CC) $(CFLAGS) -o GameParser.o $(SRC)/GameParser.cpp

tinyxml2.o	: $(SRC)/tinyxml2.cpp $(INC)/tinyxml2.h
	$(CC) $(CFLAGS) -o tinyxml2.o $(SRC)/tinyxml2.cpp
	
GUIParser.o	: $(SRC)/GUIParser.cpp $(INC)/GUIParser.h
	$(CC) $(CFLAGS) -o GUIParser.o $(SRC)/GUIParser.cpp -I../../include/interfaces
	
Parser.o	: $(SRC)/Parser.cpp $(INC)/Parser.h
	$(CC) $(CFLAGS) -o Parser.o $(SRC)/Parser.cpp

ScriptParser.o	: $(SRC)/ScriptParser.cpp $(INC)/ScriptParser.h
	$(CC) $(CFLAGS) -o ScriptParser.o $(SRC)/ScriptParser.cpp

PhysicsParser.o	: $(SRC)/PhysicsParser.cpp $(INC)/PhysicsParser.h
	$(CC) $(CFLAGS) -o PhysicsParser.o $(SRC)/PhysicsParser.cpp -I../../include/physics -I/usr/local/include/bullet

clean	:
	$(RM) ./*.o
