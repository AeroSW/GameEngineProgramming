#ifndef INTERFACE_CEGUI_WIDGET_HANDLER_H
#define INTERFACE_CEGUI_WIDGET_HANDLER_H

#include "CEGUI/CEGUI.h"
#include "Pair.h"

#include <string>
//class cegui;

//typedef void (cegui::*my_function_ptr)(const CEGUI::EventArgs&)

class widget_handler : public pair_t<CEGUI::Window, std::string>{
	private:
		// f is a CEGUI::Window reference.
		// s is a std::string

	public:
		widget_handler(CEGUI::Window * widget, const std::string &type);
		widget_handler(const widget_handler &wh);
		widget_handler(widget_handler * wh);
		~widget_handler();

		int compare(CEGUI::Window &wn);
		int compare(std::string &str);
};

#endif
