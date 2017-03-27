#include "Interface.h"

render * interface::my_renderer = nullptr;
uint64 interface::ref_counter = 0;

void interface::init(){
	// Do something here
}

interface::interface(render * the_renderer){
	if(my_renderer == nullptr)
		my_renderer = the_renderer;
	else{
		if(my_renderer != the_renderer){ // If they are different references.
			my_renderer = the_renderer;
		}
	}
	ref_counter++;
	init();
}

interface::~interface(){
	ref_counter--;
	if(ref_counter == 0)
		my_renderer = nullptr;
	actions.clear();
}