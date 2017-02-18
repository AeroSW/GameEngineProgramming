#ifndef PARSER_H_
#define PARSER_H_

#include "Ogre.h"
#include <tinyxml2.h>
#include <utility>
#include <memory>
#include <string>

#include "Render.h"

//std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > parse_lvl(const std::string &xml, std::shared_ptr<Ogre::Root> &root);
void parse_scene(const std::string &xml, Ogre::SceneManager * scene, render * r);
void parse_resources(const std::string &xml, Ogre::ResourceGroupManager * rgm);
std::string parse_scene_name(const std::string &xml);

#endif