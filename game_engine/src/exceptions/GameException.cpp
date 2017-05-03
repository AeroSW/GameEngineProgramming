#include "GameException.h"

#include <iostream>

GameError::GameError(const std::string &what_msg, const std::string &file, uint32 line):
runtime_error(what_msg){
	line_number = line;
	file_name = file;
}

GameError::~GameError(){}

const char* GameError::what(){
//	std::string full_msg = std::string(runtime_error::what()) + " in class " + class_name + " at line " + std::to_string(line_number);
	std::string msg = std::string(runtime_error::what()) + "\n\t" + file_name + ":" + std::to_string(line_number);
	std::cout << msg << std::endl;
	return msg.c_str();
}