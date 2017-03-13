#include "Scene.h"
#include "SceneException.h"
#include "Render.h"

scene::scene(render * renderer){
	my_renderer = renderer;
}
scene::scene(render * renderer, std::vector<std::string> lvls):
level_files(lvls){
	my_renderer = renderer;
}
scene::scene(render * renderer, const std::string &game_file){
	my_renderer = renderer;
	gameparser gparser(game_file);
	my_renderer->set_window_name(gparser.get_name());
	level_files = gparser.get_levels();
}
scene::scene(const scene &s):
level_files(s.level_files){
	my_renderer = s.my_renderer;
}
scene::~scene(){
	my_renderer = nullptr;
}

void scene::log(const std::string &msg){
	string new_msg = "Scene:\t" + msg;
	my_renderer->log_scene(new_msg);
}

void scene::add_rsrc_location(const std::string &location, const std::string &group){
	my_renderer->add_resource_location(location, group);
}
void scene::declare_rsrc(const std::string &file, const std::string &type, const std::string &group){
	my_renderer->declare_resource(file, type, group);
}

// Entity Functions
void scene::add_entity(const std::string &entity, const std::string &mesh, const std::string &group){
	my_renderer->add_entity(entity, mesh, group);
}
void scene::add_material(const std::string &entity, const std::string &material, const std::string &group){
	my_renderer->add_material(entity, material, group);
}
bool scene::has_group(const std::string &group){
	return my_renderer->has_group(group);
}

// Camera Functions
void scene::create_camera(const std::string camera){
	my_renderer->add_camera(camera);
}
void scene::apply_camera(std::vector<float> &loc, std::vector<float> &target, std::vector<float> &clip){
	my_renderer->adjust_camera(loc, target, clip);
}

// Light Functions
void scene::create_light(const std::string &light){
	my_renderer->add_light(light);
}
void scene::set_light_type(const std::string &light, const std::string &type){
	my_renderer->set_light_type(light, type);
}
void scene::set_light_location(const std::string &light, std::vector<float> &location){
	my_renderer->set_light_location(light, location);
}
void scene::set_light_target(const std::string &light, std::vector<float> &target){
	my_renderer->set_light_target(light, target);
}
void scene::set_light_color(const std::string &light, std::vector<float> &color){
	my_renderer->set_light_colour(light, color);
}

// Scene Graph Functions
void scene::add_root_child(const std::string &child){
	my_renderer->add_root_child(child);
}
void scene::create_node(const std::string &name){
	my_renderer->add_node(name);
}
void scene::add_child(const std::string &parent, const std::string &child){
	my_renderer->add_child(parent, child);
}
void scene::attach_object(const std::string &node, const std::string &entity){
	my_renderer->attach_object(node, entity);
}
// Transformations
void scene::apply_rotation(const std::string &node, axis w, float angle){
	my_renderer->rotate_node(node, w, angle); // Will probably split this up and create seperate rotation functions in render.h and render.cpp
}
void scene::apply_scale(const std::string &node, std::vector<float> &scaling){
	my_renderer->scale_node(node, scaling);
}
void scene::apply_translation(const std::string &node, std::vector<float> &translation){
	my_renderer->move_node(node, translation);
}
// Animations
void scene::create_animation(const std::string &node, const std::string &animation, float time, const unsigned short &track_num){
	my_renderer->add_animation(node, animation, time, track_num);
}
void scene::add_frame(const std::string &animation, const unsigned short &track_num, float time, std::vector<transform> &transforms){
	my_renderer->add_frame(animation, track_num, time, transforms);
}