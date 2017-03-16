AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/exceptions -I../../include/logs -I../../include/listeners
GL_INC	= -I/usr/local/include/OGRE

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/listeners
INC	= ../../include/listeners

FILES	= AnimationListener.o RenderListener.o

default	: all
all	: $(FILES)
	
RenderListener.o	: $(SRC)/RenderListener.cpp $(INC)/RenderListener.h
	$(CC) $(CFLAGS) -o RenderListener.o $(SRC)/RenderListener.cpp
	
AnimationListener.o	: $(SRC)/AnimationListener.cpp $(INC)/AnimationListener.h
	$(CC) $(CFLAGS) -o AnimationListener.o $(SRC)/AnimationListener.cpp
	
clean	:
	$(RM) ./*.o