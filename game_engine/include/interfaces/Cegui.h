#ifndef INTERFACE_CEGUI_H
#define INTERFACE_CEGUI_H

#include "Interface.h"

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"

class cegui : interface{
	private:
		const std::string type = "cegui";
		std::string file;
		guiparser my_parser;
		render * my_renderer;
		
		/*!
		 *	init
		 *
		 *	Calls parser's build gui function.
		 */
		virtual void init();
		
		// CEGUI Objects.
		CEGUI::GUIContext * my_context;
		static CEGUI::OgreRenderer * my_ogre_renderer;
		CEGUI::System * my_system;
		CEGUI::Window * my_window;
		
	public:
		cegui(render * the_renderer, const std::string &setup);
		cegui(render * the_renderer, std::vector<std::pair<std::string, std::string> > &acts);
		~cegui();
		
		virtual void load_level(); // Loads a new interface for a level????
		virtual void unload_level(); // Unloads the current level interface????
		
		
		virtual void set_resource_loc(resource_t &type, const std::string &name, const std::string &loc); // Set location to 'loc' for 'resource'.
		
		// Setter functions.
		virtual void set_resource(resource_t &type, const std::string &name); // Set current 'resource' to 'name'
		virtual void apply_script(const std::string &widget, const std::string &script); // Apply script to widget.
		
		
		virtual void key_event(const std::string &key); // What happens if a key is entered.
		virtual void mouse_move_event(std::vector<int> &abs, std::vector<int> &rel); // What happens if mouse is moved?
		virtual void mouse_press_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel);
};

#endif