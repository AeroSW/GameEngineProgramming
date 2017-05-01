AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/exceptions -I../../include/physics
GL_INC	= -I/usr/local/include/bullet -I/usr/include/OGRE
INC_DIRS= $(MY_INC) $(GL_INC)

INC 	= ../../include/physics

SRC		= ../../src/physics

CFLAGS	= -c -g -std=c++11 $(INC_DIRS)

FILES	= BulletPhysics.o

default	: all
all	: $(FILES)

BulletPhysics.o:	$(SRC)/BulletPhysics.cpp $(INC)/BulletPhysics.h $(INC)/ObjectStruct.h
	$(CC) $(CFLAGS) -o BulletPhysics.o -c $(SRC)/BulletPhysics.cpp

clean	:
	$(RM) ./*.o