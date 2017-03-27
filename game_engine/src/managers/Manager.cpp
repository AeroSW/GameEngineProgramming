/*
 * manager.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: uge
 */

#include "Manager.h"
#include "Render.h"
#include "Scene.h"
#include "LogManager.h"
#include "Input.h"
#include "Gamepad.h"
#include "Mouse.h"
#include "Keyboard.h"

manager::~manager(){
	delete renderer;
	renderer = nullptr;
	for(input * i : input_managers){
		delete i;
	}
}

manager* manager::get_manager(const std::string &xml_file, const std::string &log_name, gamepad_t type){
	static manager game_manager(xml_file, log_name, type);
	return &game_manager;
}

uint32 manager::get_win_height(){
	if(renderer != nullptr){
		return renderer->get_win_height();
	}
	return 0;
}

uint32 manager::get_win_length(){
	if(renderer != nullptr){
		return renderer->get_win_length();
	}
	return 0;
}

uint32 manager::get_render_win_handler(){
	if(renderer != nullptr){
		return renderer->get_win_handle();
	}
	return 0;
}

scene * manager::get_scene(render * this_renderer){ // Could result in unknown behavior.
	if(my_scene == nullptr){
		my_scene = new scene(this_renderer);
	}
	return my_scene;
}

void manager::log(const std::string &comment){
	my_log->comment(comment);
}
void manager::log(const std::string &comment, uint ln_number, const char * what_msg){
	std::string msg(what_msg);
	std::string new_comment = comment + ":\n" + msg;
	my_log->problem(new_comment, ln_number);
}
/*
 *	Input methods
 */
void manager::poll_inputs(){
	for(input * i : input_managers){
		if(i->has()){
			i->poll();
		}
	}
}
void manager::key_pressed(const std::string &key){ // On press, check which key was used.
	std::cout << "Key:  " << key << std::endl;
	if(key.compare("escape") == 0){ // If escape was pressed.
		log("Escape pressed, exiting game.");
		renderer->end_render(); // Then stop rendering the game, the user wants to exit.
		return;
	}
	if(key.compare("lctrl") == 0 || key.compare("rctrl") == 0){ // If a ctrl key was pressed
		my_keyboard_flags.ctrl = true; // Set the flag to true until it is released.
		return;
	}
	if(my_keyboard_flags.ctrl){ // If the ctrl flag is true
	//	std::cout << "Inside the ctrl flag conditional." << std::endl;
		if(key.compare("lshift") == 0 || key.compare("rshift") == 0){ // Then check if shift was pressed.
		//	std::cout << "Shift was pressed." << std::endl;
			my_keyboard_flags.toggle = !my_keyboard_flags.toggle; // If so, then toggle the shift flag.
			my_keyboard_flags.shift = !my_keyboard_flags.shift;
			return;
		}
	}
	if(key.compare("lshift") == 0 || key.compare("rshift") == 0){ // If the shift key is pressed
		my_keyboard_flags.shift = true; // Set the flag to true.  It will be set to false on releae if toggle is false.
	}
	if(my_keyboard_flags.shift){ // If shift flag is true
		if(key.compare("return") == 0){ // Then if enter was pressed
			renderer->prev_level(); // Return to the previous level.
			return;
		}
	}
	if(key.compare("return") == 0){ // If enter was pressed.
		renderer->next_level(); // Next level.
		return;
	}
	if(key.compare("left") == 0){
		renderer->prev_camera();
		return;
	}
	if(key.compare("right") == 0){
		renderer->next_camera();
		return;
	}
}
void manager::key_released(const std::string &key){
	if(key.compare("lctrl") == 0 || key.compare("rctrl") == 0){ // On release, we should set the flags to false.
		my_keyboard_flags.ctrl = false;
	}
	if((key.compare("lshift") == 0 || key.compare("rshift") == 0) && !my_keyboard_flags.toggle){
		my_keyboard_flags.shift = false;
	}
	if(key.compare("lalt") == 0 || key.compare("ralt") == 0){
		my_keyboard_flags.alt = false;
	}
}
/*
 *	Mouse Methods
 */
void manager::mbutton_pressed(uint8 button, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	renderer->mouse_pressed(button, abs_vals, rel_vals);
}
void manager::mbutton_released(uint8 button, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	renderer->mouse_released(button, abs_vals, rel_vals);
}

/*
 *	Gamepad Methods
 */
// Public
bool manager::is_trigger(int index){
	switch(my_gamepad_info.type){
		case(gamepad_t::DUALSHOCK4):
			if(index == 3 || index == 4){
				return true;
			}
			return false;
		case(gamepad_t::XBOX1):
			if(index == 2 || index == 5){
				return true;
			}
			return false;
		default:
			return false;
	}
}
void manager::gamepad_move(float value, int index){
	switch(my_gamepad_info.type){
		case(gamepad_t::DUALSHOCK4):
			dualshock_move(value, index);
			break;
		case(gamepad_t::XBOX1):
			xbox_move(value, index);
			break;
		default:
			return;
	}
}
void manager::gamepad_trigger(float value, int index){
	switch(my_gamepad_info.type){
		case(gamepad_t::DUALSHOCK4):
			dualshock_trigger(value, index);
			break;
		case(gamepad_t::XBOX1):
			xbox_trigger(value, index);
			break;
		default:
			return;
	}
}
void manager::gamepad_pressed(std::vector<bool> buttons, int index){
	switch(my_gamepad_info.type){
		case(gamepad_t::DUALSHOCK4):
			dualshock_pressed(buttons, index);
			break;
		case(gamepad_t::XBOX1):
			xbox_pressed(buttons, index);
			break;
		default:
			return;
	}
}
// Private
//  Dualshock Methods
void manager::dualshock_move(float value, int index){
	// Index 0 is Left and Right on left joystick for gamepad
	// mapping that to X-Axis
	// Index 1 is Up and Down on left joystick for gamepad
	// mapping that to Y-Axis
	// Index 2 is Left and Right on right joystick for gamepad
	// mapping that to Y-Axis Local Rotation
	// Index 5 is Up and Down on right joystick for gamepad
	// mapping that to X-Axis Local Rotations
	if(index == 0){
		renderer->cam_x_move(value);
	}
	else if(index == 1){
		renderer->cam_z_move(value);
	}
	else if(my_gamepad_flags.local_toggle){
		if(index == 2){
			renderer->cam_y_local_rotation(-1 * value);
		}
		else if(index == 5){
			renderer->cam_x_local_rotation( -1 * value);
		}
	}
	else{
		if(index == 2){
			renderer->cam_y_global_rotation(value);
		}
		else if(index == 5){
			renderer->cam_x_global_rotation( -1 * value);
		}
	}
}
void manager::dualshock_trigger(float value, int index){
	if(my_gamepad_flags.trigger_toggle){
		if(my_gamepad_flags.local_toggle){
			if(index == 4){ // Positive Rotation
				renderer->cam_z_local_rotation(value);
			}
			else{
				renderer->cam_z_local_rotation(-1 * value);
			}
		}
		else{
			if(index == 4){ // Positive Rotation
				renderer->cam_z_global_rotation(value);
			}
			else{
				renderer->cam_z_global_rotation(-1 * value);
			}
		}
	}
	else{
		if(index == 4){ // Positive Rotation
			renderer->cam_y_move(value);
		}
		else{
			renderer->cam_y_move(-1 * value);
		}
	}
}
void manager::dualshock_pressed(std::vector<bool> buttons, int index){
	if(index == 5){
		my_gamepad_flags.trigger_toggle = !my_gamepad_flags.trigger_toggle;
	}
	else if(index == 4){
		my_gamepad_flags.local_toggle = !my_gamepad_flags.local_toggle;
	}
}
//  Xbox One Methods
void manager::xbox_move(float value, int index){
	// Index 0 is Left and Right on left joystick for gamepad
	// mapping that to X-Axis
	// Index 1 is Up and Down on left joystick for gamepad
	// mapping that to Y-Axis
	// Index 3 is Left and Right on right joystick for gamepad
	// mapping that to Y-Axis Local Rotation
	// Index 4 is Up and Down on right joystick for gamepad
	// mapping that to X-Axis Local Rotations
	if(index == 0){
		renderer->cam_x_move(value);
	}
	else if(index == 1){
		renderer->cam_z_move(value);
	}
	else if(!my_gamepad_flags.local_toggle){
		if(index == 3){
			renderer->cam_y_global_rotation(value);
		}
		else if(index == 4){
			renderer->cam_x_global_rotation(-1 * value);
		}
	}
	else{
		if(index == 3){
			renderer->cam_y_local_rotation(-1 * value);
		}
		else if(index == 4){
			renderer->cam_x_local_rotation(-1 * value);
		}
	}
}
void manager::xbox_trigger(float value, int index){
	if(my_gamepad_flags.trigger_toggle){
		if(my_gamepad_flags.local_toggle){
			if(index == 5){ // Positive Rotation
				renderer->cam_z_local_rotation(value);
			}
			else{
				renderer->cam_z_local_rotation(-1 * value);
			}
		}
		else{
			if(index == 5){ // Positive Rotation
				renderer->cam_z_global_rotation(value);
			}
			else{
				renderer->cam_z_global_rotation(-1 * value);
			}
		}
	}
	else{
		if(index == 5){ // Positive Rotation
			renderer->cam_y_move(value);
		}
		else{
			renderer->cam_y_move(-1 * value);
		}
	}
}
void manager::xbox_pressed(std::vector<bool> buttons, int index){
	if(index == 5){
		my_gamepad_flags.trigger_toggle = !my_gamepad_flags.trigger_toggle;
	}
	else if(index == 4){
		my_gamepad_flags.local_toggle = !my_gamepad_flags.local_toggle;
	}
}

/*
 * Private Methods.
 */
manager::manager(const std::string &xml_file, const std::string &log_name, gamepad_t type){
	my_scene = nullptr;
	my_log = new logger(log_name);
	init_render(xml_file);
	log("RENDER CREATION COMPLETE.");
	if(my_scene == nullptr){
		my_scene = new scene(renderer);
	}
	init_inputs(type);
	log("INPUT CREATIONS COMPLETE.");
	renderer->start_render();
}
void manager::init_render(const std::string &xml_file){
	renderer = new render(this, xml_file);
	log("Render created.");
}
void manager::init_inputs(gamepad_t type){
	bool has_input = false;
	input * my_gamepad = new gamepad(this);
	if(my_gamepad->has()){
		log("Gamepad created.");
		input_managers.push_back(my_gamepad);
		my_gamepad_info.type = type;
		switch(type){
			case(gamepad_t::DUALSHOCK4):
				my_gamepad_info.curr_buttons = std::vector<bool>(14);
				my_gamepad_info.axes = std::vector<float>(6);
				break;
			case(gamepad_t::XBOX1):
				my_gamepad_info.curr_buttons = std::vector<bool>(11);
				my_gamepad_info.axes = std::vector<float>(6);
				break;
		}
		my_gamepad_flags.local_toggle = true;
		has_input = true;
	}
	else{
		log("Gamepad creation failure.");
		delete my_gamepad;
	}
	input * my_mouse = new mouse(this);
	if(my_mouse->has()){
		log("Mouse created.");
		input_managers.push_back(my_mouse);
		has_input = true;
	}
	else{
		log("Mouse creation failure.");
		delete my_mouse; // If failure in creation, then we need to delete the object.
	}
	input * my_keyboard = new keyboard(this);
	if(my_keyboard->has()){
		log("Keyboard created.");
		input_managers.push_back(my_keyboard);
		my_keyboard_flags.shift = false;
		my_keyboard_flags.ctrl = false;
		my_keyboard_flags.alt = false;
		has_input = true;
	}
	else{
		log("Keyboard creation failure.");
		delete my_keyboard;
	}
	if(!has_input){
		log("Failure to create an input.");
		std::exit(1);
	}
}
