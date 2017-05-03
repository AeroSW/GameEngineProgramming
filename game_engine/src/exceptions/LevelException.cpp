#include "LevelException.h"

level_error::level_error(const std::string &msg, uint32 ln_number):
GameError(msg, name, ln_number){}

level_error::~level_error(){}

const char* level_error::what(){
	return GameError::what();
}