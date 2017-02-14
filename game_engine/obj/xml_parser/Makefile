CC	= g++

INCLUDES= -I../../include -I../../include/level -I../../include/xml_parser
SOURCES	= ../../src/xml_parser

CFLAGS	= -c -std=c++11 $(INCLUDES)

default	: all
all	:
	$(CC) $(CFLAGS) $(SOURCES)/*.cpp

clean:
	rm ./*.o