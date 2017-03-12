/*
 * Renderer.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Kenneth Cornett
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <string>
#include <memory>
#include <vector>

//#include "Resource.h"
//#include "Scene.h"
#include "UnsignedTypes.h"


#include "Ogre.h"

class manager;
class animation_listener;

class render{
	private:
		Ogre::Root * root;
		Ogre::RenderWindow * window;
		Ogre::Viewport * viewport;
		
		Ogre::SceneManager * my_scene_manager;
		manager * my_game_manager;
		animation_listener * al;
		
		Ogre::Camera * camera;
		
		void init(const std::string &xml_file);
		
		
		//void set_camera();
		uint32 win_handler; // window handler
		Ogre::Real tslf; // time since last frame
		std::shared_ptr<std::vector<Ogre::AnimationState*> > animation_states;
	protected:


	public:
		render(manager * manjr, const std::string &xml_file);
		render(const render &ren);
		virtual ~render();

		uint32 get_win_handle();
		uint32 get_win_length();
		uint32 get_win_height();
		void push_animation_state(Ogre::AnimationState * as);
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
		std::string get_scene_name();

		/*
		 * add_scene
		 * 	Parameters:
		 * 		string	xml_file -> filename xml formatted for scene
		 * 	Returns:	Boolean value representing whether scene was
		 * 				successfully loaded or not.
		 */
		bool add_scene(const std::string &xml_scene_file);
		void loop_animations(float timestep);
};

#endif /* RENDERER_H_ */
