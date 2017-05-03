#include "GameParser.h"

#include "GameException.h"
#include "SudoExcept.h"

const std::string gameparser::my_tag = "game";
const std::string gameparser::my_type = "gameparser";

gameparser::gameparser(const std::string &doc_name):
parser(doc_name, my_tag){}

gameparser::~gameparser(){}

std::string gameparser::get_level(const std::string &skey){
	bool flag = false;
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	tinyxml2::XMLElement * lvl = game->FirstChildElement("level"); // Grab the first level tag.
	if(lvl == nullptr){ // Check if file is properly formatted.
		THROW_TRACE("Game needs atleast 1 level.");
	}
	std::string result; // Initialize string.
	for(;lvl != nullptr; lvl = lvl->NextSiblingElement("level")){ // Loop over all elements with "level" tag.
		const char * lvl_attr = lvl->Attribute("name"); // Get the name attribute from the tag.
		if(lvl_attr == nullptr){ // Check if the file is properly formatted.
			THROW_TRACE("Level needs a name.");
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

std::string gameparser::get_gui(const std::string &skey){
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	tinyxml2::XMLElement * gui = game->FirstChildElement("gui"); // Grab the first level tag.
	std::string result = ""; // Initialize string.
	for(;gui != nullptr; gui = gui->NextSiblingElement("gui")){ // Loop over all elements with "level" tag.
		const char * gui_attr = gui->Attribute("name"); // Get the name attribute from the tag.
		if(gui_attr == nullptr){ // Check if the file is properly formatted.
			THROW_TRACE("GUI needs a name.");
		}
		std::string val(gui_attr); // Get the value of the attribute(the key).
		trim(val);
		if(val.compare(skey) == 0){ // Compare the search key with the attribute's value.
			std::string str(gui->GetText()); // Get the file name from the element text.
			trim(str);
			result = str; // Set it to the initialized string.
			break; // Leave the loop.
		}
	}
	return result;
}

std::string gameparser::get_physics(const std::string &skey){
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	for(tinyxml2::XMLElement * p_tag = game->FirstChildElement("physics"); p_tag != nullptr; p_tag = p_tag->NextSiblingElement("physics")){
		const char * name_attr = p_tag->Attribute("name");
		if(name_attr == nullptr) THROW_TRACE("Physics needs a name.");
		std::string val(name_attr);
		trim(val);
		if(val.compare(skey) == 0){
			std::string text(p_tag->GetText());
			trim(text);
			return text;
		}
	}
	return "";
}

std::vector<std::string> gameparser::get_levels(){
	std::vector<std::string> levels;
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	tinyxml2::XMLElement * lvl = game->FirstChildElement("level"); // Grab the first level tag.
	if(lvl == nullptr){
		THROW_TRACE("Game needs atleast 1 level.");
	}
	for(;lvl != nullptr; lvl = lvl->NextSiblingElement("level")){ // Loop over level tags.
		std::string lvl_file(lvl->GetText()); // Get the filename.
		trim(lvl_file);
		levels.push_back(lvl_file); // Push it onto the vector.
	}
	return levels; // Return the vector.
}

std::vector<std::string> gameparser::get_guis(){
	std::vector<std::string> guis;
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	for(tinyxml2::XMLElement * gui = game->FirstChildElement("gui"); gui != nullptr; gui = gui->NextSiblingElement("gui")){
		std::string gui_file(gui->GetText());
		trim(gui_file);
		guis.push_back(gui_file);
	}
	return guis;
}

std::string gameparser::get_name(){
	tinyxml2::XMLElement * game;
	try{
		game = get_main_element();
	}
	catch(GameError &e){
		THROW_TRACE(std::string(e.what()));
	}
	const char * game_attr = game->Attribute("name");
	if(game_attr == nullptr){
		THROW_TRACE("Game needs a name.");
	}
	std::string name(game_attr);
	trim(name);
	return name;
}
std::string gameparser::get_type(){
	return my_type;
}