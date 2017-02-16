/*
 * Renderer.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Kenneth Cornett
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <memory>
#include <vector>

#include "Resource.h"
#include "Scene.h"
#include "UnsignedTypes.h"

#include "Ogre.h"

class manager;

class render{
	private:
		std::shared_ptr<Ogre::Root> root;
		std::shared_ptr<Ogre::RenderWindow> window;
		std::shared_ptr<Ogre::Viewport> viewport;
		
		std::shared_ptr<resource> my_rsrc_manager;
		std::shared_ptr<scene> my_scene_manager;
		std::shared_ptr<manager> my_game_manager;

		void init(const std::string &xml_file);
		uint32 win_handle; // window handler
		Ogre::Real tslf; // time since last frame
	protected:


	public:
		render(manager &manjr, const std::string &xml_file);
		render(const render &ren);
		virtual ~render();

		uint32 get_win_handle();
		uint32 get_win_length();
		uint32 get_win_height();

		/*
		 * get_win
		 * 	Parameters:
		 * 		Nothing
		 * 	Returns:	Reference to Ogre RenderWindow
		 */
		Ogre::RenderWindow* get_win();
		/*
		 * get_scene
		 * 	Parameters:
		 * 		Nothing
		 * 	Returns:	Reference to Ogre Scene
		 */
		Ogre::SceneManager* get_scene();

		/*
		 * Start and End Render Functions
		 */
		void start_render();
	//	void end_render();

		/*
		 * get_curr_level_name
		 * 	Parameters:
		 * 		None
		 * 	Returns:
		 * 		Returns a string representation of the level's name.
		 */
		std::string get_curr_level_name();

		/*
		 * add_scene
		 * 	Parameters:
		 * 		string	xml_file -> filename xml formatted for scene
		 * 	Returns:	Boolean value representing whether scene was
		 * 				successfully loaded or not.
		 */
		bool add_scene(const std::string &xml_scene_file);
};

#endif /* RENDERER_H_ */
