#ifndef MOUSE_H
#define MOUSE_H

#include "Input.h"

class mouse : public input, public OIS::MouseListener{
	private:
		const std::string type = "mouse";
		OIS::Mouse * ois_mouse;
		std::string map_button(const OIS::MouseButtonID &id);
		virtual void initialize();
		
	protected:
		
	public:
		mouse(manager * the_manager);
		virtual ~mouse();
		
		// input methods
		virtual std::string get_type();
		virtual bool has();
		virtual void poll();
		
		// OIS Mouse methods
		virtual bool mouseMoved(const OIS::MouseEvent &event);
		virtual bool mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id);
};

#endif