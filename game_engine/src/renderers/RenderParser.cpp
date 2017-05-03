#include "RenderParser.h"

#include "Render.h"

#include "Functions.h"
#include "MyEnums.h"
#include "UnsignedTypes.h"

#include "GameException.h"
#include "SudoExcept.h"

#include <iostream>
#include <vector>

const std::string renderparser::tag		= "render";
const std::string renderparser::type	= "renderparser";

renderparser::renderparser(const std::string &dox):
parser(dox, tag){}

renderparser::~renderparser(){}

void renderparser::construct_renderer(render * render_manager){
	
}

void renderparser::build_gui(render * render_manager){
	
}

void renderparser::construct_levels(render * render_manager, tinyxml2::XMLElement * lvls_element){
	
}
