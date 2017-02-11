#include "Camera.h"
#include <math>

camera::camera():
clip(2), loc(3,0), target(3,0){
	name = std::string("CAMERA"); // Give name a default value
	clip[0] = 10.0; // Set Close Clip Range
	clip[1] = 100.0; // Set Far Clip Range
	target[2] = -100.0; // Change Z-Axis for the target
}

camera::camera(std::string &n):
clip(2), loc(3,0), target(3,0){
	name = std::string(n);
	clip[0] = 10.0; // Set Close Clip Range
	clip[1] = 100.0; // Set Far Clip Range
	target[2] = -100.0; // Change Z-Axis for the target
}

camera::camera(const camera &cam):
clip(cam.clip), loc(cam.loc), target(cam.target){
	name = std::string(cam.name);
}

std::string camera::get_name(){
	return name;
}

std::vector<double> * camera::get_clip(){
	return &clip;
}
std::vector<double> * camera::get_loc(){
	return &loc;
}
std::vector<double> * camera::get_target(){
	return &target;
}

void camera::set_name(std::string &n){
	name = string(n);
}
void camera::set_clip(std::vector<double> &c){
	unsigned double v1 = std::abs(c[0]);
	unsigned double v2 = std::abs(c[1]);
	if(v1 < v2){
		clip[0] = v1;
		clip[1] = v2;
	}
	else{
		clip[0] = v2;
		clip[1] = v1;
	}
}
void camera::set_loc(std::vector<double> &l){
	loc[0] = l[0];
	loc[1] = l[1];
	loc[2] = l[2];
}
void camera::set_target(std::vector<double> &t){
	target[0] = t[0];
	target[1] = t[1];
	target[2] = t[2];
}