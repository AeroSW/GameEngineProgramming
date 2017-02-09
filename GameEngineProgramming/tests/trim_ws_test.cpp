/*
 * trim_ws_test.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: uge
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string trim_ws(const string &str){
	std::string sub_str(str);
	unsigned int str_length = sub_str.size();
	while(sub_str[0] == '	' || sub_str[0] == ' '){ // Remove front whitespace
		sub_str = sub_str.substr(1, str_length);
		str_length = sub_str.size();
	}
	while(sub_str[str_length-1] == '	' || sub_str[str_length-1] == ' '){
		sub_str = sub_str.substr(0, str_length-1);
		str_length = sub_str.size();
	}
	return sub_str;
}

int main(){
	vector<string> ex_strs;
	ex_strs.push_back("\t\tHello Tab 1\t\t");
	ex_strs.push_back("		Hello Tab 2		");
	ex_strs.push_back("\s\sHello Space 1\s\s");
	ex_strs.push_back("  Hello Space 2  ");
	ex_strs.push_back("\t\sHello Mix 1\t\s");
	ex_strs.push_back("\s\tHello Mix 2\t\s");
	ex_strs.push_back("\t\sHello Mix 3\s\t");
	ex_strs.push_back("\s\tHello Mix 4\s\t");

	for(int c = 0; c < ex_strs.size(); c++){
		cout << trim_ws(ex_strs[c]) << endl;
	}

	return 0;
}


