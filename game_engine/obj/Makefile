AutomatedMakefile = am
CC	= g++

MY_INC	= -I../include -I../include/xml_parser -I../level
GL_INC	= -I$(OGRE_PATH)/include -I$(BOOST_PATH) -I$(OGRE_PATH)/OgreMain/include
INC	= $(GL_INC) $(MY_INC)

CFLAGS	= -c -std=c++11 -g $(INC)

SRC	= ../src

default	: all
all	:
	$(CC) $(CFLAGS) $(SRC)/*.cpp
	cd ./xml_parser && $(MAKE)
	
clean	:
	$(RM) ./*.o
	cd ./xml_parser && $(MAKE) clean