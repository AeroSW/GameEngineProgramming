/*
 * manager.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: uge
 */

#include "Manager.h"
#include "Render.h"
#include "Logger.h"

manager::~manager(){
	delete renderer;
	renderer = nullptr;
}

manager* manager::get_manager(const std::string &xml_file){
	static manager game_manager(xml_file);
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
/*
 * Private Methods.
 */
manager::manager(const std::string &xml_file){
	init(xml_file);
	renderer->start_render();
}
void manager::init(const std::string &xml_file){
	renderer = new render(this, xml_file);
}
