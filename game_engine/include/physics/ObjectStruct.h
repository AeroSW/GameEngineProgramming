#ifndef PHYSICS_OBJECT_STRUCT_H
#define PHYSICS_OBJECT_STRUCT_H

#include <string>
#include <vector>

enum shape_t{BOX = 1, CONE, CYLINDER, PLANE, SPHERE, SQUARE};
enum body_t{GHOST = 0, RIGID, SOFT};

struct object_struct{
	std::vector<float> basis;
	std::vector<float> inertia;
	std::vector<float> origin;
	float mass;
	shape_t shape;
//	body_t body;
	std::string name;
	std::vector<float> my_args;
};

#endif
