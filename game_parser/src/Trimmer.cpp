#include "Trimmer.h"

std::string trim_ws(const std::string &str){
	std::string sub_str(str);
	unsigned int str_length = sub_str.size();
	while(sub_str[0] == '	' || sub_str[0] == ' '){ // Remove front whitespace
		sub_str = sub_str.substr(1, str_length);
		str_length = sub_str.size();
	}
	while(sub_str[str_length-1] == '	' || sub_str[str_length-1] == ' '){ // Remove end whitespace
		sub_str = sub_str.substr(0, str_length-1);
		str_length = sub_str.size();
	}
	return sub_str;
}