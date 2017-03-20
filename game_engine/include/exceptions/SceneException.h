#ifndef SCENEEXCEPTION_H
#define SCENEEXCEPTION_H

#include "GameException.h"

class scene_error : game_error{
	private:
		const std::string name = "scene";
	public:
		scene_error(const std::string &what_msg, uint32 line_num);
		virtual ~scene_error();
		virtual const char * what();
};

#endif