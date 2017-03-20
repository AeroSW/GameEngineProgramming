#ifndef	PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include "GameException.h"

class parse_error_g : public game_error{
	private:
		const std::string name = "game_parser";
	public:
		parse_error_g(const std::string &what_msg, uint32 ln_num);
		virtual ~parse_error_g();
		virtual const char * what();
};

class parse_error_l : public game_error{
	private:
		const std::string name = "level_parser";
	public:
		parse_error_l(const std::string &what_msg, uint32 ln_num);
		virtual ~parse_error_l();
		virtual const char * what();
};

#endif