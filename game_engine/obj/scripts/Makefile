AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/parsers -I../../include/managers -I../../include/scripts -I../../include/exceptions
GL_INC	= -I/usr/include/lua5.3 -I/usr/include/LuaBridge

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../src/scripts
INC	= ../../include/scripts

FILES	= LuaScripter.o

default	: all
all	: $(FILES)

LuaScripter.o	: $(SRC)/LuaScripter.cpp $(INC)/LuaScripter.h $(INC)/Scripter.h
	$(CC) $(CFLAGS) -o LuaScripter.o $(SRC)/LuaScripter.cpp


clean	:
	$(RM) ./*.o
