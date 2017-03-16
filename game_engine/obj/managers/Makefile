AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/exceptions -I../../include/logs -I../../include/listeners
GL_INC	= -I/usr/local/include/OGRE

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/managers
INC	= ../../include/managers

FILES	= Render.o Manager.o Scene.o Level.o

default	: all
all	: $(FILES)
	
Manager.o	: $(SRC)/Manager.cpp $(INC)/Manager.h
	$(CC) $(CFLAGS) -o Manager.o $(SRC)/Manager.cpp
	
Render.o	: $(SRC)/Render.cpp $(INC)/Render.h
	$(CC) $(CFLAGS) -o Render.o $(SRC)/Render.cpp
	
Scene.o	: $(SRC)/Scene.cpp $(INC)/Scene.h
	$(CC) $(CFLAGS) -o Scene.o $(SRC)/Scene.cpp
	
Level.o	: $(SRC)/Level.cpp $(INC)/Level.h
	$(CC) $(CFLAGS) -o Level.o $(SRC)/Level.cpp
	
clean	:
	$(RM) ./*.o