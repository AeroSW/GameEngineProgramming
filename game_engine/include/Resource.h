/*
 * Resource.h
 *
 *  Created on: Feb 2, 2017
 *      Author: uge
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <memory>
#include <vector>
#include <string>
#include "Ogre.h"

class level;

class resource{
	private:
		std::shared_ptr<std::vector<std::shared_ptr<level> > > levels; // Need to treat is as 1-based.
		uint32 num_levels; // Number of total levels in game.
		uint32 curr_level; // The current level's index.
		uint32 num_finished_levels; // Number of levels currently finished.
		std::shared_ptr<Ogre::ResourceGroupManager> rgm;
		uint32 curr_cam;
		
	public:
		resource(const std::string &xml_filename); // Builds resource object based on xml file.
		resource(const resource &res); // Copy constructor
		virtual ~resource();
		
		bool add_scene(const std::string &file);
		bool build_scene(); // 1-based need to convert to 0.
		
		std::string curr_lvl_name();
		
		std::string get_camname();
		std::vector<double> get_camclip();
		std::vector<double> get_camloc();
		std::vector<double> get_camtarget();
};


#endif /* RESOURCE_H_ */
