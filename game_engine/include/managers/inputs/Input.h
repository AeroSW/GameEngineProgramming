#ifndef INPUT_H
#define INPUT_H

#include <OIS.h>

#include "UnsignedTypes.h"

#include <string>

class manager;

class input{
	private:
		
	
	protected:
		shared_ptr<OIS::InputManager> ois_manager;
		
		manager * my_manager;
		
		uint32 window_height;
		uint32 window_length;
		
	public:
		virtual ~input(){}
		
		virtual std::string get_type() = 0;
};

#endif