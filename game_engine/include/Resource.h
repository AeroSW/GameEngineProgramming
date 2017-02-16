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
		std::shared_ptr<Ogre::ResourceGroupManager> rgm;
		
	public:
		resource();
		resource(const resource &res); // Copy constructor
		virtual ~resource();
		
		void add_resource_loc(const std::string &location, const std::string &group);
		void declare_resource(const std::string &file, const std::string &type, const std::string &group);
		void initialize_group(const std::string &group);
		void load_group(const std::string &group, bool v1=true, bool v2=true);
};


#endif /* RESOURCE_H_ */
