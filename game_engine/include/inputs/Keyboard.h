#ifndef INPUTKEYBOARD_H
#define INPUTKEYBOARD_H

#include "Input.h"

class keyboard : public input, public OIS::KeyListener{
	private:
		const std::string type = "keyboard";
		std::string map_key(const OIS::KeyEvent &e);
		OIS::Keyboard * ois_keyboard;
		virtual void initialize();
		
	protected:
		
	public:
		keyboard(manager * the_manager);
		virtual ~keyboard();
		
		// input methods
		virtual std::string get_type();
		virtual bool has();
		virtual void poll();
		
		// OIS Keyboard methods
		virtual bool keyPressed(const OIS::KeyEvent &event);
		virtual bool keyReleased(const OIS::KeyEvent &event);
};

#endif