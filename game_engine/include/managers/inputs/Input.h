#ifndef INPUT_H
#define INPUT_H

#include <OIS.h>

#include "UnsignedTypes.h"

#include <string>
#include <memory>

class manager;

class input{
	private:
		virtual void initialize();
		static uint32 count;
	
	protected:
		input(manager * m);
		
		static OIS::InputManager * ois_manager;
		
		manager * my_manager;
		
		uint32 window_height;
		uint32 window_length;
		
	public:
		virtual ~input();
		
		virtual std::string get_type() = 0;
		virtual bool has() = 0;
		virtual void poll() = 0;
};

#endif
