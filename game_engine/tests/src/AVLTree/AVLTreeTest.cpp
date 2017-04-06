#include <iostream>
#include <string>

#include "AVLTree.h"

using namespace std;

int main(){
	avl_tree<int> my_tree;
	cout << "my_tree is created.\n";
	int one = 1;
	std::string a = "A";
	int two = 2;
	std::string b = "B";
	int three = 3;
	std::string c = "C";
	int four = 4;
	std::string d = "D";
	int five = 5;
	std::string e = "E";
	cout << "Adding nodes.\n";
	my_tree.add(one, a);
	cout << "A added.\n";
	my_tree.add(two, b);
	cout << "B added.\n";
	my_tree.add(three, e);
	cout << "E added.\n";
	my_tree.add(four, d);
	cout << "D added.\n";
	my_tree.add(five, c);
	cout << "C added.\n";
	my_tree.print_tree();
	cout << "\nAdds Check Out\n\n";
	string str("C");
	int C5 = *my_tree.pop(str);
	cout << "Popped: ";
	cout << C5 << "\n";
	str = "B";
	int B1 = *my_tree.pop(str);
	cout << "Popped: " << B1 << "\n";
	my_tree.print_tree();
	return 0;
}
