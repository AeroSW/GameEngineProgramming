#include "Parser.h"
#include <iostream>

#include <vector>

#include "Functions.h"

typedef unsigned int uint32;

/*
std::shared_ptr<level> parse_level(std::string file){
	std::stack<std::string> the_stack;
	std::string dummy("Dummy Name");
	std::shared_ptr<level> lvl(new level(dummy));
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError val = doc.LoadFile(file.c_str());
	tinyxml2::XMLElement * elem = doc.FirstChildElement();
	if(val != tinyxml2::XML_SUCCESS){
		std::cout << "something went wrong" << std::endl;
		doc.PrintError();
	}
	if(elem == nullptr)
		std::cout << "it's null" << std::endl;
	std::string str(elem->Value());
	std::cout << str << std::endl;
	return lvl;
}*/

void parse_scene_cameras(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * cameras_tree){
	for(uint32 c = 0, tinyxml2::XMLElement * cam = cameras_tree->FirstChildElement("camera"); cam != nullptr; c++, cam = cam->NextSiblingElement("camera")){
		// Retreive the camera's name
		tinyxml2::XMLElement * cam_name_tag = cam->FirstChildElement("name");
		std::string cam_name(cam_name_tag->GetText());
		the_scene->add_camera(cam_name);
		// Grab element tags.
		tinyxml2::XMLElement * loc_tag = cam->FirstChildElement("loc");
		tinyxml2::XMLElement * tar_tag = cam->FirstChildElement("target");
		tinyxml2::XMLElement * clip_tag = cam->FirstChildElement("clip");
		// Pull and trim the strings.
		std::string loc_str(loc_tag.GetText());
		trim(loc_str);
		std::string tar_str(tar_tag.GetText());
		trim(tar_str);
		std::string clip_str(clip_tag.GetText());
		trim(clip_str);
		// Convert Values to Vectors of Floats
		std::vector<float> loc = parse_fvector(loc_str);
		std::vector<float> tar = parse_fvector(tar_str);
		std::vector<float> clip = parse_fvector(clip_str);
		// Set vectors in scene
		the_scene->set_camera_clip(c, clip);
		the_scene->set_camera_location(c, loc);
		the_scene->set_camera_target(c, tar);
		cam->DeleteChildren(); // Delete and prevent memory leaks
	}
}

void parse_scene_entities(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * entities_tree){
	for(uint32 c = 0, tinyxml2::XMLElement * entity_tag = entities_tree->FirstChildElement("entity"); entity_tag != nullptr; c++, entity_tag = entity_tag->NextSiblingElement("entity")){
		tinyxml2::XMLElement * name_tag = entity_tag->FirstChildElement("name");
		std::string name(name_tag->GetText());
		trim(name);
		tinyxml2::XMLElement * mesh_tag = entity_tag->FirstChildElement("mesh");
		std::string mesh(mesh_tag->GetText());
		trim(mesh);
		the_scene->add_entity(name, mesh);
		tinyxml2::XMLElement * mat_tag = entity_tag->FirstChildElement("mat");
		if(mat_tag != nullptr){
			std::string mat(mat_tag->GetText());
			trim(mat);
			the_scene->set_material_name(c, mat);
		}
		entity_tag->DeleteChildren();
	}
}

void parse_scene_lights(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * lights_tree){
	for(uint32 c = 0, tinyxml2::XMLElement * light_tag = lights_tree->FirstChildElement("light"); light_tag != nullptr; light_tag = light_tag->NextSiblingElement("light"), c++){
		tinyxml2::XMLElement * name_tag = light_tag->FirstChildElement("name");
		tinyxml2::XMLElement * type_tag = light_tag->FirstChildElement("type");
		std::string name(name_tag->GetText());
		trim(name);
		if(type_tag != nullptr){
			std::string type(type_tag->GetText());
			trim(type);
			the_scene->add_light(name, type);
		}
		else{
			the_scene->add_light(name);
		}
		tinyxml2::XMLElement * loc_tag = light_tag->FirstChildElement("loc");
		std::string loc_str(loc_tag->GetText());
		trim(loc_str);
		std::vector<float> loc = parse_fvector(loc_str);
		the_scene->set_light_location(c, loc);
		tinyxml2::XMLElement * tar_tag = light_tag->FirstChildElement("target");
		if(tar_tag != nullptr){
			std::string tar_str(tar_tag->GetText());
			trim(tar_str);
			std::vector<float> tar = parse_fvector(tar_str);
			the_scene->set_light_target(c, tar);
		}
		tinyxml2::XMLElement * col_tag = light_tag->FirstChildElement("color");
		if(col_tag != nullptr){
			std::string col_str(col_tag->GetText());
			trim(col_str);
			std::vector<float> col = parse_fvector(col_str);
			the_scene->set_light_color(c, col);
		}
		else{
			std::vector<float> color;
			for(uint32 cc = 0; cc < 3; cc++){
				color.push_back(1.0);
			}
			the_scene->set_light_color(c, color);
		}
		light_tag->DeleteChildren();
	}
}

std::string recur_scene(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * curr_node){
	tinyxml2::XMLElement * name_tag = curr_node->FirstChildElement("name");
	std::string name(name_tag->GetText());
	trim(name);
	the_scene->add_node(name);
	tinyxml2::XMLElement * child = curr_node->FirstChildElement("node");
	if(child == nullptr){
		tinyxml2::XMLElement * object_tag = curr_node->FirstChildElement("object");
		if(object_tag == nullptr){
			throw "Object tag does not exist in leaf node\n";
		}
		std::string object_name(object_tag->GetText());
		the_scene->attach_node_object(name, object_name);
	}
	else{
		for(; child != nullptr; child = child->NextSiblingElement("node")){
			std::string cname = recur_scene(the_scene, child);
			trim(cname);
			the_scene->add_node_child(name, cname);
		}
	}
	tinyxml2::XMLElement * transforms_tree = curr_node->FirstChildElement("transforms");
	if(transforms_tree != nullptr){
		for(tinyxml2::XMLElement * transform_tag = transforms_tree->FirstChildElement(); transform_tag != nullptr; transform_tag = transform_tag->NextSiblingTag()){
			std::string type(transform_tag->Value());
			trim(type);
			if(type.compare("rotate")){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				TRANSFORM t = TRANSFORM::ROTATE;
				the_scene->add_node_transform(name, t, t_vect);
			}
			else if(type.compare("translate")){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				TRANSFORM t = TRANSFORM::TRANSLATE;
				the_scene->add_node_transform(name, t, t_vect);
			}
			else if(type.compare("scale")){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				TRANSFORM t = TRANSFORM::SCALE;
				the_scene->add_node_transform(name, t, t_vect);
			}
		}
		transforms_tree->DeleteChildren();
	}
	return name;
}

void parse_scene_graph(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * graph_tree){
	uint32 rt_index = 0; // It will always be 0
	tinyxml2::XMLElement * root_tag = graph_tree->FirstChildElement("root");
	for(tinyxml2::XMLElement * root_child = root_tag->FirstChildElement("node"); root_child != nullptr; root_child = root_child->NextSiblingElement("node")){
		std::string name = recur_scene(the_scene, root_child);
		the_scene->add_node_child(rt_index, name);
	}
	root_tag->DeleteChildren();
}

void parse_scene(std::shared_ptr<scene> my_scene, tinyxml2::XMLElement * scene_tree){
	// Parse its elements
	tinyxml2::XMLElement * cams_tree = scene_tree->FirstChildElement("cameras");
	parse_scene_cameras(my_scene, cams_tree); // Cameras
	cams_tree->DeleteChildren();
	// Parse entities
	tinyxml2::XMLElement * entities_tree = scene_tree->FirstChildElement("entities");
	// parsing entities tag
	parse_scene_entities(my_scene, entities_tree);
	entities_tree->DeleteChildren();
	// Parsing Lights
	tinyxml2::XMLElement * lights_tree = scene_tree->FirstChildElement("lights");
	parse_scene_lights(my_scene, lights_tree);
	lights_tree->DeleteChildren();
	// Parse Graph
	tinyxml2::XMLElement * graph_tree = scene->FirstChildElement("graph");
	parse_scene_graph(my_scene, graph_tree);
	graph_tree->DeleteChildren();
}

void parse_resource_group(std::shared_ptr<resource> my_rsrc, tinyxml2::XMLElement * rsrcs_tree){
	for(tinyxml2::XMLElement * group_tree = rsrcs_tree->FirstChildElement("group"); group_tree != nullptr; group_tree = group_tree->NextSiblingElement("group")){
		tinyxml2::XMLElement * name_tag = group_tree->FirstChildElement("name");
		std::string name(name_tag->GetText());
		trim(name);
		for(tinyxml2::XMLElement * loc_tag = group_tree->FirstChildElement("loc"); loc_tag != nullptr; loc_tag = loc_tag->NextSiblingElement("loc")){
			std::string loc(loc_tag->GetText());
			trim(loc);
			my_rsrc->add_resource_location(loc, name);
		}
		for(tinyxml2::XMLElement * rsrc_tree = group_tree->FirstChildElement("resource"); rsrc_tree != nullptr; rsrc_tree = rsrc_tree->NextSiblingElement("resource")){
			tinyxml2::XMLElement * type_tag = rsrc_tree->GetFirstChildElement("type");
			tinyxml2::XMLElement * file_tag = rsrc_tree->GetFirstChildElement("file");
			std::string type(type_tag->GetText());
			std::string file(file_tag->GetText());
			trim(type);
			trim(file);
			my_rsrc->declare_resource(file, type, name);
		}
	}
}

std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > parse_lvl(const std::string &xml, Ogre::Root * root){
	std::shared_ptr<resource> my_rsrc(new resource());
	
	// Create the TinyXMLDocument
	tinyxml2::XMLDocument doc;
	// Load the xml parameter using doc
	tinyxml2::XMLError flag = doc.LoadFile(xml.c_str());
	if(val != tinyxml2::XML_SUCCESS){
		doc.PrintError();
		std::exit(1);
	}
	// Grab the <game> tag
	tinyxml2::XMLElement * game_tree = doc.FirstChildElement("game");
	// Get the game's name
	tinyxml2::XMLElement * game_name_tag = game_tree->FirstChildElement("name");
	std::string game_name(game_name_tag->GetText());
	trim(game_name); // Trim whitespace off
	tinyxml2::XMLElement * rsrcs_tree = game_tree->FirstChildElement("resources");
	parse_resource_group(my_rsrc, rsrcs_tree);
	// It is now time to slowly start parsing the scene.
	// I have a function which will handle the graph
	// specifically in a top-down recursive fashion.
	tinyxml2::XMLElement * scene_tree = game_tree->FirstChildElement("scene");
	tinyxml2::XMLElement * scene_name_tag = scene_tree->FirstChildElement("name");
	std::string scene_name(scene_name_tag->GetText());
	// Create the scene
	std::shared_ptr<scene> my_scene(new scene(scene_name, root));
	parse_scene(my_scene, scene_tree);
	scene_tree->DeleteChildren();
	game_tree->DeleteChildren();
	doc.DeleteChildren();
	std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > game(new std::pair(my_resrc, my_scene));
	return game;
}