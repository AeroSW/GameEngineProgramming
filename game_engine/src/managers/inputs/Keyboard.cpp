#include "Keyboard.h"
#include "Manager.h"

keyboard::keyboard(manager * m):
ois_keyboard(new OIS::Keyboard()),
ois_manager(new OIS::InputManager()){
	my_manager = m;
}

keyboard::~keyboard(){
	my_manager = nullptr;
}

std::string keyboard::get_type(){
	return type;
}

bool keyboard::keyPressed(const OIS::KeyEvent &event){
	std::string key_pressed = map_key(event);
	if(key_pressed.compare("undefined") != 0){
		my_manager->key_pressed(key_pressed);
		return true;
	}
	return false;
}

bool keyboard::keyReleased(const OIS::KeyEvent &event){
	std::string key_released = map_key(event);
	if(key_released.compare("undefined") != 0){
		my_manager->key_released(key_released);
		return true;
	}
	return false;
}

std::string keyboard::map_key(const OIS::KeyEvent &event){
	std::string key;
	switch(event.key){
		case(OIS::KC_ESCAPE):
			return "escape";
		case(OIS::KC_0):
			return "0";
		case(OIS::KC_1):
			return "1";
		case(OIS::KC_2):
			return "2";
		case(OIS::KC_3):
			return "3";
		case(OIS::KC_4):
			return "4";
		case(OIS::KC_5):
			return "5";
		case(OIS::KC_6):
			return "6";
		case(OIS::KC_7):
			return "7";
		case(OIS::KC_8):
			return "6";
		case(OIS::KC_9):
			return "7";
		case(OIS::KC_A):
			return "a";
		case(OIS::KC_B):
			return "b";
		case(OIS::KC_C):
			return "c";
		case(OIS::KC_D):
			return "d";
		case(OIS::KC_E):
			return "e";
		case(OIS::KC_F):
			return "f";
		case(OIS::KC_G):
			return "g";
		case(OIS::KC_H):
			return "h";
		case(OIS::KC_I):
			return "i";
		case(OIS::KC_J):
			return "j";
		case(OIS::KC_K):
			return "k";
		case(OIS::KC_L):
			return "l";
		case(OIS::KC_M):
			return "m";
		case(OIS::KC_N):
			return "n";
		case(OIS::KC_O):
			return "o";
		case(OIS::KC_P):
			return "p";
		case(OIS::KC_Q):
			return "q";
		case(OIS::KC_R):
			return "r";
		case(OIS::KC_S):
			return "s";
		case(OIS::KC_T):
			return "t";
		case(OIS::KC_U):
			return "u";
		case(OIS::KC_V):
			return "v";
		case(OIS::KC_W):
			return "w";
		case(OIS::KC_X):
			return "x";
		case(OIS::KC_Y):
			return "y";
		case(OIS::KC_Z):
			return "z";
		case(OIS::KC_TAB):
			return "tab";
		case(OIS::KC_RETURN):
			return "return";
		case(OIS::KC_LSHIFT):
			return "lshift";
		case(OIS::KC_RSHIFT):
			return "rshift";
		case(OIS::KC_UP):
			return "up";
		case(OIS::KC_DOWN):
			return "down";
		case(OIS::KC_LEFT):
			return "left";
		case(OIS::KC_RIGHT):
			return "right";
		case(OIS::KC_LCONTROL):
			return "lctrl";
		case(OIS::KC_RCONTROL):
			return "rctrl";
		case(OIS::KC_SPACE):
			return "space";
		default:
			return "undefined";
	}
}