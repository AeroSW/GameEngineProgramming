#ifndef LEVELEXCEPTION_H
#define LEVELEXCEPTION_H

#include "GameException.h"
#include <string>
#include "UnsignedTypes.h"

class level_error : public game_error{
	private:
		const std::string name = "level";
	public:
		level_error(const std::string &what_msg, uint32 ln_num);
		virtual ~level_error();
		virtual const char * what();
};

#endif