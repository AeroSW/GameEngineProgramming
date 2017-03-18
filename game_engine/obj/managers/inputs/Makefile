AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../../include -I../../../include/managers -I../../../include/managers/inputs -I../../../include/exceptions -I../../../include/listeners
GL_INC	= -I/usr/include/ois

INC_DIRS= $(MY_INC) $(GL_INC)

CFLAGS	= -c -std=c++11 -g $(INC_DIRS)

SRC	= ../../../src/managers/inputs
INC	= ../../../include/managers/inputs

FILES	= Gamepad.o Keyboard.o Mouse.o Input.o

default	: all
all	: $(FILES)
	
Gamepad.o	: $(SRC)/Gamepad.cpp $(INC)/Gamepad.h $(INC)/Input.h
	$(CC) $(CFLAGS) -o Gamepad.o $(SRC)/Gamepad.cpp
	
Keyboard.o	: $(SRC)/Keyboard.cpp $(INC)/Keyboard.h $(INC)/Input.h
	$(CC) $(CFLAGS) -o Keyboard.o $(SRC)/Keyboard.cpp

Mouse.o	: $(SRC)/Mouse.cpp $(INC)/Mouse.h $(INC)/Input.h
	$(CC) $(CFLAGS) -o Mouse.o $(SRC)/Mouse.cpp
	
Input.o	: $(SRC)/Input.cpp $(INC)/Input.h
	$(CC) $(CFLAGS) -o Input.o $(SRC)/Input.cpp
	
clean	:
	$(RM) ./*.o