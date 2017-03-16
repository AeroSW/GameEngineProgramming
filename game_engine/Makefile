AutomatedMakefile = am
CC		= g++
EXE		= Game

GL_INC	= -I/usr/local/include/OGRE -I/usr/include/boost
INC_DIRS= $(MY_INC) $(GL_INC)

MY_LIB	= ./obj/*.o ./obj/parsers/*.o ./obj/managers/*.o ./obj/logs/*.o ./obj/exceptions/*.o ./obj/listeners/*.o
GL_LIB	= -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu
LIB_DIRS= $(MY_LIB) $(GL_LIB)
LIBS	= -lboost_filesystem -lboost_system -lOgreMain

CFLAGS	= -std=c++11 $(INC_DIRS) -c
EFLAGS	= -std=c++11 $(LIB_DIRS) -o

default	: compile

compile	:
	cd ./obj && $(MAKE)
	
install	:
	$(CC) $(EFLAGS) $(EXE) $(LIBS)