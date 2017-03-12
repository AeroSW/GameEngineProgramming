#include "Parser.h"
#include <iostream>

#include <vector>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

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

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

void parse_scene_cameras(Ogre::SceneManager * scene, tinyxml2::XMLElement * cameras_tree){
	tinyxml2::XMLElement * cam = cameras_tree->FirstChildElement("camera");
	for(uint32 c = 0; cam != nullptr; c++, cam = cam->NextSiblingElement("camera")){
		// Retreive the camera's name
		tinyxml2::XMLElement * cam_name_tag = cam->FirstChildElement("name");
		std::string cam_name(cam_name_tag->GetText());
		Ogre::Camera * the_cam = scene->createCamera(cam_name);
		// Grab element tags.
		tinyxml2::XMLElement * loc_tag = cam->FirstChildElement("loc");
		tinyxml2::XMLElement * tar_tag = cam->FirstChildElement("target");
		tinyxml2::XMLElement * clip_tag = cam->FirstChildElement("clip");
		// Pull and trim the strings.
		std::string loc_str(loc_tag->GetText());
		trim(loc_str);
		std::string tar_str(tar_tag->GetText());
		trim(tar_str);
		std::string clip_str(clip_tag->GetText());
		trim(clip_str);
		// Convert Values to Vectors of Floats
		std::vector<float> loc = parse_fvector(loc_str);
		std::vector<float> tar = parse_fvector(tar_str);
		std::vector<float> clip = parse_fvector(clip_str);
		// Set vectors in scene
		the_cam->setPosition(loc[0], loc[1], loc[2]);
		the_cam->lookAt(tar[0], tar[1], tar[2]);
		the_cam->setNearClipDistance(clip[0]);
		the_cam->setFarClipDistance(clip[1]);
		std::cout << ":: Camera: " << cam_name << " Created" << std::endl;
	}
}

void parse_scene_entities(Ogre::SceneManager * scene, tinyxml2::XMLElement * entities_tree){
	tinyxml2::XMLElement * group_tag = entities_tree->FirstChildElement("group");
	std::string group_name(group_tag->GetText());
	trim(group_name);
	tinyxml2::XMLElement * entity_tag = entities_tree->FirstChildElement("entity");
	for(uint32 c = 0; entity_tag != nullptr; c++, entity_tag = entity_tag->NextSiblingElement("entity")){
		tinyxml2::XMLElement * name_tag = entity_tag->FirstChildElement("name");
		std::string name(name_tag->GetText());
		trim(name);
		tinyxml2::XMLElement * mesh_tag = entity_tag->FirstChildElement("mesh");
		std::string mesh(mesh_tag->GetText());
		trim(mesh);
		Ogre::Entity * ent = scene->createEntity(name, mesh, group_name);
		tinyxml2::XMLElement * mat_tag = entity_tag->FirstChildElement("mat");
		if(mat_tag != nullptr){
			std::string mat(mat_tag->GetText());
			trim(mat);
			std::cout << "Material:\t" << mat << std::endl;
			ent->setMaterialName(mat);
		}
		std::cout << ":: Entity: " << name << " Created" << std::endl;
	}
}

void parse_scene_lights(Ogre::SceneManager * scene, tinyxml2::XMLElement * lights_tree){
	tinyxml2::XMLElement * light_tag = lights_tree->FirstChildElement("light");
	for(uint32 c = 0; light_tag != nullptr; light_tag = light_tag->NextSiblingElement("light"), c++){
		std::cout << ">> Parsing Light" << std::endl;
		tinyxml2::XMLElement * name_tag = light_tag->FirstChildElement("name");
		tinyxml2::XMLElement * type_tag = light_tag->FirstChildElement("type");
		std::string name(name_tag->GetText());
		trim(name);
		Ogre::Light * light = scene->createLight(name);
		if(type_tag != nullptr){
			std::string type(type_tag->GetText());
			trim(type);
			std::cout << ">>> Setting Light Type:\t";
			Ogre::Light::LightTypes t = Ogre::Light::LightTypes::LT_POINT;
			if(type.compare("directional") == 0){
				std::cout << "LT_DIRECTIONAL" << std::endl;
				t = Ogre::Light::LightTypes::LT_DIRECTIONAL;
			}
			else if(type.compare("spotlight") == 0){
				std::cout << "LT_SPOTLIGHT" << std::endl;
				t = Ogre::Light::LightTypes::LT_SPOTLIGHT;
			}
			else{
				std::cout << "LT_POINT" << std::endl;
			}
			light->setType(t);
			std::cout << "<<< Light Type Set" << std::endl;
		}
		tinyxml2::XMLElement * loc_tag = light_tag->FirstChildElement("loc");
		if(loc_tag != nullptr){
			std::string loc_str(loc_tag->GetText());
			trim(loc_str);
			std::vector<float> loc = parse_fvector(loc_str);
			std::cout << ">>> Setting Light Loc:\tx = " << loc[0] << "\ty = " << loc[1] << "\tz = " << loc[2] << std::endl;
			light->setPosition(loc[0], loc[1], loc[2]);
			std::cout << "<<< Location was set" << std::endl;
		}
		tinyxml2::XMLElement * tar_tag = light_tag->FirstChildElement("target");
		if(tar_tag != nullptr){
			std::string tar_str(tar_tag->GetText());
			trim(tar_str);
			std::vector<float> tar = parse_fvector(tar_str);
			std::cout << ">>> Setting Direction:\tx = " << tar[0] << "\ty = " << tar[1] << "\tz = " << tar[2] << std::endl;
			light->setDirection(tar[0], tar[1], tar[2]);
			std::cout << "<<< Direction Set" << std::endl;
		}
		tinyxml2::XMLElement * col_tag = light_tag->FirstChildElement("color");
		if(col_tag != nullptr){
			std::string col_str(col_tag->GetText());
			trim(col_str);
			std::vector<float> col = parse_fvector(col_str);
			std::cout << ">>> Setting Colour:\tr = " << col[0] << "\tg = " << col[1] << "\tb = " << col[2] << std::endl;
			light->setDiffuseColour(col[0], col[1], col[2]);
			std::cout << "<<< Color Set" << std::endl;
		}
		std::cout << "<< Light: " << name << " Created" << std::endl;
	}
}

void parse_animation(render * r, Ogre::SceneManager * scene, Ogre::SceneNode * node, tinyxml2::XMLElement * animation_tree){
	static unsigned short animation_handle = 1;
	tinyxml2::XMLElement * name_tag = animation_tree->FirstChildElement("name");
	std::string name(name_tag->GetText());
	trim(name);
	tinyxml2::XMLElement * time_tag = animation_tree->FirstChildElement("time");
	std::string time_str(time_tag->GetText());
	trim(time_str);
	float time = std::stof(time_str);
	Ogre::Animation * anime = scene->createAnimation(name, time);
	anime->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack * anode = anime->createNodeTrack(animation_handle++, node);
	for(tinyxml2::XMLElement * frame_tree = animation_tree->FirstChildElement("frame"); frame_tree != nullptr; frame_tree = frame_tree->NextSiblingElement("frame")){
		time_tag = frame_tree->FirstChildElement("time");
		time_str = time_tag->GetText();
		trim(time_str);
		time = std::stof(time_str);
		Ogre::TransformKeyFrame * frame = anode->createNodeKeyFrame(time);
		tinyxml2::XMLElement * transforms_tree = frame_tree->FirstChildElement("transforms");
		if(transforms_tree != nullptr){
			for(tinyxml2::XMLElement * transform = transforms_tree->FirstChildElement(); transform != nullptr; transform = transform->NextSiblingElement()){
				std::string type(transform->Value());
				trim(type);
				std::string t_vect_str(transform->GetText());
				trim(t_vect_str);
				std::vector<float> coords = parse_fvector(t_vect_str);
				if(type.compare("trans") == 0){
					std::cout << "trans:\tx = " << coords[0] << "\ty = " << coords[1] << "\tz = " << coords[2] << std::endl;
					Ogre::Vector3 v(coords[0], coords[1], coords[2]);
					frame->setTranslate(v);
				}
				else if(type.compare("rotat") == 0){
					Ogre::Vector3 v(coords[1], coords[2], coords[3]);
					Ogre::Quaternion q(Ogre::Degree(coords[0]), v);
					frame->setRotation(q);
				}
				else if(type.compare("scale") == 0){
					Ogre::Vector3 v(coords[0], coords[1], coords[2]);
					frame->setScale(v);
				}
			}
		}
	}
	Ogre::AnimationState * anime_state = scene->createAnimationState(name);
	anime_state->setEnabled(true);
	anime_state->setLoop(true);
	std::cout << "Grab VECTOR" << std::endl;
	r->push_animation_state(anime_state);
	std::cout << "Finished with VECTOR" << std::endl;
}

Ogre::SceneNode * recur_scene(render * r, Ogre::SceneManager * scene, tinyxml2::XMLElement * curr_node){
	tinyxml2::XMLElement * name_tag = curr_node->FirstChildElement("name");
	std::string name(name_tag->GetText());
	trim(name);
	Ogre::SceneNode * node = scene->createSceneNode(name);
	tinyxml2::XMLElement * child = curr_node->FirstChildElement("node");
	if(child == nullptr){
		tinyxml2::XMLElement * object_tag = curr_node->FirstChildElement("object");
		if(object_tag == nullptr){
			throw "Object tag does not exist in leaf node\n";
		}
		std::string object_name(object_tag->GetText());
		trim(object_name);
		Ogre::Entity * the_entity = scene->getEntity(object_name);
		node->attachObject(the_entity);
	}
	else{
		for(; child != nullptr; child = child->NextSiblingElement("node")){
			Ogre::SceneNode * child_node = recur_scene(r, scene, child);
			node->addChild(child_node);
			tinyxml2::XMLElement * node_animation = curr_node->FirstChildElement("animation");
			if(node_animation != nullptr){
				std::cout << ">> Parsing Animation" << std::endl;
				parse_animation(r, scene, node, node_animation);
				std::cout << "<< Finished Parsing Animation" << std::endl;
			}
		}
	}
	tinyxml2::XMLElement * transforms_tree = curr_node->FirstChildElement("transforms");
	if(transforms_tree != nullptr){
		for(tinyxml2::XMLElement * transform_tag = transforms_tree->FirstChildElement(); transform_tag != nullptr; transform_tag = transform_tag->NextSiblingElement()){
			std::string type(transform_tag->Value());
			trim(type);
			if(type.compare("rotat") == 0){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				Ogre::Vector3 vr(t_vect[1], t_vect[2], t_vect[3]);
				Ogre::Quaternion q(Ogre::Degree(t_vect[0]), vr);
				node->rotate(q);
			}
			else if(type.compare("trans") == 0){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				node->translate(t_vect[0], t_vect[1], t_vect[2]);
			}
			else if(type.compare("scale") == 0){
				std::string t_str(transform_tag->GetText());
				trim(t_str);
				std::vector<float> t_vect = parse_fvector(t_str);
				node->scale(t_vect[0], t_vect[1], t_vect[2]);
			}
			else{
				std::cout << "Incorrect Type" << std::endl;
			}
		}
		std::cout << "Finished Translating" << std::endl;
	}
	return node;
}

void parse_scene_graph(render * r, Ogre::SceneManager * scene, tinyxml2::XMLElement * graph_tree){
	uint32 rt_index = 0; // It will always be 0
	Ogre::SceneNode * root = scene->getRootSceneNode();
	tinyxml2::XMLElement * root_tag = graph_tree->FirstChildElement("root");
	for(tinyxml2::XMLElement * root_child = root_tag->FirstChildElement("node"); root_child != nullptr; root_child = root_child->NextSiblingElement("node")){
		Ogre::SceneNode * child = recur_scene(r, scene, root_child);
		root->addChild(child);
	}
	root_tag->DeleteChildren();
}

void parse_the_scene(render * r, Ogre::SceneManager * scene, tinyxml2::XMLElement * scene_tree){
	// Parse its elements
	tinyxml2::XMLElement * cams_tree = scene_tree->FirstChildElement("cameras");
	parse_scene_cameras(scene, cams_tree); // Cameras
	// Parse entities
	tinyxml2::XMLElement * entities_tree = scene_tree->FirstChildElement("entities");
	// parsing entities tag
	parse_scene_entities(scene, entities_tree);
	// Parsing Lights
	tinyxml2::XMLElement * lights_tree = scene_tree->FirstChildElement("lights");
	parse_scene_lights(scene, lights_tree);
	// Parse Graph
	tinyxml2::XMLElement * graph_tree = scene_tree->FirstChildElement("graph");
	parse_scene_graph(r, scene, graph_tree);
}

void parse_resource_group(Ogre::ResourceGroupManager * rgm, tinyxml2::XMLElement * rsrcs_tree){
	std::cout << ">>>>>Parsing Resource Group<<<<<" << std::endl;
	for(tinyxml2::XMLElement * group_tree = rsrcs_tree->FirstChildElement("group"); group_tree != nullptr; group_tree = group_tree->NextSiblingElement("group")){
		tinyxml2::XMLElement * name_tag = group_tree->FirstChildElement("name");
		std::string name(name_tag->GetText());
		trim(name);
		std::cout << "\tResource Name:\t" << name << std::endl;
		//rgm->add_group(name);
		for(tinyxml2::XMLElement * loc_tag = group_tree->FirstChildElement("loc"); loc_tag != nullptr; loc_tag = loc_tag->NextSiblingElement("loc")){
			std::string loc(loc_tag->GetText());
			trim(loc);
			std::cout << "\tAdding Item location:\t" << loc << std::endl;
			rgm->addResourceLocation(loc, "FileSystem", name);
			std::cout << "\tResource Location Added:\t" << loc << std::endl;
		}
		for(tinyxml2::XMLElement * rsrc_tree = group_tree->FirstChildElement("resource"); rsrc_tree != nullptr; rsrc_tree = rsrc_tree->NextSiblingElement("resource")){
			tinyxml2::XMLElement * type_tag = rsrc_tree->FirstChildElement("type");
			tinyxml2::XMLElement * file_tag = rsrc_tree->FirstChildElement("file");
			std::string type(type_tag->GetText());
			std::string file(file_tag->GetText());
			trim(type);
			trim(file);
			std::cout << "\tAdding Resource\t" << file << "\tType:\t" << type << std::endl;
			rgm->declareResource(file, type, name);
			std::cout << "\tResource Added:\t" << file << "\tType:\t" << type << std::endl;
		}
	}
	std::cout << "FINISHED FINISHED FINISHED" << std::endl;
}

void parse_resources(const std::string &xml, Ogre::ResourceGroupManager * rgm){
	// Create the TinyXMLDocument
	tinyxml2::XMLDocument doc;
	// Load the xml parameter using doc
	tinyxml2::XMLError flag = doc.LoadFile(xml.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		doc.PrintError();
		std::exit(1);
	}
	// Grab the <game> tag
	tinyxml2::XMLElement * game_tree = doc.FirstChildElement("game");
	// Get the game's name
	tinyxml2::XMLElement * rsrcs_tree = game_tree->FirstChildElement("resources");
	parse_resource_group(rgm, rsrcs_tree);
}

std::string parse_scene_name(const std::string &xml){
	// Create the TinyXMLDocument
	tinyxml2::XMLDocument doc;
	// Load the xml parameter using doc
	tinyxml2::XMLError flag = doc.LoadFile(xml.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		doc.PrintError();
		std::exit(1);
	}
	// Grab the <game> tag
	tinyxml2::XMLElement * game_tree = doc.FirstChildElement("game");
	// It is now time to slowly start parsing the scene.
	// I have a function which will handle the graph
	// specifically in a top-down recursive fashion.
	tinyxml2::XMLElement * scene_tree = game_tree->FirstChildElement("scene");
	tinyxml2::XMLElement * scene_name_tag = scene_tree->FirstChildElement("name");
	std::string scene_name(scene_name_tag->GetText());
	return scene_name;
}

void parse_scene(const std::string &xml, Ogre::SceneManager * scene, render * r){
	// Create the TinyXMLDocument
	tinyxml2::XMLDocument doc;
	// Load the xml parameter using doc
	tinyxml2::XMLError flag = doc.LoadFile(xml.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		doc.PrintError();
		std::exit(1);
	}
	// Grab the <game> tag
	tinyxml2::XMLElement * game_tree = doc.FirstChildElement("game");
	// Create the scene
	tinyxml2::XMLElement * scene_tree = game_tree->FirstChildElement("scene");
	parse_the_scene(r, scene, scene_tree);
}