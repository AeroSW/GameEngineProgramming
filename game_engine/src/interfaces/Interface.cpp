#include "Interface.h"
#include "GUIParser.h"
#include "Render.h"

#include <iostream>

render * interface::my_renderer = nullptr;
uint64 interface::ref_counter = 0;

void interface::init(render * the_renderer){
	// Do something here
	if(my_renderer == nullptr){
		my_renderer = the_renderer;
	}
	ref_counter++;
}
interface::interface(render * the_renderer, const std::string &document){
//	std::cout << "INTERFACE::RENDER:::::::: " << the_renderer << std::endl;
	my_renderer = the_renderer;
	my_parser = new guiparser(document);
}/*
interface::interface(render * the_renderer, const std::vector<std::pair<std::string, std::string> > acts):
actions(acts){
	my_parser = nullptr;
	init(the_renderer);
}
*/
interface::~interface(){
	ref_counter--;
	if(ref_counter == 0)
		my_renderer = nullptr;
//	actions.clear();
	delete my_parser;
}
