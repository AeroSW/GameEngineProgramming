CC		= g++

INCLUDES= -I../../include -I../../level -I../../xml_parser

CFLAGS	= -std=c++11 -c $(INCLUDES)

default	: all

all		:
	$(CC) $(CFLAGS) ../../src/level/*.cpp
	
clean	:
	$(RM) ./*.o