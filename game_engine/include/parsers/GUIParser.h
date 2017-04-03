#ifndef PARSERS_GUIPARSER_H
#define PARSERS_GUIPARSER_H

#include "Parser.h"
#include <vector>
#include <string>
#include <utility>

class interface;

struct my_pair{
	std::string first;
	std::string second;
	my_pair();
	my_pair(const std::string &f, const std::string &s);
	my_pair(const my_pair &mp);
};

class guiparser : public parser{
	private:
		// To-Do:	Add helper methods.
		const static std::string main_tag; // Main tag!!!!
		const static std::string type; // Object type.
		
	//	void parse_resources(interface * my_interface, tinyxml2::XMLElement * resources_tag);
	//	void parse_defaults(interface * my_interface, tinyxml2::XMLElement * tooltips_tag);
	//	void parse_widgets(interface * my_interface);
	//	void parse_locations(interface * my_interface, tinyxml2::XMLElement * locations_tag);
		
		std::string build_window(interface * i, tinyxml2::XMLElement * window_element);
		
	public:
		guiparser(const std::string &file);
		virtual ~guiparser();
		
		virtual std::string get_name();
		virtual std::string get_type();
		
		void build_gui(interface * my_interface);
		
		std::vector<std::string> get_fonts();
		std::vector<std::string> get_schemes();
		std::vector<my_pair> get_defaults();
};

#endif