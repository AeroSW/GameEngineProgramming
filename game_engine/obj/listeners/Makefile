AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/managers/inputs -I../../include/exceptions -I../../include/logs -I../../include/listeners -I../../include/audio
GL_INC	= -I/usr/include/OGRE

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/listeners
INC	= ../../include/listeners

FILES	= AnimationListener.o InputListener.o RenderListener.o AudioListener.o PhysicsListener.o

default	: all
all	: $(FILES)
	
RenderListener.o	: $(SRC)/RenderListener.cpp $(INC)/RenderListener.h
	$(CC) $(CFLAGS) -o RenderListener.o $(SRC)/RenderListener.cpp
	
AnimationListener.o	: $(SRC)/AnimationListener.cpp $(INC)/AnimationListener.h
	$(CC) $(CFLAGS) -o AnimationListener.o $(SRC)/AnimationListener.cpp

InputListener.o		: $(SRC)/InputListener.cpp $(INC)/InputListener.h
	$(CC) $(CFLAGS) -o InputListener.o $(SRC)/InputListener.cpp

AudioListener.o		: $(SRC)/AudioListener.cpp $(INC)/AudioListener.h
	$(CC) $(CFLAGS) -o AudioListener.o $(SRC)/AudioListener.cpp

PhysicsListener.o	: $(SRC)/PhysicsListener.cpp $(INC)/PhysicsListener.h
	$(CC) $(CFLAGS) -o PhysicsListener.o $(SRC)/PhysicsListener.cpp

clean	:
	$(RM) ./*.o
