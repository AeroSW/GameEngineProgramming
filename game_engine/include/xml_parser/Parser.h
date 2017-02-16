#ifndef PARSER_H_
#define PARSER_H_

#include "Level.h"
#include <tinyxml2.h>
#include <memory>
#include <string>


std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > parse_lvl(const std::string &xml, Ogre::Root * root);
std::shared_ptr<level> parse_level_orig(std::string file);



#endif