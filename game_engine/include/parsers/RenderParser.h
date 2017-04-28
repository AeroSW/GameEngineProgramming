#ifndef PARSERS_RENDERPARSER_H
#define PARSERS_RENDERPARSER_H

class render;

#include "Parser.h"
#include <vector>

class renderparser : public parser{
	private:
		static const std::string tag;
		static const std::string type;
		
		virtual void construct_levels(render * render_manager, tinyxml2::XMLElement * levels_element);
		
	public:
		renderparser(const std::string &dox);
		virtual ~renderparser();
		
		virtual void build_gui(render * render_manager):
		virtual void construct_renderer(render * render_manager);
};

#endif