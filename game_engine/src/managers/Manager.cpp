/*
 * manager.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: uge
 */

#include "Manager.h"
#include "Render.h"
#include "Scene.h"

manager::~manager(){
	delete renderer;
	renderer = nullptr;
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

scene * manager::get_scene(){ // Could result in unknown behavior.
	if(my_scene == nullptr){
		my_scene = new scene(renderer);
	}
	return my_scene;
}

void manager::log(const std::string &comment){
	my_log.comment(comment);
}
void manager::log(const std::string &comment, uint ln_number){
	my_log.problem(comment, ln_number);
}
/*
 * Private Methods.
 */
manager::manager(const std::string &xml_file, const std::string &log_name):
my_log(log_name){
	init(xml_file);
	if(my_scene == nullptr){
		my_scene = new scene(renderer);
	}
	renderer->start_render();
}
void manager::init(const std::string &xml_file){
	renderer = new render(this, xml_file);
}
