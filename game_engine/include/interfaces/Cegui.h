#ifndef INTERFACE_CEGUI_H
#define INTERFACE_CEGUI_H

#include "Interface.h"

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"

class cegui : public interface{
	private:
		const std::string type = "cegui";
		std::string file;
	//	guiparser my_parser;
		render * my_renderer;
		
		/*!
		 *	init
		 *
		 *	Calls parser's build gui function.
		 */
		virtual void init();
		virtual void destroy_context();
		
		static uint ogre_render_count;
		std::vector<std::string> my_resources;
		
		// CEGUI Objects.
		CEGUI::GUIContext * my_context;
		static CEGUI::OgreRenderer * my_ogre_renderer;
		CEGUI::System * my_system;
		CEGUI::WindowManager * my_win_manager;
		CEGUI::Window * my_window;
		// How to store multiple widgets.
		std::vector<CEGUI::Window*> widgets; // Not sure if needed...
		std::vector<std::pair<uint, std::string> > widget_mappings; //!< Map window ids to names given by user.
		
	public:
		cegui(render * the_renderer, const std::string &setup);
		cegui(render * the_renderer, std::vector<std::pair<std::string, std::string> > &acts);
		~cegui();
		
	//	virtual void load_level(); // Loads a new interface for a level????
	//	virtual void unload_level(); // Unloads the current level interface????
		
	//	virtual void create_widget(const std::string &type, std::pair<float, float> left, std::pair<float, float> top, std::pair<float, float> right, std::pair<float, float> bottom, const std::string &name = "");
		
		virtual void set_resource_loc(const std::string &name, const std::string &loc); // Set location to 'loc' for 'resource'.
		virtual void load_resource(const std::string &group); // Set current 'resource' to 'name'
		virtual void create_resource(const std::string &type, const std::string &file);
	//	virtual void load_file(resource_t &type, const std::string &file);
		virtual void set_default(const std::string &type, const std::string &file);
		virtual void set_default_component(const std::string &component, const std::string &value);
	//	virtual void add_tooltip(const std::string &name);
		virtual void apply_script(const std::string &widget, const std::string &script); // Apply script to widget.
		
		
		virtual void key_event(const std::string &key); // What happens if a key is entered.
		virtual void mouse_move_event(std::vector<int> &abs, std::vector<int> &rel); // What happens if mouse is moved?
		virtual void mouse_click_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel);
};

#endif