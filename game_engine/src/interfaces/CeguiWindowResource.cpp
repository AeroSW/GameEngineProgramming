#include "CeguiWindowResource.h"

cegui_resource::cegui_resource():
my_name(""),my_type(""){
	my_script = new std::string("");
	my_window = nullptr;
}
cegui_resource::cegui_resource(const std::string &name, CEGUI::Window * window, const std::string &type, const std::string &script):
my_name(name),my_type(type){
	my_script = new std::string(script);
	my_window = window;
}
cegui_resource::cegui_resource(const cegui_resource &target):
my_name(target.my_name),my_type(target.my_type){
	my_script = new std::string(*target.my_script);
/*	if(target.my_script != nullptr)
		my_script = new std::string(*target.my_script);
	else
		my_script = nullptr;*/
	my_window = target.my_window;
}
cegui_resource::~cegui_resource(){
	delete my_script;
	my_window = nullptr;
}

std::string cegui_resource::get_name(){
	return my_name;
}
std::string cegui_resource::get_type(){
	return my_type;
}
std::string cegui_resource::get_script(){
	return *my_script;
}
CEGUI::Window * cegui_resource::get_window(){
	return my_window;
}
void cegui_resource::set_script(const std::string &s){
	if(my_script != nullptr) delete my_script;
	my_script = new std::string(s);
}
