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
