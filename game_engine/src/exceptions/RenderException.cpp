#include "RenderException.h"

render_error::render_error(const string &msg, uint32 ln_number):
GameException(msg, name, ln_number){}

render_error::~render_error(){}

const char* render_error::what(){
	return game_error::what();
}