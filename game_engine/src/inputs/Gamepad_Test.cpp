#include "Gamepad.h"
#include "Manager.h"

#include "asserts.h"
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iostream>

void gamepad::initialize(){
	std::cout << "Inside Gamepad Initialize" << std::endl;
	try{
		my_manager->log(std::to_string(ois_manager->getNumberOfDevices(OIS::OISJoyStick)));
		if(ois_manager->getNumberOfDevices(OIS::OISJoyStick) > 0){
			ois_gamepad = static_cast<OIS::JoyStick*>(ois_manager->createInputObject(OIS::OISJoyStick, true));
			ois_gamepad->setEventCallback(this);
		}
	}
	catch(std::exception &e){
		ASSERT_LOG(false, e.what());
	}
	catch(...){
		ASSERT_LOG(false, "Inputs will not be used.")
	}
}

gamepad::gamepad(manager * m, int t):
input(m){
	ois_gamepad = nullptr;
	m->log("Created base class");
	my_manager = m;
	my_manager->log("Manager pointer now points to ME!!!");
	tol = std::labs(t);
	std::string tol_str = "tol:\t" + std::to_string(tol);
	my_manager->log(tol_str);
	initialize();
	my_manager->log("Gamepad initialized");
	window_height = my_manager->get_win_height();
	window_length = my_manager->get_win_length();
}

gamepad::~gamepad(){
	my_manager = nullptr;
	ois_gamepad = nullptr;
}

std::string gamepad::get_type(){
	return type;
}

bool gamepad::has(){
	if(ois_gamepad){
		return true;
	}
	return false;
}

void gamepad::poll(){
	ois_gamepad->capture();
}

bool gamepad::buttonPressed(const OIS::JoyStickEvent &event, int button){
	// Gonna run some tests with the Gamepad buttons.
	// I want to trace what button maps to what.
	uint16 num_buttons = event.state.mButtons.size();
	std::vector<int> buttons_id(num_buttons);
	std::cout << "Gamepad\tButtonPressed\tNumButtons\t" << num_buttons << "\tValues\t";
	for(uint16 cx = 0; cx < num_buttons; cx++){
		std::cout << event.state.mButtons[cx];
		if(cx != num_buttons - 1) std::cout << "\t";
	}
	std::cout << std::endl;
	return true;
}

bool gamepad::buttonReleased(const OIS::JoyStickEvent &event, int button){
	// Gonna run some tests with the Gamepad buttons.
	// I want to trace what button maps to what.
	uint16 num_buttons = event.state.mButtons.size();
	std::vector<int> buttons_id(num_buttons);
	std::cout << "Gamepad\tButtonReleased\tNumButtons\t" << num_buttons << "\tValues\t";
	for(uint16 cx = 0; cx < num_buttons; cx++){
		std::cout << event.state.mButtons[cx];
		if(cx != num_buttons - 1) std::cout << "\t";
	}
	std::cout << std::endl;
	return true;
}

bool gamepad::axisMoved(const OIS::JoyStickEvent &event, int axis){
	uint16 num_axis = event.state.mAxes.size();
	std::vector<int> axis_ids(num_axis);
	std::cout << "Gamepad\tAxis\tNumAxis\t" << num_axis << "\tValues\t";
	for(uint16 cx = 0; cx < num_axis; cx++){
		std::cout << event.state.mAxes[cx].abs;
		if(cx != num_axis - 1) std::cout << "\t";
	}
	std::cout << std::endl;
	return true;
}

std::string gamepad::map_button(const int &button){
	switch(button){
		case(1):
			return "ga";
		case(2):
			return "gb";
		case(3):
			return "gx";
		case(4):
			return "gy";
		default:
			return "undefined";
	}
}


bool gamepad::sliderMoved(const OIS::JoyStickEvent &event, int slid){return true;}
bool gamepad::povMoved(const OIS::JoyStickEvent &event, int pov){return true;}
bool gamepad::vector3Moved(const OIS::JoyStickEvent &event, int vect){return true;}
