#ifndef INTERFACES_CEGUI_WINDOW_RESOURCES_H
#define INTERFACES_CEGUI_WINDOW_RESOURCES_H

#include "CEGUI/CEGUI.h"

struct cegui_resource{
	std::string my_name;
	std::string my_type;
	std::string my_script;
	CEGUI::Window * my_window;
	cegui_resource(); // Identity Constructor
	cegui_resource(const std::string &name, CEGUI::Window * window, const std::string &my_type="Default Window", const std::string &my_script=""); // Regular constructor
	cegui_resource(const cegui_resource &target); // Copy Constructor
	~cegui_resource();
};

#endif