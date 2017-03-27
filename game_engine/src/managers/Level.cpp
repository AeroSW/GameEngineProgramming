#include "Level.h"
#include "Scene.h"
#include "Render.h"
#include "LevelException.h"

#include <iostream> // Debug

level::level(const std::string &doc_name, render * my_renderer){
	cam_index = 0;
	my_parser = new levelparser(doc_name);
	my_scene = (scene*)my_renderer->get_scene_manager();
	name = my_parser->get_name();
}

level::level(const level &lvl):
name(lvl.name){
	cam_index = 0;
	my_parser = new levelparser(lvl.my_parser->file_name);
	my_scene = lvl.my_scene;
}

level::~level(){
	delete my_parser;
	my_scene = nullptr;
}

void level::construct_level(){
	if(!my_scene->has_manager(name)){
		try{
			my_scene->create_manager(name);
			my_parser->parse_paths(my_scene);
			my_scene->load_resources(resources);
			my_scene->load(name);
			my_parser->parse_scene(my_scene);
		}
		catch(game_error &e){
			throw level_error(std::string(e.what()), 29);
		}
	}
	else{
		my_scene->load_resources(resources);
		my_scene->load(name);
	}
	my_scene->build(name);
}
void level::destruct_level(){
	if(my_scene->has_manager(name))
		my_scene->unload_resources(resources);
}

std::string level::get_camera(uint32 index){
	cam_index = index;
	return cameras[index];
}
uint32 level::num_cameras(){
	return cameras.size();
}
std::string level::get_name(){
	return name;
}
std::string level::get_resource(uint32 index){
	return resources[index];
}
uint32 level::num_resources(){
	return resources.size();
}

bool level::has_resource(const std::string &resource){
	for(std::string r : resources){
		if(r.compare(resource) == 0){
			return true;
		}
	}
	return false;
}
bool level::has_entity(const std::string &entity){
	for(std::string e : entities){
		if(e.compare(entity) == 0){
			return true;
		}
	}
	return false;
}
bool level::has_camera(const std::string &camera){
	for(std::string c : cameras){
		if(c.compare(camera) == 0){
			return true;
		}
	}
	return false;
}
bool level::has_light(const std::string &light){
	for(std::string l : lights){
		if(l.compare(light) == 0){
			return true;
		}
	}
	return false;
}
bool level::has_node_track(const std::string &node, const uint16 &track){
	for(std::pair<std::string, std::vector<uint16> > node_track : node_tracks){
		if(node_track.first.compare(node) == 0){
			uint32 num_tracks = node_track.second.size();
			for(uint32 cx = 0; cx < num_tracks; cx++){
				if(track == node_track.second[cx]){
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

void level::add_resource(const std::string &resource){
	resources.push_back(resource);
}
void level::add_entity(const std::string &entity){
	entities.push_back(entity);
}
void level::add_camera(const std::string &camera){
	cameras.push_back(camera);
}
void level::add_light(const std::string &light){
	lights.push_back(light);
}
void level::add_node_track(const std::string &node, const uint16 &track){
	for(std::pair<std::string, std::vector<uint16> > node_track : node_tracks){
		if(node_track.first.compare(node) == 0){
			node_track.second.push_back(track);
			return;
		}
	}
	std::pair<std::string, std::vector<uint16> > tracker;
	tracker.first = node;
	tracker.second.push_back(track);
	node_tracks.push_back(tracker);
}

level& level::operator=(const level &lvl){
	entities = lvl.entities;
	cameras = lvl.cameras;
	lights = lvl.lights;
	node_tracks = lvl.node_tracks;
	delete my_parser;
	my_parser = new levelparser(lvl.my_parser->file_name);
	my_scene = lvl.my_scene;
}