#include "ParseException.h"

parse_error_g::parse_error_g(const std::string &what_msg, uint32 ln_num):
game_error(msg, name, ln_num){}
parse_error_l::parse_error_l(const std::string &what_msg, uint32 ln_num):
game_error(msg, name, ln_num){}

parse_error_g::~parse_error_g(){}
parse_error_l::~parse_error_l(){}

const char * parse_error_g::what(){
	return game_error::what();
}
const char * parse_error_l::what(){
	return game_error::what();
}