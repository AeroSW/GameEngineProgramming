// Filename:	GameParser
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017

#ifndef PARSERS_GAMEPARSER_H
#define PARSERS_GAMEPARSER_H

#include "Parser.h"

#include <vector>
#include <string>

class gameparser : public parser{
	private:
	//	tinyxml2::XMLDocument * doc;
	//	tinyxml2::XMLElement * game_element;
	//	tinyxml2::XMLElement * get_game_element();
		const static std::string my_tag;
		const static std::string my_type;
		
	//	std::vector<std::string> parse_doc();
	
	public:
		gameparser(const std::string &doc_name);
		virtual ~gameparser();
		virtual std::string get_level(const std::string &skey);
		virtual std::string get_gui(const std::string &skey);
		virtual std::string get_physics(const std::string &skey);
		virtual std::vector<std::string> get_levels();
		virtual std::vector<std::string> get_guis();
		virtual std::string get_name(); // Overloaded function
		virtual std::string get_type();
		
	//	virtual void load_file(const std::string &doc_name);
};

#endif

