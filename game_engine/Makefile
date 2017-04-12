AutomatedMakefile = am
CC		= g++
EXE		= Game

GL_INC	= -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OIS -I/usr/include/cegui-0.8.4 -I/usr/local/include/BASS -I/usr/include/LuaBridge -I/usr/include/lua5.3
INC_DIRS= $(MY_INC) $(GL_INC)

MY_LIB	= ./obj/*.o ./obj/parsers/*.o ./obj/managers/*.o ./obj/logs/*.o ./obj/exceptions/*.o ./obj/listeners/*.o ./obj/managers/inputs/*.o ./obj/interfaces/*.o ./obj/audio/*.o ./obj/scripts/*.o
GL_LIB	= -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/lib/cegui-0.8 -L/usr/local/lib/BASS/x64
LIB_DIRS= $(MY_LIB) $(GL_LIB)
LIBS	= -lboost_filesystem -lboost_system -lOgreMain -lOIS -lCEGUIBase-0 -lCEGUIOgreRenderer-0 -lbass -llua5.3

CFLAGS	= -std=c++11 $(INC_DIRS) -c
EFLAGS	= -std=c++11 $(LIB_DIRS) -o

default	: compile

compile	:
	cd ./obj && $(MAKE)
	
install	:
	$(CC) $(EFLAGS) $(EXE) $(LIBS)
	
clean	:
	cd ./obj && $(MAKE) clean
