#ifndef RENDERERS_RENDERRESOURCE_H
#define RENDERERS_RENDERRESOURCE_H

#include "MyEnums.h"
#include <string>
#include <vector>

struct anim_resource{
//	object_t object;
	std::string transform;
	axis_t axis;
	rotation_t rot;
	std::vector<float> adjustments;
};

struct object_resource{
	object_t object;
	light_t light;
	float near;
	float far;
	std::string name;
	std::string mesh;
	std::string grp;
};

#endif