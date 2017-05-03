#ifndef PARSERS_GUIPARSER_H
#define PARSERS_GUIPARSER_H

#include "include/parser.h"
#include <vector>
#include <string>
#include <utility>

namespace asw{
	class interface;
	
	struct ui_parser_pair{
		std::string first;
		std::string second;
		ui_parser_pair();
		ui_parser_pair(const std::string &f, const std::string &s);
		ui_parser_pair(const ui_parser_pair &mp);
	};
	
	class GuiParser : public Parser{
		private:
			// To-Do:	Add helper methods.
			const static std::string main_tag; // Main tag!!!!
			const static std::string type; // Object type.
			
		//	void parse_resources(interface * my_interface, tinyxml2::XMLElement * resources_tag);
		//	void parse_defaults(interface * my_interface, tinyxml2::XMLElement * tooltips_tag);
		//	void parse_widgets(interface * my_interface);
		//	void parse_locations(interface * my_interface, tinyxml2::XMLElement * locations_tag);
			
			std::string buildWindow(interface * i, tinyxml2::XMLElement * window_element);
			
		public:
			GuiParser(const std::string &file);
			virtual ~GuiParser();
			
			virtual std::string getName();
			virtual std::string getType();
			
			void buildGui(interface * my_interface);
			
			std::vector<std::string> getFonts();
			std::vector<std::string> getSchemes();
			std::vector<ui_parser_pair> getDefaults();
	};
}

#endif