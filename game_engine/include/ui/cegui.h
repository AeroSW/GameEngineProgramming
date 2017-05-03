#ifndef INTERFACE_CEGUI_H
#define INTERFACE_CEGUI_H

#include "include/ui/user_interface.h"
#include "include/ui/cegui_resource.h"

//#include "CEGUI/CEGUI.h"
//#include "CEGUI/RendererModules/Ogre/Renderer.h"

namespace CEGUI{
	class GUIContext;
	class OgreRenderer;
	class System;
	class WindowManager;
	class Window;
}

namespace asw{
	class Cegui : public UserInterface{
		private:
			const std::string type = "Cegui";

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
		//	render * my_renderer;

			/*!
			 *	init
			 *
			 *	Calls parser's build gui function.
			 */
			virtual void init();
			virtual void destroyContext();

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
			Cegui(render * the_renderer, const std::string &setup);
		//	cegui(render * the_renderer, std::vector<std::pair<std::string, std::string> > &acts);
			~Cegui();

			virtual bool buttonClick(const CEGUI::EventArgs &args);

			virtual void addChild(const std::string &parent, const std::string &child);
			virtual void addRootChild(const std::string &child);
			virtual void addEvent(const std::string &widget, const std::string &event);
			virtual void createWidget(const std::string &name, const std::string &type, const std::string &looknfeel);
			virtual void setArea(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel);
			virtual void setPosition(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel);
			virtual void setText(const std::string &widget_name, const std::string &text);

			virtual void keyPressEvent(const std::string &key); // What happens if a key is entered.
			virtual void keyReleaseEvent(char &key);
			virtual void mouseMoveEvent(std::vector<int> &abs, std::vector<int> &rel); // What happens if mouse is moved?
			virtual void mouseClickEvent(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
			virtual void mouseReleaseEvent(uint8 button, std::vector<int> &abs, std::vector<int> &rel); // What happens if a mouse button is pressed?
			virtual void mouseWheelEvent(std::vector<int> &abs, std::vector<int> &rel);
	};
}
#endif
