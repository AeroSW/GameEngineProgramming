#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Input.h"

class gamepad : public input, public OIS::JoyStickListener{
	private:
		const static std::string type = "gamepad";
		
		virtual std::string map_button(const int &button);
		virtual std::string map_axis(const int &axis);
		
	
	protected:
		shared_ptr<OIS::JoyStick> ois_gamepad;
		uint32 tol;
		
	public:
		gamepad(manager * the_manager, int tol=10000);
		virtual ~gamepad();
		
		virtual std::string get_type();
		
		virtual bool buttonPressed(const OIS::JoyStickEvent &event, int button);
		virtual bool buttonReleased(const OIS::JoyStickEvent &event, int button);
		
		virtual bool axisMoved(const OIS::JoyStickEvent &event, int axis);
};

#endif