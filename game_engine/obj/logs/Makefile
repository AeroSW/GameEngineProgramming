AutomatedMakefile = am
CC		= g++

MY_INC	= -I../../include -I../../include/logs
INC_DIRS= $(MY_INC)

INC 	= ../../include/logs

SRC	= ../../src/logs

CFLAGS	= -c -g -std=c++11 $(INC_DIRS)

FILES	= LogManager.o

default	: all
all	: $(FILES)

LogManager.o	: $(SRC)/LogManager.cpp $(INC)/LogManager.h
	$(CC) $(CFLAGS) -o LogManager.o $(SRC)/LogManager.cpp

clean	:
	$(RM) ./*.o