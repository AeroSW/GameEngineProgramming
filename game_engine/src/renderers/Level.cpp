// My definition
#include "Level.h"
// Exceptions
#include "GameException.h"
#include "SudoExcept.h"

level::scene::scene(){}
level::scene::scene(const scene &s):
scene_manager_name(s.scene_manager_name),
animation_names(s.animation_names),
group_names(s.group_names),
camera_names(s.camera_names),
light_names(s.light_names),
entity_group_material_names(s.entity_group_material_names){}

level::scene::~scene(){
	animation_names.clear();
	camera_names.clear();
	group_names.clear();
	light_names.clear();
	entity_group_material_names.clear();
}

void level::initialize(render * rm, const std::string &dox){
	if(render_manager == nullptr){
		render_manager = rm;
	}
	if(my_parser == nullptr){
		my_parser = new level_paser(dox);
	}
	else{
		my_parser->load_file(dox);
	}
}

level::level(render * rm, const std::string &dox){
	render_manager = nullptr;
	my_parser = nullptr;
	initialize(rm, dox);
	my_dox->build_level();
}

level::~level(){
	clear_scenes();
	my_parser = nullptr;
	render_manager = nullptr;
}

void level::switch_scene(uint32 scene_num){
	render_manager->destruct_resources(my_scenes[curr_scene_level].scene_manager_name, my_scenes[curr_scene_level].group_names);
	curr_scene_level = scene_num;
	
	render_manager->initialize_resources(my_scenes[curr_scene_level].group_names);
	render_manager->load_scene(my_scenes[curr_scene_level].scene_manager_name);
}
