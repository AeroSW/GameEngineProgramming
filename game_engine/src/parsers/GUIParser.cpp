#include "GUIParser.h"
#include "Interface.h"
#include "GameException.h"
#include "SudoExcept.h"

#include <iostream>

const std::string guiparser::main_tag = "gui";
const std::string guiparser::type = "guiparser";

my_pair::my_pair():
first(""), second(""){}
my_pair::my_pair(const std::string &f, const std::string &s):
first(f),second(s){}
my_pair::my_pair(const my_pair &mp):
first(mp.first),second(mp.second){}

guiparser::guiparser(const std::string &file):
parser(file, main_tag){}

guiparser::~guiparser(){}

void guiparser::build_gui(interface * my_interface){
	
	tinyxml2::XMLElement * tag = get_main_element();
	tinyxml2::XMLElement * widgets_tag = tag->FirstChildElement("widgets");
	for(tinyxml2::XMLElement * window_tag = widgets_tag->FirstChildElement("window"); window_tag != nullptr; window_tag = window_tag->NextSiblingElement("window")){
		std::string child_name = build_window(my_interface, window_tag);
		my_interface->add_root_child(child_name);
	}
}

std::string guiparser::build_window(interface * my_interface, tinyxml2::XMLElement * my_window){
	const char * name_cstr = my_window->Attribute("name"); // Grab the name, type, and look attributes to build the window
	if(name_cstr == nullptr) throw_trace("<window> requires a 'name' attribute.");	// Check if they exist, if not, then throw error.
	const char * type_cstr = my_window->Attribute("type");
	if(type_cstr == nullptr) throw_trace("<window> requires a 'type' attribute.");
	const char * look_cstr = my_window->Attribute("look");
	if(look_cstr == nullptr) throw_trace("<window> requires a 'look' attribute.");
	
	tinyxml2::XMLElement * loc_tag = my_window->FirstChildElement("location"); // Grab <location> and <area>
	if(loc_tag == nullptr) throw_trace("<location> must be present within <window> tree."); // Check if they exist, if not, throw error.
	tinyxml2::XMLElement * area_tag = my_window->FirstChildElement("area");
	if(area_tag == nullptr) throw_trace("<area> must be present within <window> tree.");
	
	const char * loc_abs = loc_tag->Attribute("absolute"); // Grab <location>'s and <area>'s absolute and relative attributes
	if(loc_abs == nullptr) throw_trace("<location> needs an 'absolute' attribute."); // Check if they exist, if not, then throw error.
	const char * loc_rel = loc_tag->Attribute("relative");
	if(loc_abs == nullptr) throw_trace("<location> needs an 'relative' attribute.");
	const char * area_abs = area_tag->Attribute("absolute");
	if(loc_abs == nullptr) throw_trace("<area> needs an 'absolute' attribute.");
	const char * area_rel = area_tag->Attribute("relative");
	if(loc_abs == nullptr) throw_trace("<area> needs an 'relative' attribute.");
	
	std::string name_str(name_cstr); // name, type, and look exist, so convert them to std::string and trim whitespace off.
	trim(name_str);
	std::string type_str(type_cstr);
	trim(type_str);
	std::string look_str(look_cstr);
	trim(look_str);
	
	my_interface->create_widget(name_str, type_str, look_str); // Create the widget.
	
	std::string lastr(loc_abs); // <location>'s and <area>'s relative and absolute attributes exist, so convert them to vector<float>s
	trim(lastr);
	std::vector<float> location_absolutes = parse_fvector(lastr);
	std::string lrstr(loc_rel);
	trim(lrstr);
	std::vector<float> location_relatives = parse_fvector(lrstr);
	std::string aastr(area_abs);
	trim(aastr);
	std::vector<float> area_absolutes = parse_fvector(aastr);
	std::string arstr(area_rel);
	trim(arstr);
	std::vector<float> area_relatives = parse_fvector(arstr);
	
	my_interface->set_position(name_str, location_absolutes, location_relatives); // Set the position and area for the widget.
	my_interface->set_area(name_str, area_absolutes, area_relatives);
	
	for(tinyxml2::XMLElement * window_tag = my_window->FirstChildElement("window"); window_tag != nullptr; window_tag = window_tag->NextSiblingElement("window")){ // Recursively create this widget's children.
		std::string child_name = build_window(my_interface, window_tag);
		my_interface->add_child(name_str, child_name);
	}
	
	tinyxml2::XMLElement * text_tag = my_window->FirstChildElement("text");
	if(text_tag != nullptr){
		std::string text_str(text_tag->Attribute("string"));
		my_interface->set_text(name_str, text_str);
	}
	return name_str;
}




std::vector<std::string> guiparser::get_fonts(){
	std::vector<std::string> fonts;
	
	tinyxml2::XMLElement * tag = get_main_element();
	tinyxml2::XMLElement * fonts_tag = tag->FirstChildElement("fonts");
	if(fonts_tag == nullptr) throw_trace("<fonts> is needed in XML file.");
	for(tinyxml2::XMLElement * font_tag = fonts_tag->FirstChildElement("font"); font_tag != nullptr; font_tag = font_tag->NextSiblingElement("font")){
		const char * file_cstr = font_tag->Attribute("file");
		std::string file_str(file_cstr);
		fonts.push_back(file_str);
	}
	return fonts;
}
std::vector<std::string> guiparser::get_schemes(){
	std::vector<std::string> schemes; // Vector we wish to return.
	
	tinyxml2::XMLElement * tag = get_main_element();
	tinyxml2::XMLElement * schemes_tag = tag->FirstChildElement("schemes");
	if(schemes_tag == nullptr) throw_trace("<schemes> is needed in XML file.");
	// Loop over all <scheme> tags. Pull the contents of the 'file' attribute and store it in the schemes vector.
	for(tinyxml2::XMLElement * scheme_tag = schemes_tag->FirstChildElement("scheme"); scheme_tag != nullptr; scheme_tag = scheme_tag->NextSiblingElement("scheme")){
		const char * file_cstr = scheme_tag->Attribute("file");
		std::string file_str(file_cstr);
		schemes.push_back(file_str);
	}
	
	return schemes;
}
std::vector<my_pair> guiparser::get_defaults(){
	std::vector<my_pair> defaults;
	
	tinyxml2::XMLElement * tag = get_main_element();
	tinyxml2::XMLElement * defaults_tag = tag->FirstChildElement("defaults");
	if(defaults_tag == nullptr) throw_trace("<defaults> is needed in XML file.");
	
	for(tinyxml2::XMLElement * default_tag = defaults_tag->FirstChildElement("default"); default_tag != nullptr; default_tag = default_tag->NextSiblingElement("default")){
		const char * type_cstr = default_tag->Attribute("type");
		const char * name_cstr = default_tag->Attribute("name");
	//	std::pair<std::string, std::string> new_pair(std::string(type_cstr), std::string(name_cstr));
		defaults.push_back(my_pair(std::string(type_cstr),std::string(name_cstr)));
	//	std::string type_str(type_cstr);
	//	std::string name_str(name_cstr);
	//	std::pair<std::string, std::string> the_pair(type_str, name_str);
		
	//	defaults.push_back(the_pair);
	}
	return defaults;
}

std::string guiparser::get_type(){
	return type;
}

std::string guiparser::get_name(){
	tinyxml2::XMLElement * tag = get_main_element();
	const char * name_cstr = tag->Attribute("name");
	if(name_cstr == nullptr) throw_trace("GUI needs a name.");
	return std::string(name_cstr);
}
