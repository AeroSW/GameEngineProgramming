#include "Gamepad.h"
#include "Manager.h"

#include "Asserts.h"
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
		ASSERT_LOG(false, "Gamepad inputs will not be used.")
	}
}

gamepad::gamepad(manager * m, int t/*, gamepad_t my_type*/):
input(m){
	ois_gamepad = nullptr;
	m->log("Created base class");
	my_manager = m;
	tol = std::labs(t);
	initialize();
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
	OIS::JoyStickState ois_joystick_state = ois_gamepad->getJoyStickState();
	OIS::JoyStickEvent event(ois_gamepad, ois_joystick_state);
	uint16 num_axis = event.state.mAxes.size();
	for(uint16 cx = 0; cx < num_axis; cx++){
		axisMoved(event, cx);
	}
}

bool gamepad::buttonPressed(const OIS::JoyStickEvent &event, int button){
	// Need to split up the types of gamepads.
	std::vector<bool> button_vectre = event.state.mButtons;
	my_manager->gamepad_pressed(button_vectre, button);
	return true;
}

bool gamepad::buttonReleased(const OIS::JoyStickEvent &event, int button){
	// Gonna run some tests with the Gamepad buttons.
	// I want to trace what button maps to what.
	/*uint16 num_buttons = event.state.mButtons.size();
	std::vector<int> buttons_id(num_buttons);
	std::cout << "Gamepad\tButtonReleased\tNumButtons\t" << num_buttons << "\tValues\t";
	for(uint16 cx = 0; cx < num_buttons; cx++){
		std::cout << event.state.mButtons[cx];
		if(cx != num_buttons - 1) std::cout << "\t";
	}
	std::cout << std::endl;*/
	return true;
}

bool gamepad::axisMoved(const OIS::JoyStickEvent &event, int axis){ // So we are going to implement gamepad now.
	bool trigger_flag = my_manager->is_trigger(axis);
	float v = 0.0;
	if(!trigger_flag){ // Check if it was joysticks
		int value = (event.state.mAxes[axis].abs);
		int c_val = std::labs(event.state.mAxes[axis].abs);
		if(c_val > tol){
			if(value < 0.0){ // Calculate relative value.
				v = value / neg_max * -1; // Multiply by -1 to preserve sign.
			}
			else{
				v = value / pos_max;
			}
			my_manager->gamepad_move(v, axis);
			return true;
		}
	}
	else{
		int limit = event.state.mAxes[axis].abs;
		int ntp_max = std::labs(neg_max);
		limit += ntp_max;
		if(limit > tol){
			v = limit / (pos_max + ntp_max);
			my_manager->gamepad_trigger(v, axis);
			return true;
		}
	}
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
