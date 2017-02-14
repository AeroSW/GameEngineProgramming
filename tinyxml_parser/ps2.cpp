#include "Parser.h"
#include "Camera.h"
#include <iostream>

#include <vector>
#include <sstream>
#include <cstddef>
#include <stack>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

typedef unsigned int uint32;

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

std::vector<double> parse_vector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<double> value;
	while (std::getline(ss, buffer, delim)) {
		value.push_back(std::stod(buffer));
	}
	return value;
}
std::shared_ptr<level> parse_level(std::string file){
	std::stack<std::string> the_stack;
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
	
	// Cam Section
	{
		tinyxml2::XMLElement * cams_tree = lvl_tree->FirstChildElement("cameras");
		tinyxml2::XMLElement * num_cams = cams_tree->FirstChildElement("num");
		std::string cnum_str(num_cams->GetText());
		uint32 cnum = std::stoul(cnum_str); // Grab the number of cameras as an unsigned integer
		tinyxml2::XMLElement * cam_tree = cams_tree->FirstChildElement("camera");
		for(uint32 c = 0; c < cnum; c++, cam_tree = cam_tree->NextSiblingElement("camera")){
			lvl->add_cam();
			tinyxml2::XMLElement * cam_name = cam_tree->FirstChildElement("name"); // Get the Camera's Name
			std::string cname(cam_name->GetText());
			lvl->set_cam_name(c, cname);
			tinyxml2::XMLElement * cam_loc = cam_tree->FirstChildElement("loc"); // Get the Camera's Location
			std::string cloc_vector(cam_loc->GetText());
			std::vector<double> loc = parse_vector(cloc_vector);
			lvl->set_cam_loc(c, loc);
			tinyxml2::XMLElement * cam_clip = cam_tree->FirstChildElement("clip"); // Get the Camera's Clip
			std::string cclip_vector(cam_clip->GetText());
			std::vector<double> clip = parse_vector(cclip_vector);
			lvl->set_cam_clip(c, clip);
			tinyxml2::XMLElement * cam_target = cam_tree->FirstChildElement("target"); // Get the Camera's Target
			std::string ctarget_vect(cam_target->GetText());
			std::vector<double> target = parse_vector(ctarget_vect);
			lvl->set_cam_target(c, target);
			cam_tree->DeleteChildren();
		}
		cams_tree->DeleteChildren();
	}
	doc.DeleteChildren();
	return lvl;
}