#include "Mouse.h"
#include "Manager.h"

mouse::mouse(manager * m):
ois_mouse(new OIS::Mouse()),
ois_manager(new OIS::InputManager()){
	my_manager = m;
}

mouse::~mouse(){
	my_manager = nullptr;
}

std::string mouse::get_type(){
	return type;
}

bool mouse::mouseMoved(const OIS::MouseEvent &event){
	return false;
}

bool mouse::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	std::string mbutton = map_button(id);
	if(mbutton.compare("undefined") != 0){
		my_manager->mbutton_pressed(mbutton);
		return true;
	}
	return false;
}

bool mouse::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	std::string mbutton = map_button(id);
	if(mbutton.compare("undefined") != 0){
		my_manager->mbutton_released(mbutton);
		return true;
	}
	return false;
}

std::string mouse::map_button(const OIS::MouseButtonID &id){
	switch(id){
		case(OIS::MB_LEFT):
			return "mleft";
		case(OIS::MB_RIGHT):
			return "mright";
		case(OIS::MB_MIDDLE):
			return "mmiddle";
		default:
			return "undefined";
	}
}