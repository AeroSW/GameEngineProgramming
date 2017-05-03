#include "include/parser.h"
#include "include/except_macro.h"
#include "tinyxml2.h"

tinyxml2::XMLElement * asw::Parser::getMainElement(){
	if(doc != nullptr){
		if(main_element == nullptr){
			main_element = doc->FirstChildElement(main_tag.c_str());
			if(main_element == nullptr) THROW_TRACE(main_tag + " tag was not found.");
		}
		return main_element;
	}
	THROW_TRACE("Document needs to be loaded.");
}

asw::Parser::Parser(const std::string &document, const std::string &tag):
main_tag(tag), file_name(document){
	doc = nullptr;
	main_element = nullptr;
	load_file(file_name);
}

asw::Parser::~Parser(){
	if(doc != nullptr){
		doc->Clear();
		main_element = nullptr;
		delete doc;
		doc = nullptr;
	}
}

std::string asw::Parser::getName(){
	return file_name;
}

void asw::Parser::loadFile(const std::string &document){
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