CC		= g++
DRIVER	= ParserTest
INC		= -I../game_engine/include -I../game_engine/include/level -I./include
SRC		= ./src
GOBJ	= ../game_engine/obj
LOBJ	= ../level_objects/obj
XOBJ	= ./obj
OBJ		= $(GOBJ)/*.o $(LOBJ)/*.o $(XOBJ)/*.o
CFLAGS	= -c -std=c++11 $(INC) -Wall -g
EFLAGS	= -o $(DRIVER) $(OBJ)
default:	compile_all
compile_all:
	cd $(XOBJ) && $(MAKE)
	$(CC) $(CFLAGS) ./tests/$(DRIVER).cpp
install:
	$(CC) $(EFLAGS) ./$(DRIVER).o -g