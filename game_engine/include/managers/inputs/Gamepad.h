#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Input.h"

class gamepad : public input, public OIS::JoyStickListener{
	private:
		const std::string type = "gamepad";
		
		virtual std::string map_button(const int &button);
	//	virtual std::string map_axis(const int &axis);
		virtual void initialize();
	
	protected:
		OIS::JoyStick * ois_gamepad;
		uint32 tol;
		
	public:
		gamepad(manager * the_manager, int tol=10000);
		virtual ~gamepad();
		
		// input methods
		virtual std::string get_type();
		virtual bool has();
		virtual void poll();
		
		// OIS JoyStick methods
		virtual bool buttonPressed(const OIS::JoyStickEvent &event, int button);
		virtual bool buttonReleased(const OIS::JoyStickEvent &event, int button);
		virtual bool sliderMoved(const OIS::JoyStickEvent &event, int slid);
		virtual bool povMoved(const OIS::JoyStickEvent &event, int pov);
		virtual bool vector3Moved(const OIS::JoyStickEvent &event, int vect);
		
		
		virtual bool axisMoved(const OIS::JoyStickEvent &event, int axis);
};

#endif
