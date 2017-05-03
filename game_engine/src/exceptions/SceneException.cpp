#include "SceneException.h"

scene_error::scene_error(const std::string &msg, uint32 ln):
GameError(msg, name, ln){}

scene_error::~scene_error(){}

const char * scene_error::what(){
	return GameError::what();
}