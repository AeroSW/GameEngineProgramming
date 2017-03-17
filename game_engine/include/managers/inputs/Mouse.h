#ifndef MOUSE_H
#define MOUSE_H

#include "Input.h"

class mouse : public input, public OIS::MouseListener{
	private:
		const static std::string type = "mouse";
		shared_ptr<OIS::Mouse> ois_mouse;
		std::string map_button(const OIS::MouseButtonID &id);
		
	protected:
		
	public:
		mouse(manager * the_manager);
		virtual ~mouse();
		
		virtual std::string get_type();
		virtual bool mouseMoved(const OIS::MouseEvent &event);
		virtual bool mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id);
};

#endif