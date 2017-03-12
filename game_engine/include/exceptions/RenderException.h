#ifndef RENDEREXCEPTION_H
#define RENDEREXCEPTION_H

#include "GameException.h"
#include <string>
#include "UnsignedTypes.h"

class render_error : public game_error{
	private:
		const std::string name = "render";
	public:
		render_error(const std::string &what_msg, uint32 ln_num);
		virtual ~render_error();
		virtual const char * what();
};

#endif