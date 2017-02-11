#include "light.h"

light::light():
color(3,1), location(3,0){
	name = std::string("LIGHT");
}
light::light(std::string &n):
color(3,1), location(3,0){
	name = std::string(n);
}
light::light(std::string &n, std::vector<double> &loc):
color(3,1), location(loc){
	name = std::string(n);
}
light::light(const light &l):
color(l.color), location(l.location){
	name = std::string(l.name);
}

std::string light::get_name(){
	return name;
}
std::vector<double> * light::get_color(){
	return &color;
}
std::vector<double> * light::get_loc(){
	return &location;
}

void light::set_name(std::string &name){
	name = std::string(name);
}
void light::set_color(std::vector<double> &c){
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void light::set_loc(std::vector<double> &l){
	location[0] = l[0];
	location[1] = l[1];
	location[2] = l[2];
}