#include "MyPair.h"

my_pair::my_pair():
pair_t<std::string,int>(){}

my_pair::my_pair(const std::string &str, const int my_int):
pair_t<std::string,int>(str, my_int){}

my_pair::my_pair(std::string * str, int * my_int):
pair_t<std::string,int>((const std::string) *str, (const int) *my_int){}

my_pair::my_pair(const my_pair &mp):
pair_t<std::string,int>(mp){}

my_pair::my_pair(my_pair * mp):
pair_t<std::string,int>(mp){}

int my_pair::compare(std::string &str){
	std::string &my_str = first();
	return my_str.compare(str);
}

int my_pair::compare(int &i){
	int &my_int = second();
	return my_int - i;
}