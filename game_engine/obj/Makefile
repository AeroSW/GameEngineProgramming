AutomatedMakefile = am
CC		= g++

MY_INC	= -I./include -I./include/xml_parser
GL_INC	= -I/usr/local/include/OGRE -I/usr/include/boost
INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC		= ../src

default	: all
all		:
	$(CC) $(CFLAGS) $(SRC)/*.cpp
	cd ./xml_parser && $(MAKE)
	
clean	:
	$(RM) ./*.o
	cd ./xml_parser && $(MAKE) clean