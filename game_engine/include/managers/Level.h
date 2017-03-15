#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "LevelParser.h"
#include "UnsignedTypes.h"

class manager;
class scene;

class level{
	private:
		std::string name; //! Name of this level.
		levelparser * my_parser;
		scene * my_scene; // Personal scene reference.
		
		std::vector<std::string> entities;
		std::vector<std::string> cameras;
		std::vector<std::string> lights;
		std::vector<std::pair<std::string, std::vector<uint16> > > node_tracks;
		
	protected:
		
	public:
		std::vector<std::string> animation_list;
		
		level(const std::string &xml_doc, manager * my_manager);
		level(const level &lvl);
		virtual ~level();
		
		virtual void construct_level();
		virtual void destruct_level();
		
		// has functions
		virtual bool has_entity(const std::string &entity);
		virtual bool has_camera(const std::string &camera);
		virtual bool has_light(const std::string &light);
		virtual bool has_node_track(const std::string &node, const uint16 &track); // Need to think this through.
		
		// add functions
		virtual void add_entity(const std::string &entity);
		virtual void add_camera(const std::string &camera);
		virtual void add_light(const std::string &light);
		virtual void add_node_track(const std::string &node, const uint16 &track); // Need to think this through.
		
		level& operator=(const level &lvl);
};

#endif