/*
 * Manager.h
 *
 *  Created on: Feb 2, 2017
 *      Author: uge
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>
#include <vector>

#include "UnsignedTypes.h"

class render;
class scene;
class logger;
class input;

// Determines which layout to use.
enum gamepad_t{
	DUALSHOCK4=0,
	XBOX1=1
};

class manager{
	private:
		render* renderer;
		scene * my_scene;
		logger * my_log;
		/*
		 * Constructor
		 * Parameters:
		 * 	None
		 */
		
		std::vector<input*> input_managers;
		
		manager(const std::string &xml, const std::string &log_name, gamepad_t type);
		void init_render(const std::string &xml);
		void init_inputs(gamepad_t type);
		struct gamepad_info{
			gamepad_t type;
			std::vector<bool> curr_buttons;
			std::vector<float> axes;
		} my_gamepad_info;
		struct keyboard_flags{
			bool shift;
			bool ctrl;
			bool alt;
			bool toggle;
		} my_keyboard_flags;
	
	public:
		virtual ~manager();
		static manager* get_manager(const std::string &xml_file, const std::string &log_name, gamepad_t type = gamepad_t::DUALSHOCK4);
		uint32 get_win_length();
		uint32 get_win_height();
		uint32 get_render_win_handler();
		std::string get_curr_level_name();
		bool add_scene(const std::string &xml_filename);
		scene * get_scene();
		void log(const std::string &comment);
		void log(const std::string &comment, uint32 ln_number, const char * msg);
		scene * get_scene(render * mr);
		
		// Input Methods
		void poll_inputs();
		void key_pressed(const std::string &key);
		void key_released(const std::string &key);
		void mbutton_pressed(const std::string &mbutton);
		void mbutton_released(const std::string &mbutton);
};

#endif /* MANAGER_H_ */
