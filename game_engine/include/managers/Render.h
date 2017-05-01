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
#include "GameParser.h"
#include "Transform.h"

#include "Ogre.h"

class level;
class manager;
class interface;
class renderlistener;
class bullet;

class render{
	private:
		Ogre::Root * root;
		Ogre::RenderWindow * window;
		Ogre::Viewport * viewport;
		float aspect_ratio;

		Ogre::ResourceGroupManager * rgm;
		Ogre::SceneManager * ogre_scene;

		manager * my_manager;
		interface * my_interface;
		bullet * physics_manager;

		std::vector<renderlistener*> listeners;

		std::vector<level> levels; // The list of levels.  Keeps track of cameras, entities, and lights.  Animations etc.
		uint32 curr_level; // 0-based

		gameparser * gp;


	//	Ogre::Camera * active_cam;

		void init();

		void destroy_levels();
		void unload_level();

	//	void set_camera();
		uint32 win_handler; // window handler
		Ogre::Real tslf; // time since last frame

		void build_levels(std::vector<std::string> &names);

	protected:


	public:
		render(manager * manjr, const std::string &xml_file);
		render(const render &ren);
		virtual ~render();

		void * get_scene_manager();

		void build_gui();
		void build_physics();

		uint32 get_win_handle();
		uint32 get_win_length();
		uint32 get_win_height();
	//	void push_animation_state(Ogre::AnimationState * as);
		Ogre::RenderWindow* get_win();
		Ogre::SceneManager* get_scene();

		/*
		 * Start and End Render Functions
		 */
		void start_render();
		void stop_render();
		void end_render();
		std::string get_scene_name();

		/*
		 * add_scene
		 * 	Parameters:
		 * 		string	xml_file -> filename xml formatted for scene
		 * 	Returns:	Boolean value representing whether scene was
		 * 				successfully loaded or not.
		 */
		bool add_scene(const std::string &xml_scene_file);

		void load_level(uint lvl=1); // 1-based function call.
		void next_level();
		void prev_level();
		void log(const std::string &msg);

		// Other methods
		void call_script(const std::string &script, std::vector<std::string> &args);

		// Listener Functions
		//	Listener Grabber
		void loop_animations(float timestep);
		void check_input(float timestep);
		void update_audio(float timestep);
		void update_physics(float timestep);
		
		// Cam movement functions
		void cam_x_move(float val);
		void cam_y_move(float val);
		void cam_z_move(float val);
		void cam_x_local_rotation(float val);
		void cam_y_local_rotation(float val);
		void cam_z_local_rotation(float val);
		void cam_x_global_rotation(float val);
		void cam_y_global_rotation(float val);
		void cam_z_global_rotation(float val);
		
		void prev_camera();
		void next_camera();

		void set_node_position(const std::string &node_name, float x, float y, float z);
		void set_node_orientation(const std::string &node_name, float w, float x, float y, float z);
		bool has_node(const std::string &name);
		
		// Mouse movement functions
		void mouse_moved(std::vector<int> &abs_pos, std::vector<int> &rel_pos);
		void mouse_pressed(uint8 click_id, std::vector<int> &abs_pos, std::vector<int> &rel_pos);
		void mouse_released(uint8 click_id, std::vector<int> &abs_pos, std::vector<int> &rel_pos);

		// Scene Functions
		//	Manager Functions
		bool has_scene_manager(const std::string &name);
		void create_scene_manager(const std::string &name);
		void load_scene(const std::string &name);
		void render_scene(const std::string &name);
		//	Resource Manipulation
		void load_resource(const std::string &resource);
		void unload_resource(const std::string &resource);
		void add_resource_location(const std::string &location, const std::string &group); // Add resource location for everything other than levels.
		void add_resource_location_l(const std::string &location, const std::string &group); // Add resource location for levels.
		void declare_resource(const std::string &file, const std::string &type, const std::string &group);
		bool has_group(const std::string &group);
		//	Generic Scene Functions
		void add_plane(const std::string &plane, const std::string &axis, float w, float h, const std::string &group);
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
