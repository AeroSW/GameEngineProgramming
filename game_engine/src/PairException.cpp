#include "PairException.h"

#include <iostream>

pair_err::pair_err(const char * msg):
std::runtime_error(msg){
	line_number = nullptr;
	file = nullptr;
}

pair_err::pair_err(const char * msg, unsigned int ln, const char * from):
std::runtime_error(msg){
	line_number = new unsigned int(ln);
	file = new std::string(from);
}

pair_err::~pair_err(){
	if(line_number != nullptr)
		delete line_number;
	if(file != nullptr)
		delete file;
	line_number = nullptr;
	file = nullptr;
}

const char * pair_err::what(){
	std::string what_msg(std::runtime_error::what());
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	if(line_number != nullptr && file != nullptr){
		std::cout << "=======================================" << std::endl;
		std::string the_file(*file);
		static std::string tab("\t");
		static std::string space(" ");
		static std::string new_ln("\n");
		unsigned int i(*line_number);
		std::string i_str = std::to_string(i);
		what_msg = (what_msg + new_ln + tab + the_file + space + i_str);
	}
	std::cout << "?????????????????????????????????????????" << std::endl;
	return what_msg.c_str();
}