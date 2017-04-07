#include "CeguiWindowResource.h"

cegui_resource::cegui_resource():
my_name(""),my_type(""),my_script(""){
	my_window = nullptr;
}
cegui_resource::cegui_resource(const std::string &name, CEGUI::Window * window, const std::string &type, const std::string &script):
my_name(name),my_type(type),my_script(script){
	my_window = window;
}
cegui_resource::cegui_resource(const cegui_resource &target):
my_name(target.my_name),my_type(target.my_type),my_script(target.my_script){
	my_window = target.my_window;
}
cegui_resource::~cegui_resource(){
	my_window = nullptr;
}