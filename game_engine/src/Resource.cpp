#include "Resource.h"
#include "Functions.h"
#include "Parser.h"
#include <utility>

resource::resource(const std::string &xml_filename):
rgm(Ogre::ResourceGroupManager::getSingletonPtr()){
	std::shared_ptr<Game_Info> game = parse_game(xml_filename);
	levels = game->levels;
	uint32 num_levels = levels.size();
	for(uint32 c = 0; c < num_levels; c++){
		rgm->addResourceLocation(levels[c]->get_mesh_loc(), "FileSystem", levels[c]->get_name());
		rgm->addResourceLocation(levels[c]->get_mat_loc(), "FileSystem", levels[c]->get_name());
	}
	curr_level = 1; // 1-based
	num_finished_levels = 0;
}

resource::resource(const resource &rsrc):
levels(rsrc.levels),curr_level(rsrc.curr_level),num_finished_levels(rsrc.num_finished_levels),rgm(rsrc.rgm){}

resource::~resource(){}

void resource::add_scene(const std::string &xml_filename){
	std::shared_ptr<level> lv = parse_level(xml_filename);
	levels.push_back(lv);
}

bool resource::build_scene(){
	// Will build the current level.
	uint32 num_objs = levels[curr_level]->mesh_count();
	for(uint32 c = 0; c < num_objs; c++){
		rgm->declareResource(levels[curr_level-1]->get_mesh(c), "Mesh", levels[curr_level-1]->get_name());
	}
	rgm->initializeResourceGroup(levels[curr_level-1]->get_name());
	rgm->loadResourceGroup(levels[curr_level-1]->get_name(), true, true);
}

std::string resource::curr_lvl_name(){
	return levels[curr_level-1]->get_name();
}

std::string resource::get_camname(){
	return levels[curr_level-1]->get_cam_name();
}
std::vector<double> * resource::get_camclip(){
	return levels[curr_level-1]->get_cam_clip();
}
std::vector<double> * resource::get_camloc(){
	return levels[curr_level-1]->get_cam_location();
}
std::vector<double> * resource::get_camtarget(){
	return levels[curr_level-1]->get_cam_target();
}