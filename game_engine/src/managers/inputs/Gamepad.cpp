#include "Gamepad.h"
#include "Manager.h"

#include <cstdlib>
#include <iostream>

gamepad::gamepad(manager * m, int t):
ois_gamepad(new OIS::JoyStick()),
ois_manager(new OIS::InputManager()){
	tol = std::labs(t);
}

gamepad::~gamepad(){
	my_manager = nullptr;
}

std::string gamepad::get_type(){
	return type;
}

bool gamepad::buttonPressed(const OIS::JoyStickEvent &event, int button){
	// Gonna run some tests with the Gamepad buttons.
	// I want to trace what button maps to what.
	uint16 num_buttons = ois_gamepad->buttons();
	std::vector<int> buttons_id(num_buttons);
	std::cout << "Gamepad Buttons:  " << num_buttons << "\n";
	for(uint16 cx = 0; cx < num_buttons; cx++){
		std::cout << event.state.buttondown(cx);
		if(cx != num_buttons - 1) std::cout << "\t";
	}
	std::cout << std::endl;
	return true;
}

bool gamepad::buttonReleased(const OIS::JoyStickEvent &event, int button){
	return false;
}

bool gamepad::axisMoved(const OIS::JoyStickEvent &event, int axis){
	uint16 num_axis = ois_gamepad->axis();
	std::vector<int> axis_ids(num_axis);
	std::cout << "Gamepad Axis:     " << num_axis << "\n";
	for(uint16 cx = 0; cx < num_axis; cx++){
		std::cout << event.state.axis
	}
	return false;
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