#ifndef ASW_INCLUDE_PHYSICS_OBJECTSTRUCT_H
#define ASW_INCLUDE_PHYSICS_OBJECTSTRUCT_H

#include <string>
#include <vector>

namespace asw{
	enum shape_t{BOX = 1, CONE, CYLINDER, CYLINDER_X, PLANE, SPHERE, SQUARE};
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
}

#endif
