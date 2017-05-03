#ifndef PARSERS_SCRIPTPARSER_H
#define PARSERS_SCRIPTPARSER_H

#include "Parser.h"

class scripter;

class script_parser : public parser{
	private:
		const static std::string my_tag; //
		const static std::string my_type;
	public:
		script_parser(const std::string &doc);
		~script_parser();

		virtual std::string get_name();
		virtual std::string get_type();
		virtual void parse_setup(scripter * scr);
};

#endif
