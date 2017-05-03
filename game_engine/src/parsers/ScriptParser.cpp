#include "GameException.h"
#include "SudoExcept.h"

#include "ScriptParser.h"
#include "Scripter.h"

const std::string script_parser::my_tag = "script";
const std::string script_parser::my_type = "script_parser";

script_parser::script_parser(const std::string &doc):
parser(doc, my_tag){}

script_parser::~script_parser(){}

std::string script_parser::get_name(){
	tinyxml2::XMLElement * main_tag = get_main_element();
	const char * name_attr = main_tag->Attribute("name");
	if(name_attr == nullptr) THROW_TRACE("<script> tag needs a 'name' attribute.");
	return std::string(name_attr);
}

std::string script_parser::get_type(){
	return my_type;
}

void script_parser::parse_setup(scripter * scr){
	tinyxml2::XMLElement * main_tag = get_main_element();
	tinyxml2::XMLElement * scripts_tag = main_tag->FirstChildElement("scripts");
	if(scripts_tag == nullptr) THROW_TRACE("<scripts> tag is needed for script parsing.");
	for(tinyxml2::XMLElement * script_tag = scripts_tag->FirstChildElement("file"); script_tag != nullptr; script_tag = script_tag->NextSiblingElement("file")){
		const char * name_attr = script_tag->Attribute("name");
		const char * file_attr = script_tag->Attribute("path");
		if(name_attr == nullptr) THROW_TRACE("<file> tag needs 'name' attribute.");
		if(file_attr == nullptr) THROW_TRACE("<file> tag needs 'path' attribute.");
		scr->add_script(std::string(name_attr), std::string(file_attr));
	}
	tinyxml2::XMLElement * methods_tag = main_tag->FirstChildElement("methods");
	if(methods_tag == nullptr) THROW_TRACE("<methods> tag is needed for method parsing.");
	for(tinyxml2::XMLElement * method = methods_tag->FirstChildElement("method"); method != nullptr; method = method->NextSiblingElement("method")){
		const char * class_attr = method->Attribute("class");
		if(class_attr == nullptr) THROW_TRACE("<method> tag needs a 'class' attribute.");
		scr->import_methods(std::string(class_attr));
	}
}
