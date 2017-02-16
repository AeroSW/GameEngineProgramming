#ifndef PARSER_H_
#define PARSER_H_

#include "Scene.h"
#include "Resource.h"
#include "Ogre.h"
#include <tinyxml2.h>
#include <utility>
#include <memory>
#include <string>


std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > parse_lvl(const std::string &xml, Ogre::Root * root);


#endif