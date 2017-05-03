#include "Parser.h"
#include "GameException.h"
#include "SudoExcept.h"

tinyxml2::XMLElement * parser::get_main_element(){
	if(doc != nullptr){
		if(main_element == nullptr){
			main_element = doc->FirstChildElement(main_tag.c_str());
			if(main_element == nullptr) THROW_TRACE(main_tag + " tag was not found.");
		}
		return main_element;
	}
	THROW_TRACE("Document needs to be loaded.");
}

parser::parser(const std::string &document, const std::string &tag):
main_tag(tag), file_name(document){
	doc = nullptr;
	main_element = nullptr;
	load_file(file_name);
}

parser::~parser(){
	if(doc != nullptr){
		doc->Clear();
		main_element = nullptr;
		delete doc;
		doc = nullptr;
	}
}

std::string parser::get_name(){
	return file_name;
}

void parser::load_file(const std::string &document){
	tinyxml2::XMLDocument * new_doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError flag = new_doc->LoadFile(document.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		delete new_doc;
		if(doc == nullptr) THROW_TRACE("Initial file, " + document + " needs to exist.");
		return;
	}
	if(doc != nullptr){
		doc->Clear();
		main_element = nullptr;
		delete doc;
		doc = nullptr;
	}
	doc = new_doc;
}