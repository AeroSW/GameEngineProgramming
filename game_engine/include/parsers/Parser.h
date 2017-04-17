#ifndef PARSERS_PARSER_H
#define PARSERS_PARSER_H

#include "tinyxml2.h"
#include "Functions.h"

#include <string>

class parser{
	private:
		std::string main_tag;
	protected:
		std::string file_name;
		
		tinyxml2::XMLDocument * doc;
		tinyxml2::XMLElement * main_element;
		
		tinyxml2::XMLElement * get_main_element();
		
		parser(const std::string &document, const std::string &tag);
		
	public:
		virtual ~parser();
		
		virtual std::string get_name();
		virtual std::string get_type() = 0;
		virtual void load_file(const std::string &document);
};

#endif