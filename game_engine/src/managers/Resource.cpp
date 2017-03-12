#include "Resource.h"
#include "Functions.h"
#include "Parser.h"
#include "Render.h"
#include <utility>

resource::resource():
rgm(Ogre::ResourceGroupManager::getSingletonPtr()){}

resource::resource(const resource &rsrc):
rgm(rsrc.rgm){}

resource::~resource(){}

void resource::add_group(const std::string &name){
	groups.push_back(name);
}

std::vector<std::string> resource::get_groups(){
	return groups;
}

void resource::add_resource_loc(const std::string &location, const std::string &group){
	for(std::string g : groups){
		if(g.compare(group) == 0){
			rgm->addResourceLocation(location, "FileSystem", group);
		}
	}
}
void resource::declare_resource(const std::string &file, const std::string &type, const std::string &group){
	for(std::string g : groups){
		if(g.compare(group) == 0){
			rgm->declareResource(file, type, group);
		}
	}
}
void resource::initialize_group(const std::string &group){
	rgm->initialiseResourceGroup(group);
}
void resource::load_group(const std::string &group, bool v1, bool v2){
	rgm->loadResourceGroup(group, v1, v2);
}

std::shared_ptr<Ogre::ResourceGroupManager> resource::get_manager(){
	return rgm;
}
