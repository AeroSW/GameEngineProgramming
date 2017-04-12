AutomatedMakefile = am
CC		= g++

MY_INC	= -I../include -I../include/managers -I../include/managers/inputs -I../include/audio -I../include/exceptions -I../include/interfaces -I../include/logs -I../include/listeners -I../include/parsers -I../include/scripts
# GL_INC	= -I/usr/local/include/OGRE

INC_DIRS= $(MY_INC) # $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../src
INC	= ../include

FILES	= Transform.o Functions.o Game.o #PairException.o

default	: all
all	: $(FILES)
	cd logs && $(MAKE)
	cd parsers && $(MAKE)
	cd exceptions && $(MAKE)
	cd listeners && $(MAKE)
	cd managers && $(MAKE)
	cd interfaces && $(MAKE)
	cd audio && $(MAKE)
	cd scripts && $(MAKE)
	
Transform.o	: $(SRC)/Transform.cpp $(INC)/Transform.h
	$(CC) $(CFLAGS) -o Transform.o $(SRC)/Transform.cpp
	
Functions.o	: $(SRC)/Functions.cpp $(INC)/Functions.h
	$(CC) $(CFLAGS) -o Functions.o $(SRC)/Functions.cpp
	
Game.o	: $(SRC)/Game.cpp
	$(CC) $(CFLAGS) -o Game.o $(SRC)/Game.cpp
	
#PairException.o	:	$(SRC)/PairException.cpp $(INC)/PairException.h
#	$(CC) $(CFLAGS) -o PairException.o $(SRC)/PairException.cpp
	
clean	:
	$(RM) ./*.o
	cd ./parsers && $(MAKE) clean
	cd ./managers && $(MAKE) clean
	cd ./logs && $(MAKE) clean
	cd ./listeners && $(MAKE) clean
	cd ./exceptions && $(MAKE) clean
	cd ./interfaces && $(MAKE) clean
	cd ./audio && $(MAKE) clean
	cd ./scripts && $(MAKE) clean
	
