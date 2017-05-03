#ifndef MOUSE_H
#define MOUSE_H

#include "Input.h"
#include <vector>

class mouse : public input, public OIS::MouseListener{
	private:
		const std::string type = "mouse";
		OIS::Mouse * ois_mouse;
		uint8 map_button(const OIS::MouseButtonID &id);
		
		virtual void initialize();
		virtual std::vector<int> get_absolute_position();
		virtual std::vector<int> get_relative_position();
		
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