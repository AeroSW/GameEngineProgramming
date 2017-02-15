/*
 * Level.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#include "Level.h"

level::level(std::string &n):
name(n){}

level::level(const level &l):
name(l.name),cameras(l.cameras),lights(l.lights),meshes(l.meshes){}

level::~level(){}

void level::add_cam(){
	std::shared_ptr<camera> cam(new camera());
	cameras.push_back(cam);
}
void level::add_cam(std::string &name){
	std::shared_ptr<camera> cam(new camera(name));
	cameras.push_back(cam);
}
void level::add_cam(const camera &cam){
	std::shared_ptr<camera> c(new camera(cam));
	cameras.push_back(c);
}

void level::add_light(){
	std::shared_ptr<light> l(new light());
	lights.push_back(l);
}
void level::add_light(std::string &name){
	std::shared_ptr<light> l(new light(name));
	lights.push_back(l);
}
void level::add_light(std::string &name, std::vector<double> &loc){
	std::shared_ptr<light> l(new light(name, loc));
	lights.push_back(l);
}

void level::add_mesh(){
	std::shared_ptr<mesh> m(new mesh());
	meshes.push_back(m);
}
void level::add_mesh(std::string &name){
	std::shared_ptr<mesh> m(new mesh(name));
	meshes.push_back(m);
}
void level::add_mesh(std::string &name, std::string &mesh_path){
	std::shared_ptr<mesh> m(new mesh(name, mesh_path));
	meshes.push_back(m);
}
void level::add_mesh(std::string &name, std::string &mesh_path, std::string &mat_path){
	std::shared_ptr<mesh> m(new mesh(name, mesh_path, mat_path));
	meshes.push_back(m);
}
void level::add_mesh(const mesh &m__){
	std::shared_ptr<mesh> m(new mesh(m__));
	meshes.push_back(m);
}

void level::set_name(std::string &n){
	name = n;
}
void level::set_cam_name(uint32 index, std::string &n){
	if(index < cameras.size()){
		cameras[index]->set_name(n);
	}
	else{
		// Raise exception
	}
}
void level::set_light_name(uint32 index, std::string &n){
	if(index < lights.size()){
		lights[index]->set_name(n);
	}
	else{
		// Raise exception
	}
}
void level::set_mesh_name(uint32 index, std::string &n){
	if(index < meshes.size()){
		meshes[index]->set_name(n);
	}
	else{
		// Raise exception
	}
}

std::vector<std::shared_ptr<camera> > * level::get_cams(){
	return &cameras;
}
std::vector<std::shared_ptr<light> > * level::get_lights(){
	return &lights;
}
std::vector<std::shared_ptr<mesh> > * level::get_meshes(){
	return &meshes;
}

void level::set_cam_clip(uint32 index, std::vector<double> &clip){
	if(index < cameras.size()){
		cameras[index]->set_clip(clip);
	}
	else{
		// Raise Exception.
	}
}
void level::set_cam_loc(uint32 index, std::vector<double> &location){
	if(index < cameras.size()){
		cameras[index]->set_loc(location);
	}
	else{
		// Raise Exception.
	}
}
void level::set_cam_target(uint32 index, std::vector<double> &target){
	if(index < cameras.size()){
		cameras[index]->set_target(target);
	}
	else{
		// Raise Exception.
	}
}

void level::set_light_color(uint32 index, std::vector<double> &color){
	if(index < lights.size()){
		lights[index]->set_color(color);
	}
	else{
		// Raise Exception.
	}
}
void level::set_light_loc(uint32 index, std::vector<double> &location){
	if(index < lights.size()){
		lights[index]->set_loc(location);
	}
	else{
		// Raise Exception.
	}
}

void level::add_mesh_transform(uint32 index, TRANSF t, std::vector<double> &transform_vector){
	if(index < meshes.size()){
		meshes[index]->add_transform(t, transform_vector);
	}
	else{
		// Raise Exception.
	}
}
void level::rmv_mesh_transform(uint32 index, uint32 transform_index){
	if(index < meshes.size()){
		meshes[index]->rmv_transform(transform_index);
	}
	else{
		// Raise Exception.
	}
}
void level::set_mesh_matpath(uint32 index, std::string &path){
	if(index < meshes.size()){
		meshes[index]->set_matpath(path);
	}
	else{
		// Raise Exception.
	}
}
void level::set_mesh_path(uint32 index, std::string &path){
	if(index < meshes.size()){
		meshes[index]->set_meshpath(path);
	}
	else{
		// Raise Exception.
	}
}

// Level Functions
uint32 level::cam_count(){
	return cameras.size();
}
uint32 level::light_count(){
	return lights.size();
}
uint32 level::mesh_count(){
	return meshes.size();
}
std::string level::get_name(){
	return name;
}
std::string level::get_mesh_loc(){
	return mesh_loc;
}
std::string level::get_mat_loc(){
	return mat_loc;
}

// Get Members' names
std::string level::get_cam_name(uint32 index){
	return cameras[index]->get_name();
}
std::string level::get_light_name(uint32 index){
	return lights[index]->get_name();
}
std::string level::get_mesh_name(uint32 index){
	return meshes[index]->get_name();
}

// Camera Functions
std::vector<double> * level::get_cam_clip(uint32 index){
	return cameras[index]->get_clip();
}
std::vector<double> * level::get_cam_location(uint32 index){
	return cameras[index]->get_loc();
}
std::vector<double> * level::get_cam_target(uint32 index){
	return cameras[index]->get_target();
}

// Mesh Functions
std::string level::get_mesh(uint32 index){
	return meshes[index]->get_mesh();
}
std::string level::get_mat(uint32 index){
	return meshes[index]->get_mat();
}