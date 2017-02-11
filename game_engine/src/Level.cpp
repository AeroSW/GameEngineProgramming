/*
 * Level.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#include "Level.h"

level::level(std::string &n){
	name = n;
}
level::level(const level &l):
		name(l.name), cam_coords(l.cam_coords),
		cam_dir(l.cam_dir), objects(l.objects){
}
level::~level(){}

void level::add_obj(std::shared_ptr<object> &obj){
	objects.push_back(obj);
}
void level::add_obj(std::string &url, std::vector<transform> &transforms){
	std::shared_ptr<object> obj(new object);
	obj->transforms = transforms;
	obj->url = url;
	objects.push_back(obj);
}
void level::add_objs(std::vector<std::shared_ptr<object> > objs){
	objects.insert(objects.end(), objs.begin(), objs.end());
}

void level::clean(){
	objects.clear();
}

void level::get_name(std::string &dest){
	dest = name;
}
void level::get_object(uint32 index, object &dest){
	&dest = objects[index];
}
void level::get_cam_coords(std::vector<double> &dest){
	dest = cam_coords;
}
void level::get_cam_direction(std::vector<double> &dest){
	dest = cam_dir;
}

void  level::rmv_obj(uint32 index){
	objects.erase(objects.begin() + index);
}
void level::set_name(std::string &new_name){
	name = new_name;
}
