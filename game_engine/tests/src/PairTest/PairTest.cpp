#include "MyPair.h"

#include <string>
#include <iostream>

using namespace std;

int main(){
	my_pair pair_1("Hello String", 200);
	my_pair pair_2(pair_1);
	std::cout << "Pair 1 and Pair 2 test:\n";
	std::cout << "\tstring: " << pair_1.compare(pair_2.first()) << "\n";
	std::cout << "\tint:    " << pair_1.compare(pair_2.second()) << "\n";
//	my_pair * pair_2 = nullptr;
	my_pair * pair_3 = new my_pair();
	my_pair * pair_4 = new my_pair("Hello World!", 45);
	
	pair_3->first() = "This is a new string";
	
	std::cout << pair_3->first() << "\n"; 
	
	delete pair_3;
	delete pair_4;
	return 0;
}