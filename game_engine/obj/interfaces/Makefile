AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/interfaces -I../../include/exceptions
GL_INC	= -I/usr/include/cegui-0.8.4 -I/usr/include/OGRE

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/interfaces
INC	= ../../include/interfaces

FILES	= Interface.o Cegui.o

default	: all
all	: $(FILES)
	
Interface.o	: $(SRC)/Interface.cpp $(INC)/Interface.h
	$(CC) $(CFLAGS) -o Interface.o $(SRC)/Interface.cpp
	
Cegui.o	: $(SRC)/Cegui.cpp $(INC)/Cegui.h
	$(CC) $(CFLAGS) -o Cegui.o $(SRC)/Cegui.cpp


clean	:
	$(RM) ./*.o
