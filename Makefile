AutomatedMakefile = am
CC = 		g++

INC_DIRS=	-I../ -I$(OGRE_PATH)/include -I$(BOOST_PATH) -I$(OGRE_PATH)/OgreMain/include
LIB_DIRS=	-L../ -L$(OGRE_PATH)/lib -L$(BOOST_PATH)/lib
LIBS=		-lboost_filesystem -lboost_system -lOgreMain

COMPILE = 	$(CC) $(INC_DIRS) -c
LINK = 		$(CC) $(LIB_DIRS) -o

FILES = 	GameDriver.o GameManager.o RenderManager.o

all:		Ogre

Ogre:		$(FILES)
			$(LINK) Game $(FILES) $(LIBS)

GameManager.o:		GameManager.h GameManager.cpp
					$(COMPILE) $(GAME_PATH)/GameManager.cpp
RenderManager.o:	GameManager.h GameManager.cpp
					$(COMPILE) $(GAME_PATH)/RenderManager.cpp
GameDriver.o:		GameDriver.cpp
					$(COMPILE) $(GAME_PATH)/GameDriver.cpp