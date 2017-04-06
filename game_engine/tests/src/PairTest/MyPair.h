#ifndef TESTS_SRC_PAIRTEST_MYPAIR_H
#define TESTS_SRC_PAIRTEST_MYPAIR_H

#include "Pair.h"

#include <string>

class my_pair : public pair_t<std::string, int>{
	private:
		
	public:
		my_pair();
		my_pair(const std::string &str, int my_i);
		my_pair(std::string * str, int * my_int);
		my_pair(const my_pair &mp);
		my_pair(my_pair * mp);
		int compare(std::string &str);
		int compare(int &integer);
};

#endif