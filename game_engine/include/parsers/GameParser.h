// Filename:	GameParser
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017

#ifndef GAMEPARSER_H
#define GAMEPARSER_H

#include "ParserException.h"

#include "tinyxml2.h"

#include <string>

class gameparser{
	private:
		tinyxml2::XMLDocument * doc;
		tinyxml2::XMLElement * game_element;
		tinyxml2::XMLElement * get_game_element();

		std::vector<std::string> parse_doc();
	public:
		/**
			Constructor for gameparser
			Preconditions:	An XML document with the given
					contents of "doc_name" must exist.
			Parameters:
				const std::string &doc_name
					The path and name for the xml
					document containing the details
					for the game being loaded.
			Postconditions:
				A tinyxml2::XMLDocument pointer reference
				is created.
		 */
		gameparser(const std::string &doc_name);
		/**
			Destructor for gameparser
		 */
		virtual ~gameparser();
		/**
			Function:	get_level(const std::string &skey)
			Preconditions:	XMLDocument * doc must be a valid
					reference to a game document.
			Parameters:
				const std::string &skey
					A string key to match with a level
					name.

					ex. <level key=001> level_1.xml </level>
					    get_level("001") will return level_1.xml
			Returns:	Returns the filename for the file based off the
					given search key.
		 */
		virtual std::string get_level(const std::string &skey);
		/**
			Function:	get_levels()
			Preconditions:	XMLDocument * doc must be a valid
					reference to a game document.
			Parameters:	None
			Returns:	C++ Standard Vector containing
					C++ Standard string objects which
					reference to the xml document names
					for the levels.
		 */
		virtual std::vector<std::string> get_levels();
		/**
		 	Function:	get_name()
			Preconditions:	XMLDocument * doc must be a valid 
					reference to a game document.
			Parameters:	None
			Returns:	C++ Standard string object
				The game's name is parsed and returned.
		 */
		virtual std::string get_name();
		
		virtual void load_file(const std::string &doc_name);
};

#endif

