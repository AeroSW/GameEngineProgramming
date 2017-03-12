AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/xml_parser
GL_INC	= -I/usr/local/include/OGRE -I/usr/include/boost
INC_DIRS= $(MY_INC) $(GL_INC)

SRC		= ../../src/xml_parser

CFLAGS	= -c -std=c++11 $(INC_DIRS)

default	: all
all		:
	$(CC) $(CFLAGS) $(SRC)/*.cpp

clean	:
	$(RM) ./*.o