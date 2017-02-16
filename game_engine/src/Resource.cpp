#include "Resource.h"
#include "Functions.h"
#include "Parser.h"
#include <utility>

resource::resource():
rgm(Ogre::ResourceGroupManager::getSingletonPtr()){}

resource::resource(const resource &rsrc):
rgm(rsrc.rgm){}

resource::~resource(){}

void resource::add_resource_loc(const std::string &location, const std::string &group){
	rgm->addResourceLocation(location, "FileSystem", group);
}
void resource::declare_resource(const std::string &file, const std::string &type, const std::string &group){
	rgm->declareResource(file, type, group);
}
void resource::initialize_group(const std::string &group){
	rgm->initializeResourceGroup(group);
}
void resource::load_group(const std::string &group, bool v1=true, bool v2=true){
	rgm->loadResourceGroup(group, v1, v2);
}