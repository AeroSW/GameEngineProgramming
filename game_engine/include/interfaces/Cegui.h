#ifndef INTERFACE_CEGUI_H
#define INTERFACE_CEGUI_H

#include "Interface.h"
#include "CeguiWindowResource.h"

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"

class cegui : public interface{
	private:
		const std::string type = "cegui";

		/*
		struct window_resource{
			std::string name;
			std::string type;
			CEGUI::Window * window;
			window_resource();
			window_resource(const std::string &n, const std::string &t, CEGUI::Window * win);
			window_resource(const window_resource &wp);
		};
		std::vector<window_resource> my_windows;
		*/
		std::vector<cegui_resource*> my_windows;
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
	//	std::vector<CEGUI::Window*> widgets; // IS NEEDED!!!!!! :D glad I thought this up early on!!!!
	//	std::vector<std::pair<uint, std::string> > widget_mappings; //!< Map window ids to names given by user.

	public:
		cegui(render * the_renderer, const std::string &setup);
	//	cegui(render * the_renderer, std::vector<std::pair<std::string, std::string> > &acts);
		~cegui();

		virtual bool button_click(const CEGUI::EventArgs &args);

		virtual void add_child(const std::string &parent, const std::string &child);
		virtual void add_root_child(const std::string &child);
		virtual void add_event(const std::string &widget, const std::string &event);
		virtual void create_widget(const std::string &name, const std::string &type, const std::string &looknfeel);
		virtual void set_area(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel);
		virtual void set_position(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel);
		virtual void set_text(const std::string &widget_name, const std::string &text);

		virtual void key_event(const std::string &key); // What happens if a key is entered.
		virtual void mouse_move_event(std::vector<int> &abs, std::vector<int> &rel); // What happens if mouse is moved?
		virtual void mouse_click_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
		virtual void mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel);
};

#endif
