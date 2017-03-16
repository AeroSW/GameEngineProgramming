AutomatedMakefile = am
CC		= g++

MY_INC	= -I../include -I../include/parsers -I../include/managers -I../include/exceptions -I../include/logs -I../include/listeners
# GL_INC	= -I/usr/local/include/OGRE

INC_DIRS= $(MY_INC) # $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../src
INC	= ../include

FILES	= Transform.o Functions.o Game.o

default	: all
all	: $(FILES)
	cd logs && $(MAKE)
	cd parsers && $(MAKE)
	cd exceptions && $(MAKE)
	cd listeners && $(MAKE)
	cd managers && $(MAKE)
	
Transform.o	: $(SRC)/Transform.cpp $(INC)/Transform.h
	$(CC) $(CFLAGS) -o Transform.o $(SRC)/Transform.cpp
	
Functions.o	: $(SRC)/Functions.cpp $(INC)/Functions.h
	$(CC) $(CFLAGS) -o Functions.o $(SRC)/Functions.cpp
	
Game.o	: $(SRC)/Game.cpp
	$(CC) $(CFLAGS) -o Game.o $(SRC)/Game.cpp
	
clean	:
	$(RM) ./*.o
	cd ./xml_parser && $(MAKE) clean