#include "GameParser.h"
#include "Functions.h"
#include "ParseException.h"

gameparser::gameparser(const std::string &doc_name){
	doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError flag = doc->LoadFile(doc_name.c_str());
	
	if(flag != tinyxml2::XML_SUCCESS){
		throw parse_error_g("Could not load XML file.", 8);
	}
}

gameparser::~gameparser(){
	doc->Clear();
	game_element = nullptr;
	delete doc;
	doc = nullptr;
}

std::string gameparser::get_level(const std::string &skey){
	bool flag = false;
	tinyxml2::XMLElement * game = get_game_element();
	tinyxml2::XMLElement * lvl = game->FirstChildElement("level"); // Grab the first level tag.
	if(lvl == nullptr){ // Check if file is properly formatted.
		throw parse_error_g("Game needs atleast 1 level.", 24);
	}
	std::string result; // Initialize string.
	for(;lvl != nullptr; lvl = lvl->NextSiblingElement("level")){ // Loop over all elements with "level" tag.
		const char * lvl_attr = lvl->Attribute("name"); // Get the name attribute from the tag.
		if(lvl_attr == nullptr){ // Check if the file is properly formatted.
			throw parse_error_g("Level needs a name.", 30);
		}
		std::string val(lvl_attr); // Get the value of the attribute(the key).
		trim(val);
		if(val.compare(skey) == 0){ // Compare the search key with the attribute's value.
			flag = true; // They match, so set flag to true.
			std::string str(lvl->GetText()); // Get the file name from the element text.
			trim(str);
			result = str; // Set it to the initialized string.
			break; // Leave the loop.
		}
	}
	if(flag) // If we found the search key
		return result; // Return the file name.
	return ""; // Nothing was found.
}

std::vector<std::string> gameparser::get_levels(){
	std::vector<std::string> levels;
	tinyxml2::XMLElement * game = get_game_element();
	tinyxml2::XMLElement * lvl = game->FirstChildElement("level"); // Grab the first level tag.
	if(lvl == nullptr){
		throw parse_error_g("Game needs atleast 1 level.", 52);
	}
	for(;lvl != nullptr; lvl = lvl->NextSiblingElement("level")){ // Loop over level tags.
		std::string lvl_file(lvl->GetText()); // Get the filename.
		trim(lvl_file);
		levels.push_back(lvl_file); // Push it onto the vector.
	}
	return levels; // Return the vector.
}

std::string gameparser::get_name(){
	tinyxml2::XMLElement * game = get_game_element();
	const char * game_attr = game->Attribute("name");
	if(game_attr == nullptr){
		throw parse_error_g("Game needs a name.", 66);
	}
	std::string name(game_attr);
	trim(name);
	return name;
}

tinyxml2::XMLElement * gameparser::get_game_element(){
	if(game_element == nullptr){
		game_element = doc->FirstChildElement("game");
		if(game_element == nullptr){
			throw parse_error_g("Game file is improperly formatted.", 77);
		}
	}
	return game_element;
}

void gameparser::load_file(const std::string &doc_name){
	tinyxml2::XMLDocument * new_doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError flag = new_doc->LoadFile(doc_name.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		delete new_doc;
		throw parse_error_g("Could not load XML file.", 88); //	Throwing this first prevents doc\
																from becoming null if the new \
																document does not exist.
	}
	if(doc != nullptr){
		doc->Clear();
		game_element = nullptr;
		delete doc;
		doc = nullptr;
	}
	doc = new_doc;
}
