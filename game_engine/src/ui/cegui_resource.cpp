#include "include/ui/cegui_resource.h"
#include "CEGUI/CEGUI.h"

asw::CeguiResource::CeguiResource():
my_name(""),my_type(""){
	my_script = new std::string("");
	my_window = nullptr;
}
asw::CeguiResource::CeguiResource(const std::string &name, CEGUI::Window * window, const std::string &type, const std::string &script):
my_name(name),my_type(type){
	my_script = new std::string(script);
	my_window = window;
}
asw::CeguiResource::CeguiResource(const CeguiResource &target):
my_name(target.my_name),my_type(target.my_type){
	my_script = new std::string(*target.my_script);
	my_window = target.my_window;
}
asw::CeguiResource::~CeguiResource(){
	delete my_script;
	my_script = nullptr;
	my_window = nullptr;
}

std::string asw::CeguiResource::getName(){
	return my_name;
}
std::string asw::CeguiResource::getType(){
	return my_type;
}
std::string asw::CeguiResource::getScript(){
	return *my_script;
}
CEGUI::Window * asw::CeguiResource::getWindow(){
	return my_window;
}
void asw::CeguiResource::setScript(const std::string &s){
	if(my_script != nullptr) delete my_script;
	my_script = new std::string(s);
}

