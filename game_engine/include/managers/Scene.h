#ifndef SCENE_H
#define SCENE_H

#include <vector> // std Libraries
#include <memory>
#include <string>

#include "Transform.h"
#include "UnsignedTypes.h"

class render;
class manager;

class scene{
	private:
		render * my_renderer;
		
	public:
		scene(render * renderer);
		scene(render * renderer, std::vector<std::string> lvls);
		scene(render * renderer, const std::string &game_file);
		scene(const scene &s);
		~scene();
		
		void log(const std::string &msg); // Calls renderer's log function which then calls manager to log the message.
		
		void add_resrc_location(const std::string &location, const std::string &group_name);
		void declare_resrc(const std::string &file, const std::string &type, const std::string &group_name);
		
		// Entity Functions.
		void add_entity(const std::string &obj_name, const std::string &mesh, const std::string &group_name);
		void add_material(const std::string &obj_name, const std::string &material, const std::string &group_name);
		bool has_group(const std::string &group);
		
		// Camera Functions.
		void create_camera(const std::string &cam_name, std::vector<float> &loc, std::vector<float> &target, std::vector<float> &clip);
		
		// Light Functions.
		void create_light(const std::string &light_name);
		void set_light_type(const std::string &light_name, const std::string &type);
		void set_light_location(const std::string &light_name, std::vector<float> &location);
		void set_light_target(const std::string &light_name, std::vector<float> &target);
		void set_light_color(const std::string &light_name, std::vector<float> &color);
		
		// Scene Graph Functions.
		void add_root_child(const std::string &child);
		void create_node(const std::string &name);
		void add_child(const std::string &parent, const std::string &child);
		void attach_object(const std::string &name, const std::string &entity);
		// Scene Graph Functions for Transformations.
		void apply_rotation(const std::string &name, axis w, float angle);
		void apply_scale(const std::string &name, std::vector<float> &scaling);
		void apply_translation(const std::string &name, std::vector<float> &translation);
		// Scene Graph Functions for Animations.
		void create_animation(const std::string &name, const std::string &animation_name, float time, const unsigned short &track_num);
		void add_frame(const std::string &animation_name, const unsigned short &track_num, float frame_time, std::vector<transform> &transforms);
};

#endif