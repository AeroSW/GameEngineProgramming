#ifndef SCENE_H
#define SCENE_H

#include <vector> // std Libraries
#include <memory>
#include <string>

#include "MyEnums.h"
#include "UnsignedTypes.h"

class render;

class scene{
	private:
		render * my_renderer;
	
	public:
		scene(render * renderer);
		~scene();
};

#endif