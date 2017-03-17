#ifndef INPUTKEYBOARD_H
#define INPUTKEYBOARD_H

#include "Input.h"

class keyboard : public input, public OIS::KeyListener{
	private:
		const static std::string type = "keyboard";
		std::string map_key(const OIS::KeyEvent &e);
		shared_ptr<OIS::Keyboard> ois_keyboard;
		
	protected:
		
	public:
		keyboard(manager * the_manager);
		virtual ~keyboard();
		
		virtual std::string get_type();
		virtual bool keyPressed(const OIS::KeyEvent &event);
		virtual bool keyReleased(const OIS::KeyEvent &event);
};

#endif