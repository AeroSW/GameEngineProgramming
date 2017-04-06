CC		= g++
CFLAGS	= -std=c++11
INC		= -I../include
SRC		= ./src
M_INC	= ../include
M_OBJ	= ../obj

defualt	:	all

all		:
	$(MAKE) pair
	$(MAKE) tree

pair	: $(SRC)/PairTest/MyPair.h $(SRC)/PairTest/MyPair.cpp ./src/PairTest/PairTest.cpp
	$(CC) $(CFLAGS) -o pair_exe ./src/PairTest/PairTest.cpp $(INC) ./src/PairTest/MyPair.cpp $(M_OBJ)/PairException.o
tree	: $(SRC)/AVLTree/AVLTreeTest.cpp
	$(CC) $(CFLAGS) -o tree_exe ./src/AVLTree/AVLTreeTest.cpp $(INC) $(M_OBJ)/PairException.o
