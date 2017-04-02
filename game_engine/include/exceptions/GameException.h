#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <stdexcept>
#include <string>
#include "UnsignedTypes.h"

class game_error : public std::runtime_error{
	protected:
		uint32 line_number;
		std::string file_name;
	public:
		game_error(const std::string &what_msg, const std::string &file, uint32 line_number);
		virtual ~game_error();
		virtual const char * what();
};

#endif