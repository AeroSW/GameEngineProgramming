#include "include/ui/user_interface.h"
#include "include/ui/gui_parser.h"
#include "include/renderers/render.h"

#include <iostream>

render * asw::UserInterface::render_manager = nullptr;
uint64 asw::UserInterface::ref_counter = 0;

void asw::UserInterface::init(render * the_renderer){
	// Do something here
	if(render_manager == nullptr){
		render_manager = the_renderer;
	}
	ref_counter++;
}
asw::UserInterface::UserInterface(render * the_renderer, const std::string &document){
//	std::cout << "INTERFACE::RENDER:::::::: " << the_renderer << std::endl;
	render_manager = the_renderer;
	my_parser = new guiparser(document);
}/*
interface::interface(render * the_renderer, const std::vector<std::pair<std::string, std::string> > acts):
actions(acts){
	my_parser = nullptr;
	init(the_renderer);
}
*/
asw::UserInterface::~UserInterface(){
	ref_counter--;
	if(ref_counter == 0)
		render_manager = nullptr;
//	actions.clear();
	delete my_parser;
}
