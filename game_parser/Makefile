CC		= g++
DRIVER	= ./test/TestLPController.cpp
GAME	= parse_test

INCLUDES= -I./include -I../level_objects/include -I../game_engine/include -I../game_engine/include/level
LOBJS	= ../level_objects/obj
SRC		= ./src
GOBJS	= ../game_engine/obj
POBJS	= ./obj
LINKER	= $(LOBJS)/*.o $(POBJS)/*.o $(GOBJS)/*.o

CFlAGS	= -std=c++11 -c $(INCLUDES)
EFLAGS	= -std=c++11 -o $(GAME) $(LINKER)

default	: compile
compile	:
	cd $(POBJS) && $(MAKE)
	
install	:
	$(CC) $(INCLUDES) $(EFLAGS) $(DRIVER)
	
clean	:
	$(RM) $(GAME)
	cd $(POBJS) && $(MAKE) clean