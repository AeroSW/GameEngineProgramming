/*
 * Manager.h
 *
 *  Created on: Feb 2, 2017
 *      Author: uge
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>
#include "LogManager.h"
#include "UnsignedTypes.h"

class render;
class scene;
class logger;

class manager{
	private:
		render* renderer;
		scene * my_scene;
		logger my_log;
		/*
		 * Constructor
		 * Parameters:
		 * 	None
		 */
		manager(const std::string &xml, const std::string &log_name);
		void init(const std::string &xml);

	public:
		/*
		 * Destructor
		 */
		virtual ~manager();
		/*
		 * get_manager
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Reference to manager object
		 */
		static manager* get_manager(const std::string &xml_file, const std::string &log_name);
		/*
		 * get_win_length
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Size of window along horizontal axis.
		 */
		uint32 get_win_length();
		/*
		 * get_win_height
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Size of window along vertical axis.
		 */
		uint32 get_win_height();
		/*
		 * get_render_win_handler
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Returns the window handler for the renderer.
		 */
		uint32 get_render_win_handler();
		/*
		 * get_curr_level_name
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Returns the name of the current level.
		 */
		std::string get_curr_level_name();
		/*
		 * add_scene
		 * 	Parameters:
		 * 		string filename for an xml file
		 * 	Returns:
		 * 		Returns a boolean value representing success
		 * 		or not.
		 */
		bool add_scene(const std::string &xml_filename);
		scene * get_scene();
		void log(const std::string &comment);
		void log(const std::string &comment, uint32 ln_number);
};

#endif /* MANAGER_H_ */
