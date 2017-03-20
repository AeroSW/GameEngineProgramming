#include "Asserts.h"
#include "Mouse.h"
#include "Manager.h"
#include <vector>
#include <sstream>
#include <iostream>

void mouse::initialize(){
	try{
		if(ois_manager->getNumberOfDevices(OIS::OISMouse) > 0){
			ois_mouse = static_cast<OIS::Mouse*>(ois_manager->createInputObject(OIS::OISMouse, true));
			ois_mouse->setEventCallback(this);
		}
	}
	catch(...){
		ASSERT_LOG(false, "Inputs will not be used.");
	}
}

mouse::mouse(manager * m):
input(m){
	my_manager = m;
	initialize();
	window_height = my_manager->get_win_height();
	window_length = my_manager->get_win_length();
}

mouse::~mouse(){
	my_manager = nullptr;
	ois_mouse = nullptr;
}

std::string mouse::get_type(){
	return type;
}

bool mouse::has(){
	if(ois_mouse){
		return true;
	}
	return false;
}

void mouse::poll(){
	ois_mouse->capture();
}

bool mouse::mouseMoved(const OIS::MouseEvent &event){
	return true;
}

bool mouse::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	std::string mbutton = map_button(id);
	my_manager->mbutton_pressed(mbutton);
	return true;
}

bool mouse::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	std::string mbutton = map_button(id);
	my_manager->mbutton_released(mbutton);
	return true;
}

std::string mouse::map_button(const OIS::MouseButtonID &id){
	switch(id){
		case(OIS::MouseButtonID::MB_Left):
			return "mleft";
		case(OIS::MouseButtonID::MB_Right):
			return "mright";
		case(OIS::MouseButtonID::MB_Middle):
			return "mmiddle";
		default:
			return "undefined";
	}
}
