#ifndef	PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include "GameException.h"

class parse_error : public game_error{
	private:
		const std::string name = "parser";
	public:
		parse_error(const std::string &what_msg, uint32 ln_num);
		virtual ~parse_error();
		virtual const char * what();
};

#endif