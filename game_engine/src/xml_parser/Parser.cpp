#include "Parser.h"
#include "Camera.h"
#include <iostream>

#include <vector>
#include <sstream>
#include <cstddef>
#include <stack>

#include "Functions.h"
#include "Ogre.h"

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

void parse_scene_cameras(std::shared_ptr<scene> the_scene, tinyxml2::XMLElement * cameras_tree){
	for(uint32 c = 0, tinyxml2::XMLElement * cam = cameras_tree->FirstChildElement("camera"); cam != nullptr; c++, cam = cam->NextSiblingElement("camera")){
		// Retreive the camera's name
		tinyxml2::XMLElement * cam_name_tag = cam->FirstChildElement("name");
		std::string cam_name(cam_name_tag->GetText());
		the_scene->add_camera(cam_name);
		// Grab element tags.
		tinyxml2::XMLElement * loc_tag = cam->FirstChildElement("loc");
		tinyxml2::XMLElement * tar_tag = cam->FirstChildElement("target");
		tinyxml2::XMLElement * clip_tag = cam->FirstChildElement("clip");
		// Pull and trim the strings.
		std::string loc_str(loc_tag.GetText());
		trim(loc_str);
		std::string tar_str(tar_tag.GetText());
		trim(tar_str);
		std::string clip_str(clip_tag.GetText());
		trim(clip_str);
		// Convert Values to Vectors of Floats
		std::vector<float> loc = parse_fvector(loc_str);
		std::vector<float> tar = parse_fvector(tar_str);
		std::vector<float> clip = parse_fvector(clip_str);
		// Set vectors in scene
		the_scene->set_camera_clip(c, clip);
		the_scene->set_camera_location(c, loc);
		the_scene->set_camera_target(c, tar);
		cam->DeleteChildren(); // Delete and prevent memory leaks
	}
}

std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > parse_lvl(const std::string &xml, Ogre::Root * root){
	std::shared_ptr<resource> my_rsrc(new resource());
	
	// Create the TinyXMLDocument
	tinyxml2::XMLDocument doc;
	// Load the xml parameter using doc
	tinyxml2::XMLError flag = doc.LoadFile(xml.c_str());
	if(val != tinyxml2::XML_SUCCESS){
		doc.PrintError();
		std::exit(1);
	}
	// Grab the <game> tag
	tinyxml2::XMLElement * game_tree = doc.FirstChildElement("game");
	// Get the game's name
	tinyxml2::XMLElement * game_name_tag = game_tree->FirstChildElement("name");
	std::string game_name(game_name_tag->GetText());
	trim(game_name); // Trim whitespace off
	// Grab Mesh and Material locations
	tinyxml2::XMLElement * mesh_location_tag = game_tree->FirstChildElement("mesh");
	tinyxml2::XMLElement * material_location_tag = game_tree->FirstChildElement("mat");
	my_rsrc->add_resource_loc(mesh_location_tag->GetText());
	my_rsrc->add_resource_loc(material_location_tag->GetText());
	// It is now time to slowly start parsing the scene.
	// I have a function which will handle the graph
	// specifically in a top-down recursive fashion.
	tinyxml2::XMLElement * scene_tree = game_tree->FirstChildElement("scene");
	tinyxml2::XMLElement * scene_name_tag = scene_tree->FirstChildElement("name");
	std::string scene_name(scene_name_tag->GetText());
	// Create the scene
	std::shared_ptr<scene> my_scene(new scene(scene_name, root));
	// Parse its elements
	tinyxml2::XMLElement * cams_tree = scene_tree->FirstChildElement("cameras");
	parse_scene_cameras(my_scene, cams_tree); // Cameras
	cams_tree->DeleteChildren();
	// Parse entities
	tinyxml2::XMLElement * meshes_tree = scene_tree->FirstChildElement("meshes");
	// parsing meshes tag
}



std::shared_ptr<level> parse_level_orig(std::string file){
	std::string dummy("Dummy Name");
	std::shared_ptr<level> lvl(new level(dummy));
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError val = doc.LoadFile(file.c_str());
	if(val != tinyxml2::XML_SUCCESS){
		std::cout << "something went wrong" << std::endl;
		doc.PrintError();
		std::exit(1);
	}
	tinyxml2::XMLElement * lvl_tree = doc.FirstChildElement("level"); // Get the level tree
	tinyxml2::XMLElement * lvl_name = lvl_tree->FirstChildElement("name");
	std::string l_name(lvl_name->GetText());
	trim(l_name);
	lvl->set_name(l_name);
	tinyxml2::XMLElement * lvl_mesh_loc = lvl_tree->FirstChildElement("mesh");
	std::string mpath(lvl_mesh_loc.GetText());
	trim(mpath);
	lvl->set_mesh(mpath);
	tinyxml2::XMLElement * lvl_mat_path = lvl_tree->FirstChildElement("mat");
	std::string mater(lvl_mat_path.GetText());
	trim(mater);
	lvl->set_mat(mater);
	// Cam Section
	{
		tinyxml2::XMLElement * cams_tree = lvl_tree->FirstChildElement("cameras");
		tinyxml2::XMLElement * num_cams = cams_tree->FirstChildElement("num");
		std::string cnum_str(num_cams->GetText());
		trim(cnum_str);
		uint32 cnum = std::stoul(cnum_str); // Grab the number of cameras as an unsigned integer
		tinyxml2::XMLElement * cam_tree = cams_tree->FirstChildElement("camera");
		for(uint32 c = 0; c < cnum && cam_tree != nullptr; c++, cam_tree = cam_tree->NextSiblingElement("camera")){
			lvl->add_cam();
			tinyxml2::XMLElement * cam_name = cam_tree->FirstChildElement("name"); // Get the Camera's Name
			std::string cname(cam_name->GetText());
			trim(cname);
			lvl->set_cam_name(c, cname);
			tinyxml2::XMLElement * cam_loc = cam_tree->FirstChildElement("loc"); // Get the Camera's Location
			std::string cloc_vector(cam_loc->GetText());
			trim(cloc_vector);
			std::vector<double> loc = parse_vector(cloc_vector);
			lvl->set_cam_loc(c, loc);
			tinyxml2::XMLElement * cam_clip = cam_tree->FirstChildElement("clip"); // Get the Camera's Clip
			std::string cclip_vector(cam_clip->GetText());
			trim(cclip_vector);
			std::vector<double> clip = parse_vector(cclip_vector);
			lvl->set_cam_clip(c, clip);
			tinyxml2::XMLElement * cam_target = cam_tree->FirstChildElement("target"); // Get the Camera's Target
			std::string ctarget_vect(cam_target->GetText());
			trim(ctarget_vect);
			std::vector<double> target = parse_vector(ctarget_vect);
			lvl->set_cam_target(c, target);
			cam_tree->DeleteChildren();
		}
		cams_tree->DeleteChildren();
	}
	std::cout << "Finished Parsing Cameras" << std::endl;
	// Light Section
	{
		tinyxml2::XMLElement * lights_tree = lvl_tree->FirstChildElement("lights");
		tinyxml2::XMLElement * num_lights = lights_tree->FirstChildElement("num");
		std::string lnum_str(num_lights->GetText());
		trim(lnum_str);
		uint32 lnum = std::stoul(lnum_str); // Grab the number of cameras as an unsigned integer
		tinyxml2::XMLElement * light_tree = lights_tree->FirstChildElement("light");
		for(uint32 c = 0; c < lnum && light_tree != nullptr; c++, light_tree = light_tree->NextSiblingElement("light")){
			lvl->add_light();
			tinyxml2::XMLElement * light_name = light_tree->FirstChildElement("name");
			std::string lname = light_name->GetText();
			trim(lname);
			lvl->set_light_name(c, lname);
			tinyxml2::XMLElement * light_loc = light_tree->FirstChildElement("loc");
			std::string lloc_vect = light_loc->GetText();
			trim(lloc_vect);
			std::vector<double> loc = parse_vector(lloc_vect);
			lvl->set_light_loc(c, loc);
			tinyxml2::XMLElement * light_color = light_tree->FirstChildElement("color");
			std::string lcolor_vect = light_color->GetText();
			trim(lcolor_vect);
			std::vector<double> color = parse_vector(lcolor_vect);
			lvl->set_light_color(c, color);
			light_tree->DeleteChildren();
		}
		lights_tree->DeleteChildren();
	}
	std::cout << "Finished Parsing Lights" << std::endl;
	// Object Section
	{
		tinyxml2::XMLElement * meshes_tree = lvl_tree->FirstChildElement("objects");
		tinyxml2::XMLElement * num_meshes = meshes_tree->FirstChildElement("num");
		std::string nmesh_str(num_meshes->GetText());
		trim(nmesh_str);
		uint32 nmesh = std::stoul(nmesh_str);
		tinyxml2::XMLElement * mesh_tree = meshes_tree->FirstChildElement("object");
		for(uint32 c = 0; c < nmesh && mesh_tree != nullptr; c++, mesh_tree = mesh_tree->NextSiblingElement("object")){
			lvl->add_mesh();
			tinyxml2::XMLElement * mesh_name = mesh_tree->FirstChildElement("name");
			std::string mname(mesh_name->GetText());
			trim(mname);
			lvl->set_mesh_name(c, mname);
			tinyxml2::XMLElement * mesh_path = mesh_tree->FirstChildElement("mesh");
			std::string mepath(mesh_path->GetText());
			trim(mepath);
			lvl->set_mesh_path(c, mepath);
			tinyxml2::XMLElement * mat_path = mesh_tree->FirstChildElement("mat");
			std::string mapath(mat_path->GetText());
			trim(mapath);
			lvl->set_mesh_matpath(c, mapath);
			tinyxml2::XMLElement * transforms_tree = mesh_tree->FirstChildElement("transforms");
			for(tinyxml2::XMLElement * child = transforms_tree->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()){
				std::string child_val(child->Value());
				std::string vect(child->GetText());
				trim(vect);
				std::vector<double> child_vect = parse_vector(vect);
				TRANSF tr = TRANSF::TRANS;
				if(child_val.find("rotat") != -1){
					tr = TRANSF::ROTAT;
				}
				else if(child_val.find("trans") != -1){
					tr = TRANSF::TRANS;
				}
				else if(child_val.find("scale") != -1){
					tr = TRANSF::SCALE;
				}
				lvl->add_mesh_transform(c, tr, child_vect);
			}
			transforms_tree->DeleteChildren();
			mesh_tree->DeleteChildren();
		}
		meshes_tree->DeleteChildren();
	}
	std::cout << "Finished Parsing Meshes" << std::endl;
	//doc.DeleteChildren();
	return lvl;
}
