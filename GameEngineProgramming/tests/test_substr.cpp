/*
 * test_substr.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: uge
 */

#include <iostream>
#include <string>

using namespace std;

int main(){
	string v = "Hello";
	string empty = v.substr(5,v.size());
	cout << "String Size:\t" << empty.size() << endl;
	cout << "String:\t" << empty << endl;
}
