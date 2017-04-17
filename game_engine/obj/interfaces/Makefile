AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/interfaces -I../../include/exceptions
GL_INC	= -I/usr/include/cegui-0.8.4 -I/usr/include/OGRE

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/interfaces
INC	= ../../include/interfaces

FILES	= Interface.o Cegui.o CeguiWindowResource.o

default	: all
all	: $(FILES)

Interface.o	: $(SRC)/Interface.cpp $(INC)/Interface.h
	$(CC) $(CFLAGS) -o Interface.o $(SRC)/Interface.cpp

Cegui.o	: $(SRC)/Cegui.cpp $(INC)/Cegui.h
	$(CC) $(CFLAGS) -o Cegui.o $(SRC)/Cegui.cpp
	
CeguiWindowResource.o	: $(SRC)/CeguiWindowResource.cpp $(INC)/CeguiWindowResource.h
	$(CC) $(CFLAGS) -o CeguiWindowResource.o $(SRC)/CeguiWindowResource.cpp

#CeguiWidgetMapping.o : $(SRC)/CeguiWidgetMapping.cpp $(INC)/CeguiWidgetMapping.h
#	$(CC) $(CFLAGS) -o CeguiWidgetMapping.o $(SRC)/CeguiWidgetMapping.cpp

clean	:
	$(RM) ./*.o
