#ifndef PHYSICS_PHYSICS_H
#define PHYSICS_PHYSICS_H

#include "Functions.h"
#include "UnsignedTypes.h"
#include "Pair.h"

class render;

class physics{
	private:
		virtual void init(render * render_manager, const std::string &dox);
		
	protected:
		render * render_manager;
		physics_parser * my_parser;
		
		physics(render * render_manager, const std::string &dox);
		virtual ~physics();
		
	public:
		virtual add_resource(physics_resource * resource) = 0;
};


#endif