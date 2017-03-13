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
		Ogre::ResourceGroupManager * rgm;
		Ogre::SceneManager * ogre_scene;
		manager * my_game_manager;
		animation_listener * al;
		
		std::vector<level> levels;
		uint32 curr_level;
		std::vector<std::string> cameras;
		
	//	Ogre::Camera * cam;
		
		void init(const std::string &xml_file);
		
		
	//	void set_camera();
		uint32 win_handler; // window handler
		Ogre::Real tslf; // time since last frame
		std::shared_ptr<std::vector<Ogre::AnimationState*> > animation_states;
		void hard_resource_group_check(uint32 line_number);
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
		
		// Scene Functions
		bool has_group(const std::string &group);
		void log_scene(const std::string &msg);
		void add_resource_location(const std::string &location, const std::string &group);
		void declare_resource(const std::string &file, const std::string &type, const std::string &group);
		void add_entity(const std::string &entity, const std::string &mesh, const std::string &group);
		void add_material(const std::string &entity, const std::string &material, const std::string &group);
		void add_camera(const std::string &cam_name, std::vector<float> &loc, std::vector<float> &target, std::vector<float> &clip);
		void add_light(const std::string &light_name);
		void set_light_type(const std::string &light_name, const std::string &type);
		void set_light_location(const std::string &light_name, std::vector<float> &location);
		void set_light_target(const std::string &light_name, std::vector<float> &target);
		void set_light_colour(const std::string &light_name, std::vector<float> &colour);
		void add_root_child(const std::string &child);
		void add_node(const std::string &node_name);
		void add_child(const std::string &parent, const std::string &child);
		void attach_object(const std::string &node, const std::string &entity);
		void rotate_node(const std::string &node, axis w, float angle);
		void scale_node(const std::string &node, std::vector<float> &scaling);
		void move_node(const std::string &node, std::vector<float> movement);
		void add_animation(const std::string &node, const std::string &anim_name, const float time, const uint16 track_num);
		void add_frame(const std::string &anim_name, const uint16 &track_num, const float time, std::vector<transform> &transforms);
};

#endif /* RENDERER_H_ */
