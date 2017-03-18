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

manager* manager::get_manager(const std::string &xml_file, const std::string &log_name){
	static manager game_manager(xml_file, log_name);
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
void manager::key_pressed(const std::string &key){
	std::cout << "Key Pressed:\t" << key << std::endl;
}
void manager::key_released(const std::string &key){
	std::cout << "Key Released:\t" << key << std::endl;
}
void manager::mbutton_pressed(const std::string &mbutton){
	std::cout << "Mouse Pressed:\t" << mbutton << std::endl;
}
void manager::mbutton_released(const std::string &mbutton){
	std::cout << "Mouse Released:\t" << mbutton << std::endl;
}
/*
 * Private Methods.
 */
manager::manager(const std::string &xml_file, const std::string &log_name){
	my_scene = nullptr;
	my_log = new logger(log_name);
	init(xml_file);
	log("Manager Initialized Complete.");
	if(my_scene == nullptr){
		my_scene = new scene(renderer);
	}
	input_managers.push_back(new gamepad(this));
	log("Gamepad created.");
	input_managers.push_back(new mouse(this));
	log("Mouse created.");
	input_managers.push_back(new keyboard(this));
	log("Keyboard created.");
	renderer->start_render();
//	input_managers.push_back(new mouse(this));
//	input_managers.push_back(new keyboard(this));
}
void manager::init(const std::string &xml_file){
	renderer = new render(this, xml_file);
	log("Render created.");
}
