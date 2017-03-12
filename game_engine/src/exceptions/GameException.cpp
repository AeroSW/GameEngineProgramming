#include "GameException.h"

game_error::game_error(const std::string &what_msg, const std::string &c_name, uint32 line_num):
runtime_error(what_msg){
	line_number = line_num;
	class_name = c_name;
}

game_error::~game_error(){}

const char* game_error::what(){
	std::string full_msg = runtime_error::what() + " in class " + class_name + " at line " + line_num;
	return full_msg.to_cstr();
}