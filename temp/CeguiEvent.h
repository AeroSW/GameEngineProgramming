#ifndef INTERFACES_CEGUIEVENT_H
#define INTERFACES_CEGUIEVENT_H

#include "InterfaceArguments.h"
#include "CEGUI/CEGUI.h"

class cegui_args : public interface_args{
	private:
		CEGUI::EventArgs * arguments;
	public:
		cegui_args(CEGUI::EventArgs * arguments);
		virtual cegui_args();
		CEGUI::EventArgs * get_arguments();
};

#endif