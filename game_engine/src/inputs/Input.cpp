#include "Input.h"
#include <sstream>
#include "Manager.h"
#include "Asserts.h"

OIS::InputManager * input::ois_manager = nullptr;
uint32 input::count = 0;

void input::initialize(){
	try{
		if(!ois_manager){ // If ois_manager is an empty shared_ptr
			// Initialize it.
			OIS::ParamList parameters;
			std::ostringstream window_handler_string;
			uint32 window_handler = my_manager->get_render_win_handler();
			window_handler_string << window_handler;
			parameters.insert(std::make_pair(std::string("WINDOW"), window_handler_string.str()));
			
			// May need to play around with the following line.
			ois_manager = OIS::InputManager::createInputSystem(parameters);
		}
	}
	catch(...){
		ASSERT_LOG(false, "InputManager could not be initialized.");
	}
}

input::input(manager * m){
	my_manager = m;
	initialize();
	count++;
}
input::~input(){
	count--;
	if(count==0 && ois_manager){
		ois_manager->destroyInputSystem(ois_manager);
		ois_manager = nullptr;
	}
}