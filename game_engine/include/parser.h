#ifndef ASW_INCLUDE_PARSER_H
#define ASW_INCLUDE_PARSER_H

//#include "tinyxml2.h"
#include "functions.h"

#include <string>

// tinyxml2 forward declarations
namespace tinyxml2{
	class XMLDocument;
	class XMLElement;
}

namespace asw{
	class Parser{
		private:
			std::string main_tag;
			tinyxml2::XMLElement * main_element;
			
		protected:
			std::string file_name;
			
			tinyxml2::XMLDocument * doc;
			tinyxml2::XMLElement * getMainElement();
			
			Parser(const std::string &document, const std::string &tag);
			
		public:
			virtual ~Parser();
			
			virtual std::string getName();
			virtual std::string getType() = 0;
			virtual void loadFile(const std::string &document);
	};
}
#endif