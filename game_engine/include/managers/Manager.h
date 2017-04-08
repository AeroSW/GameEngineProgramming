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

// Class Forward Declarations.
class audio;
class input;
class logger;
class render;
class scene;
// Struct Forward Declarations.
struct audio_info;

// Determines which layout to use.
enum gamepad_t{
	DUALSHOCK4=0,
	XBOX1=1
};

class manager{
	private:
		audio * my_audio;
		render* renderer;
		scene * my_scene;
		logger * my_log;
		/*
		 * Constructor
		 * Parameters:
		 * 	None
		 */

		std::vector<input*> input_managers;

		manager(const std::string &xml, const std::string &log_name, const std::string &audio_xml, gamepad_t type);
		void init_render(const std::string &xml);
		void init_inputs(gamepad_t type);
		void init_audio(const std::string &xml);

		//Dualshock4 Methods
		void dualshock_move(float value, int index);
		void dualshock_trigger(float value, int index);
		void dualshock_pressed(std::vector<bool> buttons, int index);
		// Xbox One Methods
		void xbox_move(float value, int index);
		void xbox_trigger(float value, int index);
		void xbox_pressed(std::vector<bool> buttons, int index);

		struct gamepad_flags{
			bool trigger_toggle;
			bool local_toggle;
		} my_gamepad_flags;

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
		static manager* get_manager(const std::string &game_xml, const std::string &log_name, const std::string &audio_xml, gamepad_t type = gamepad_t::DUALSHOCK4);
		uint32 get_win_length();
		uint32 get_win_height();
		uint32 get_render_win_handler();
		std::string get_curr_level_name();
		bool add_scene(const std::string &xml_filename);
		scene * get_scene();
		void log(const std::string &comment);
		void log(const std::string &comment, uint32 ln_number, const char * msg);
		scene * get_scene(render * mr);

		audio_info * create_audio_info();
		void update_audio(float timestep);

		// Input Methods
		void poll_inputs();
		// Keyboard Methods
		void key_pressed(const std::string &key);
		void key_released(const std::string &key);
		// Mouse Methods
		void mbutton_pressed(uint8 mbutton, std::vector<int> &abs_vals, std::vector<int> &rel_vals);
		void mbutton_released(uint8 mbutton, std::vector<int> &abs_vals, std::vector<int> &rel_vals);
		void mouse_moved(std::vector<int> &abs_vals, std::vector<int> &rel_vals);
		// Gamepad Methods
		bool is_trigger(int index);
		void gamepad_move(float value, int index);
		void gamepad_trigger(float value, int index);
		void gamepad_pressed(std::vector<bool> buttons, int index);

		// GUI Methods
};

#endif /* MANAGER_H_ */
