AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/exceptions -I../../include/logs -I../../include/listeners -I../../include/managers/inputs -I../../include/audio -I../../include/scripts
GL_INC	= -I/usr/include/OGRE -I/usr/local/include/OIS -I/usr/local/include/BASS -I/usr/include/lua5.3 -I/usr/include/LuaBridge

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/managers
INC	= ../../include/managers

FILES	= Render.o Manager.o Scene.o Level.o

default	: all
all	: $(FILES)
	cd ./inputs && $(MAKE)
	
Manager.o	: $(SRC)/Manager.cpp $(INC)/Manager.h
	$(CC) $(CFLAGS) -o Manager.o $(SRC)/Manager.cpp
	
Render.o	: $(SRC)/Render.cpp $(INC)/Render.h
	$(CC) $(CFLAGS) -o Render.o $(SRC)/Render.cpp -I../../include/interfaces -I/usr/include/cegui-0.8.4
	
Scene.o	: $(SRC)/Scene.cpp $(INC)/Scene.h
	$(CC) $(CFLAGS) -o Scene.o $(SRC)/Scene.cpp
	
Level.o	: $(SRC)/Level.cpp $(INC)/Level.h
	$(CC) $(CFLAGS) -o Level.o $(SRC)/Level.cpp
	
clean	:
	$(RM) ./*.o
	cd ./inputs && $(MAKE) clean
