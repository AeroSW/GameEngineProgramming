#include "RenderException.h"

render_error::render_error(const std::string &msg, uint32 ln_number):
GameError(msg, name, ln_number){}

render_error::~render_error(){}

const char* render_error::what(){
	return GameError::what();
}