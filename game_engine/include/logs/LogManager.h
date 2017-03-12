// Filename:	LogManager
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <fstream>
#include <sstream>

#include "UnsignedTypes.h"


class logger{
	private:
		std::stringstream log_buffer;
		std::ofstream log_stream;

		void flush();
		
		std::string timestamp();
	public:
		logger(const std::string &log_name);
		virtual ~logger();

		void problem(const std::string &filename_str, uint32 ln_number, const char* msg);
		void comment(const std::string &comment_str);
};

#endif
