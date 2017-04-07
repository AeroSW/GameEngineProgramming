#ifndef INTERFACES_CEGUI_ACTION_H
#define INTERFACES_CEGUI_ACTION_H

#include "InterfaceAction.h"
#include "CEGUI/CEGUI.h"

class cegui_action : interface_action{
	private:
		
	public:
		cegui_action(ui_action action, const std::string &key);
		virtual ~cegui_action();
		virtual std::string get_key();
		virtual ui_action get_action();
};

#endif