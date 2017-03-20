#include "GameException.h"

game_error::game_error(const std::string &what_msg, const std::string &c_name, uint32 line_num):
runtime_error(what_msg){
	line_number = line_num;
	class_name = c_name;
}

game_error::~game_error(){}

const char* game_error::what(){
	std::string full_msg = std::string(runtime_error::what()) + " in class " + class_name + " at line " + std::to_string(line_number);
	return full_msg.c_str();
}