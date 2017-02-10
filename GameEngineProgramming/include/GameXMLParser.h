/*
 * XML.h
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#ifndef GAMEXMLPARSER_H_
#define GAMEXMLPARSER_H_

class Level;

#include "UnsignedTypes.h"
#include "Level.h"
#include <memory>
#include <string>
#include <vector>

class xml_parser{
	private:
		enum states{
			NAME,
			MESH,
			OBJECT,
			QUATERNION,
			TRANSLATION,
			ROTATION,
			SCALING,
			SEARCH
		};

		std::vector<std::string> objects;

		std::vector<std::string> * retrieve_files(std::ifstream &file);
		uint64 parse_level_count(std::ifstream &file, const std::string &tag);
		std::string parse_level_file(std::ifstream &file, const std::string &tag, const std::string &search_tag);
		/**
		 * Function Name:	trim_ws or trim whitespace
		 * Parameters:		Standard C++ Library string
		 * Returns:			Standard C++ Library string
		 * Description:
		 * 		Takes a string and trims the whitespace off on the front
		 * 		and end of the string.
		 */
		std::string trim_ws(const std::string &str);
		static std::shared_ptr<level> parse_level(std::string filename);

	protected:

	public:
		xml_parser();
		~xml_parser();
		/**
		 * Function Name:	parse_game
		 * Parameters:		Standard C++ Library string
		 * Returns:			Returns a Standard C++ Library vector which
		 * 						contains Standard C++ Library shared_ptr
		 * 						objects which are template level object
		 * 						pointers.
		 * Description:
		 * 		This function takes a path to an XML file as a parameter.
		 * 		It parses the file and reads the contents of it to open
		 * 		numerous other XML files, each containing a new level.
		 * 		It then constructs these levels and returns their
		 * 		references in a vector.
		 */
		std::vector<std::shared_ptr<level> > parse_game(std::string &filepath);
		static bool write_file(std::string filename, std::vector<level*>);
};


#endif /* GAMEXMLPARSER_H_ */
