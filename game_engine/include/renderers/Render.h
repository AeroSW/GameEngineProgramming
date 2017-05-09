#ifndef MANAGERS_RENDER_H
#define MANAGERS_RENDER_H

#include "UnsignedTypes.h"
#include "MyEnums.h"

#include <string>
#include <vector>

namespace asw{

	class core;
	class level;
	class renderlistener;
	class renderparser;
	class user_interface; // Renaming of class interface
	
	struct anim_resource;
	struct object_resource;
	
	class render{
		private:
			
			virtual void render_init(core * core_manager, const std::string &dox) = 0;
			virtual void gui_init(const std::string &dox) = 0;
			
		protected:
			static render * render_manager;
			static core * core_manager;
			static user_interface * ui_manager;
			static renderparser * my_parser;
			
			// (object name, object type)
			std::vector<asw::pair<std::string,object_t>> base_objs;
			
			std::vector<asw::pair<std::string,level*>> levels;
			uint32 curr_level;
			
			std::vector<renderlistener*> listeners;
		//	render(core * core_manager, const std::string &dox);
			virtual ~render(){}
			
		public:
		//	virtual bool initialize(core * core_manager, const std::string &dox) = 0;
		//	virtual bool destroy() = 0;
		//	virtual render * get_singleton_ptr() = 0;
			virtual void begin_render() = 0;
			virtual void create_gui(const std::string &doc) = 0;
			
			virtual uint32 window_height() = 0;
			virtual uint32 window_width() = 0;
			virtual uint32 window_handle() = 0;
			virtual std::string active_level() = 0;
			
			virtual void change_level(const std::string &level_name) = 0;
			virtual void translate_object(const std::string &obj, float x, float y, float z) = 0;
			virtual void rotate_object(const std::string &obj, axis_t &axis, rotation_t &type, float w) = 0;
			virtual void scale_object(const std::string &obj, float x, float y, float z) = 0;
			virtual void reveal_object(const std::string &obj) = 0;
			virtual void hide_object(const std::string &obj) = 0;
			virtual void key_pressed(char &key) = 0;
			virtual void key_released(char &key) = 0;
			virtual void mouse_clicked(uint8 id, std::vector<int> &abs, std::vector<int> &rel) = 0;
			virtual void mouse_released(uint8 id, std::vector<int> &abs, std::vector<int> &rel) = 0;
			virtual void mouse_moved(std::vector<int> &abs, std::vector<int> &rel) = 0;
			virtual void update_audio(float ts) = 0;
			virtual void poll_inputs(float ts) = 0;
			virtual void call_script(const std::string &script, std::vector<std::string> &args) = 0;
			
			virtual void add_child(const std::string &parent, const std::string &child) = 0;
			virtual void add_root_child(const std::string &child) = 0;
			virtual void create_scene_manager(const std::string &name) = 0;
			virtual void create_scene_node(const std::string &node_name) = 0;
			virtual void load_scene_manager(const std::string &name) = 0;
			virtual void add_location(const std::string &loc, const std::string &grp) = 0;
			virtual void declare_resource(const std::string &file, const std::string &type, const std::string &group) = 0;
			
			virtual void add_base(object_resource * obj_src) = 0;
			virtual void add_skin(const std::string &base, const std::string &material, const std::string &grp) = 0;
		//	virtual void add_cam(const std::string &name, std::vector<float> &clip) = 0;
		//	virtual void add_light(const std::string &name, std::vector<float> &colour) = 0;
			virtual void attach_object(const std::string &node, const std::string &object_name, object_t &object) = 0;
			// Animation
			virtual void add_animation(const std::string &node, const std::string &animation_name, const float &time, const uint16 track) = 0;
			virtual void add_frame(const std::string &animation_name, const uint16 track, const float time, std::vector<anim_resource*> vals) = 0;
	};

}

#endif