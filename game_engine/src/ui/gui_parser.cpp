#include "include/ui/gui_parser.h"
#include "include/ui/user_interface.h"

#include "tinyxml2.h"

//#include "game_exception.h"
#include "except_macros.h"

#include <iostream>

const std::string asw::GuiParser::main_tag = "gui";
const std::string asw::GuiParser::type = "GuiParser";

asw::ui_parser_pair::ui_parser_pair():
first(""), second(""){}
asw::ui_parser_pair::ui_parser_pair(const std::string &f, const std::string &s):
first(f),second(s){}
asw::ui_parser_pair::ui_parser_pair(const ui_parser_pair &mp):
first(mp.first),second(mp.second){}

asw::GuiParser::GuiParser(const std::string &file):
parser(file, main_tag){}

asw::GuiParser::~GuiParser(){}

void asw::GuiParser::buildGui(interface * my_interface){
	
	tinyxml2::XMLElement * tag = getMainElement();
	tinyxml2::XMLElement * widgets_tag = tag->FirstChildElement("widgets");
	for(tinyxml2::XMLElement * window_tag = widgets_tag->FirstChildElement("window"); window_tag != nullptr; window_tag = window_tag->NextSiblingElement("window")){
		std::string child_name = buildWindow(my_interface, window_tag);
		my_interface->addRootChild(child_name);
	}
}

std::string asw::GuiParser::buildWindow(interface * my_interface, tinyxml2::XMLElement * my_window){
	const char * name_cstr = my_window->Attribute("name"); // Grab the name, type, and look attributes to build the window
	if(name_cstr == nullptr) THROW_TRACE("<window> requires a 'name' attribute.");	// Check if they exist, if not, then throw error.
	const char * type_cstr = my_window->Attribute("type");
	if(type_cstr == nullptr) THROW_TRACE("<window> requires a 'type' attribute.");
	const char * look_cstr = my_window->Attribute("look");
	if(look_cstr == nullptr) THROW_TRACE("<window> requires a 'look' attribute.");
	
	tinyxml2::XMLElement * loc_tag = my_window->FirstChildElement("location"); // Grab <location> and <area>
	if(loc_tag == nullptr) THROW_TRACE("<location> must be present within <window> tree."); // Check if they exist, if not, throw error.
	tinyxml2::XMLElement * area_tag = my_window->FirstChildElement("area");
	if(area_tag == nullptr) THROW_TRACE("<area> must be present within <window> tree.");
	
	const char * loc_abs = loc_tag->Attribute("absolute"); // Grab <location>'s and <area>'s absolute and relative attributes
	if(loc_abs == nullptr) THROW_TRACE("<location> needs an 'absolute' attribute."); // Check if they exist, if not, then throw error.
	const char * loc_rel = loc_tag->Attribute("relative");
	if(loc_abs == nullptr) THROW_TRACE("<location> needs an 'relative' attribute.");
	const char * area_abs = area_tag->Attribute("absolute");
	if(loc_abs == nullptr) THROW_TRACE("<area> needs an 'absolute' attribute.");
	const char * area_rel = area_tag->Attribute("relative");
	if(loc_abs == nullptr) THROW_TRACE("<area> needs an 'relative' attribute.");
	
	std::string name_str(name_cstr); // name, type, and look exist, so convert them to std::string and trim whitespace off.
	trim(name_str);
	std::string type_str(type_cstr);
	trim(type_str);
	std::string look_str(look_cstr);
	trim(look_str);
	
	my_interface->createWidget(name_str, type_str, look_str); // Create the widget.
	
	std::string lastr(loc_abs); // <location>'s and <area>'s relative and absolute attributes exist, so convert them to vector<float>s
	trim(lastr);
	std::vector<float> location_absolutes = stringToVector<float>(lastr);
	std::string lrstr(loc_rel);
	trim(lrstr);
	std::vector<float> location_relatives = stringToVector<float>(lrstr);
	std::string aastr(area_abs);
	trim(aastr);
	std::vector<float> area_absolutes = stringToVector<float>(aastr);
	std::string arstr(area_rel);
	trim(arstr);
	std::vector<float> area_relatives = stringToVector<float>(arstr);
	
	my_interface->setPosition(name_str, location_absolutes, location_relatives); // Set the position and area for the widget.
	my_interface->setArea(name_str, area_absolutes, area_relatives);
	
	// Since a widget is able to have multiple events, it is important to loop over all events and add them to the widget!
	for(tinyxml2::XMLElement * event = my_window->FirstChildElement("event"); event != nullptr; event = event->NextSiblingElement("event")){
		const char * script_attribute = event->Attribute("script");
		std::string scriptName(script_attribute);
		trim(script_name);
		my_interface->addEvent(name_str, script_name);
	}
	
	for(tinyxml2::XMLElement * window_tag = my_window->FirstChildElement("window"); window_tag != nullptr; window_tag = window_tag->NextSiblingElement("window")){ // Recursively create this widget's children.
		std::string child_name = buildWindow(my_interface, window_tag);
		trim(child_name);
		my_interface->addChild(name_str, child_name);
	}
	
	tinyxml2::XMLElement * text_tag = my_window->FirstChildElement("text");
	if(text_tag != nullptr){
		std::string text_str(text_tag->Attribute("string"));
		trim(text_str);
		my_interface->setText(name_str, text_str);
	}
	return name_str;
}




std::vector<std::string> asw::GuiParser::getFonts(){
	std::vector<std::string> fonts;
	
	tinyxml2::XMLElement * tag = getMainElement();
	tinyxml2::XMLElement * fonts_tag = tag->FirstChildElement("fonts");
	if(fonts_tag == nullptr) THROW_TRACE("<fonts> is needed in XML file.");
	for(tinyxml2::XMLElement * font_tag = fonts_tag->FirstChildElement("font"); font_tag != nullptr; font_tag = font_tag->NextSiblingElement("font")){
		const char * file_cstr = font_tag->Attribute("file");
		std::string file_str(file_cstr);
		trim(file_str);
		fonts.push_back(file_str);
	}
	return fonts;
}
std::vector<std::string> asw::GuiParser::getSchemes(){
	std::vector<std::string> schemes; // Vector we wish to return.
	
	tinyxml2::XMLElement * tag = getMainElement();
	tinyxml2::XMLElement * schemes_tag = tag->FirstChildElement("schemes");
	if(schemes_tag == nullptr) THROW_TRACE("<schemes> is needed in XML file.");
	// Loop over all <scheme> tags. Pull the contents of the 'file' attribute and store it in the schemes vector.
	for(tinyxml2::XMLElement * scheme_tag = schemes_tag->FirstChildElement("scheme"); scheme_tag != nullptr; scheme_tag = scheme_tag->NextSiblingElement("scheme")){
		const char * file_cstr = scheme_tag->Attribute("file");
		std::string file_str(file_cstr);
		trim(file_str);
		schemes.push_back(file_str);
	}
	
	return schemes;
}
std::vector<ui_parser_pair> asw::GuiParser::getDefaults(){
	std::vector<ui_parser_pair> defaults;
	
	tinyxml2::XMLElement * tag = getMainElement();
	tinyxml2::XMLElement * defaults_tag = tag->FirstChildElement("defaults");
	if(defaults_tag == nullptr) THROW_TRACE("<defaults> is needed in XML file.");
	
	for(tinyxml2::XMLElement * default_tag = defaults_tag->FirstChildElement("default"); default_tag != nullptr; default_tag = default_tag->NextSiblingElement("default")){
		const char * type_cstr = default_tag->Attribute("type");
		const char * name_cstr = default_tag->Attribute("name");
	//	std::pair<std::string, std::string> new_pair(std::string(type_cstr), std::string(name_cstr));
		defaults.push_back(ui_parser_pair(std::string(type_cstr),std::string(name_cstr)));
	//	std::string type_str(type_cstr);
	//	std::string name_str(name_cstr);
	//	std::pair<std::string, std::string> the_pair(type_str, name_str);
		
	//	defaults.push_back(the_pair);
	}
	return defaults;
}

std::string asw::GuiParser::getType(){
	return type;
}

std::string asw::GuiParser::getName(){
	tinyxml2::XMLElement * tag = getMainElement();
	const char * name_cstr = tag->Attribute("name");
	if(name_cstr == nullptr) THROW_TRACE("GUI needs a name.");
	return std::string(name_cstr);
}
