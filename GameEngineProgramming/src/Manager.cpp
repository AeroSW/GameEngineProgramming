/*
 * manager.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: uge
 */

#include "Manager.h"

manager::~manager(){
	delete renderer;
	renderer = nullptr;
}

manager* manager::get_manager(){
	static manager game_manager;
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

std::string manager::get_curr_level_name(){
	if(renderer != nullptr){
		return renderer->get_curr_level_name();
	}
	throw 1;
}

bool manager::add_scene(const std::string &xml_filename){
	if(renderer != nullptr){
		if(renderer->add_scene(xml_filename)){
			return true;
		}
		return false;
	}
	throw 1;
}

/*
 * Private Methods.
 */
manager::manager(){
	init();
	renderer->start_render();
}
void manager::init(){
	renderer = new render(this);
}
