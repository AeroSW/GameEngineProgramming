CC	= g++

INCLUDES= -I../include -I../../level_objects/include -I../../game_engine/include -I../../game_engine/include/level
SOURCES	= ../src

CFLAGS	= -c -std=c++11 $(INCLUDES)

default	: all
all	:
	$(CC) $(CFLAGS) $(SOURCES)/*.cpp

clean:
	rm *.o