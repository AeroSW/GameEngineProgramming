#ifndef PARSER_H
#define PARSER_H

//#include "tinyxml2.h"
#include "functions.h"

#include <string>

class tinyxml2::XMLDocument;
class tinyxml2::XMLElement;

class Parser{
	private:
		std::string main_tag;
	protected:
		std::string file_name;
		
		tinyxml2::XMLDocument * doc;
		tinyxml2::XMLElement * main_element;
		
		tinyxml2::XMLElement * getMainElement();
		
		Parser(const std::string &document, const std::string &tag);
		
	public:
		virtual ~Parser();
		
		virtual std::string getName();
		virtual std::string getType() = 0;
		virtual void loadFile(const std::string &document);
};

#endif