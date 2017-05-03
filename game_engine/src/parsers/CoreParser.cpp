#include "CoreParser.h"

#include "Core.h"

#include "Functions.h"
#include "MyEnums.h"
#include "UnsignedTypes.h"

#include "GameException.h"
#include "SudoExcept.h"

#include <iostream>
#include <vector>

const std::string coreparser::tag	= "core";
const std::string coreparser::type	= "coreparser";

coreparser::coreparser(const std::string &dox):
parser(dox, tag){}

coreparser::~coreparser();

void coreparser::construct_engine(core * core_manager){
	tinyxml2::XMLElement * my_element = get_main_element();
	tinyxml2::XMLElement * logger_element = my_element->FirstChildElement("logger");
	tinyxml2::XMLElement * render_element = my_element->FirstChildElement("render");
	tinyxml2::XMLElement * script_element = my_element->FirstChildElement("script");
	tinyxml2::XMLElement * audio_element = my_element->FirstChildElement("audio");
	tinyxml2::XMLElement * inputs_element = my_element->FirstChildElement("inputs");
	if(logger_element == nullptr) THROW_TRACE("<logger> tag is needed with log text document.");
	if(render_element == nullptr) THROW_TRACE("<render> tag is needed for render manager creation.");
	if(script_element == nullptr) THROW_TRACE("<script> tag is needed for core manager setup.");
	// Initialize the logger
	const char * file_attr = logger_element->Attribute("file");
	if(file_attr == nullptr) THROW_TRACE("'file' attribute is needed for logger tag.");
	string file_str(file_attr);
	trim(file_str);
	core_manager->create_logger(file_str); // Initialize the logger.
	// Initialize the renderer
	file_attr = render_element->Attribute("file");
	if(file_attr == nullptr) THROW_TRACE("'file' attribute is needed for render tag.");
	file_str = string(file_attr);
	trim(file_str);
	try{
		core_manager->create_render(file_str);
	}
	catch(GameError &e){
		THROW_TRACE(e.what());
	}
	// Initialize the scripter
	file_attr = script_element->Attribute("file");
	if(file_attr == nullptr) THROW_TRACE("'file' attribute is needed for script tag.");
	file_str = string(file_attr);
	trim(file_str);
	try{
		core_manager->create_scripter(file_str);
	}
	catch(GameError &e){
		THROW_TRACE(e.what());
	}
	// Check if there is an audio manager.
	if(audio_element != nullptr){
		// Since there is an audio tag, initialize the audio manager.
		file_attr = audio_element->Attribute("file");
		if(file_attr == nullptr) THROW_TRACE("'file' attribute is needed for audio tag.");
		file_str = string(file_attr);
		trim(file_str);
		core_manager->create_audio(file_str);
	}
	if(inputs_element != nullptr){
		for(tinyxml2::XMLElement * input_element = inputs_element->FirstChildElement("input"); input_element != nullptr; input_element = input_element->NextSiblingElement("input")){
			const char * type_attr = input_element->Attribute("type");
			string type_str(type_attr);
			trim(type_str);
			if(type_str.compare("mouse") == 0){
				create_input(input_t::MOUSE, "");
			}
			else{
				file_attr = input_element->Attribute("file");
				file_str = string(file_attr);
				trim(file_str);
				if(type_str.compare("keyboard") == 0){
					core_manager->create_input(input_t::KEYBOARD, file_str);
				}
				else if(type_str.compare("xbox1") == 0){
					core_manager->create_input(input_t::XBOX1, file_str);
				}
				else if(type_str.compare("dualshock4") == 0){
					core_manager->create_input(input_t::DUALSHOCK4, file_str);
				}
				else{
					THROW_TRACE("Invalid input type.");
				}
			}
		}
	}
}
