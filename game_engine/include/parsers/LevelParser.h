#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include "Scene.h"
#include "tinyxml2.h"

#include <string>
class manager;

class levelparser{
	private:
		tinyxml2::XMLDocument * doc;
		tinyxml2::XMLElement * lvl_element;
		tinyxml2::XMLElement * get_lvl_element();
		
		void parse_plane(scene * scene_manager, const std::string &group, const std::string &obj_name, tinyxml2::XMLElement * plane_tag);
		void parse_entity(scene * scene_manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object);
		void parse_camera(scene * scene_manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object);
		void parse_light(scene * scene_manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object);
		
		void parse_graph(scene * scene_manager, tinyxml2::XMLElement * graph);
		
		std::string recursive_parsing(scene * scene_manager, tinyxml2::XMLElement * curr_node);
		void apply_transforms(scene * scene_manager, tinyxml2::XMLElement * curr_node, const std::string &node_name);
		void apply_animations(scene * scene_manager, tinyxml2::XMLElement * curr_node, const std::string &node_name);
	
	public:
		std::string file_name;
		
		levelparser();
		levelparser(const std::string &doc_name);
		levelparser(const levelparser &lp);
		virtual ~levelparser();
		
		virtual void load_level(const std::string &doc_name);
		
		virtual void parse_paths(scene * scene_manager);
		virtual void parse_scene(scene * scene_manager);
		
		virtual std::string get_name();
		
		levelparser& operator=(const levelparser &lp);
};

#endif