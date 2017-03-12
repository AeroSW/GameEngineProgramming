#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H

#include "GameException.h"

class input_error : public game_error{
	private:
		const std::string name = "input";
	public:
		input_error(const std::string &what_msg, uint32 ln_num);
		virtual ~input_error();
		virtual const char * what();
};

#endif