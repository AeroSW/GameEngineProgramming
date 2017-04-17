#ifndef INTERFACES_CEGUI_WINDOW_RESOURCES_H
#define INTERFACES_CEGUI_WINDOW_RESOURCES_H

#include "CEGUI/CEGUI.h"

class cegui_resource{
	private:
		std::string my_name;
		std::string my_type;
		std::string * my_script;
	//	std::vector<std::string> * my_scripts;
		CEGUI::Window * my_window;
	public:
		cegui_resource(); // Identity Constructor

		cegui_resource(const std::string &name, CEGUI::Window * window,
			 		   const std::string &my_type="Default Window", const std::string &script = ""); // Regular constructor

		cegui_resource(const cegui_resource &target); // Copy Constructor
		~cegui_resource();

		std::string get_name();
		std::string get_type();
		std::string get_script();
		CEGUI::Window * get_window();
		void set_script(const std::string &new_script);
};

#endif
