#include "Asserts.h"
#include "Mouse.h"
#include "Manager.h"
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

std::vector<int> mouse::get_absolute_position(){
	OIS::MouseState curr_state = ois_mouse->getMouseState();
	std::vector<int> abs_loc;
	abs_loc.push_back(curr_state.X.abs);
	abs_loc.push_back(curr_state.Y.abs);
	abs_loc.push_back(curr_state.Z.abs);
	return abs_loc;
}

std::vector<int> mouse::get_relative_position(){
	OIS::MouseState curr_state = ois_mouse->getMouseState();
	std::vector<int> rel_loc;
	rel_loc.push_back(curr_state.X.rel);
	rel_loc.push_back(curr_state.Y.rel);
	rel_loc.push_back(curr_state.Z.rel);
	return rel_loc;
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
//	std::cout << "MOUSE:\n";
//	std::cout << "ABS X: " << event.state.X.abs << "\n";
//	std::cout << "ABS Y: " << event.state.Y.abs << "\n";
//	std::cout << "ABS Z: " << event.state.Z.abs << std::endl;
//	std::cout << "REL X: " << event.state.X.rel << "\n";
//	std::cout << "REL Y: " << event.state.Y.rel << "\n";
//	std::cout << "REL Z: " << event.state.Z.rel << std::endl;
	std::vector<int> absolute_values;
	absolute_values.push_back(event.state.X.abs);
	absolute_values.push_back(event.state.Y.abs);
	absolute_values.push_back(event.state.Z.abs);
	std::vector<int> relative_values;
	relative_values.push_back(event.state.X.rel);
	relative_values.push_back(event.state.Y.rel);
	relative_values.push_back(event.state.Z.rel);
	my_manager->mouse_moved(absolute_values, relative_values);
	return true;
}

bool mouse::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	uint8 mbutton = map_button(id);
	if(mbutton != 0){
		std::vector<int> abs_vals = get_absolute_position();
		std::vector<int> rel_vals = get_relative_position();
		my_manager->mbutton_pressed(mbutton, abs_vals, rel_vals);
	}
	return true;
}

bool mouse::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id){
	uint8 mbutton = map_button(id);
	if(mbutton != 0){
		std::vector<int> abs_vals = get_absolute_position();
		std::vector<int> rel_vals = get_relative_position();
		my_manager->mbutton_released(mbutton, abs_vals, rel_vals);
	}
	return true;
}

uint8 mouse::map_button(const OIS::MouseButtonID &id){
	switch(id){
		case(OIS::MouseButtonID::MB_Left):
			return 1;
		case(OIS::MouseButtonID::MB_Right):
			return 2;
		case(OIS::MouseButtonID::MB_Middle):
			return 3;
		default:
			return 0;
	}
}
