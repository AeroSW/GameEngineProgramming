#ifndef ASW_INCLUDE_MYENUMS_H
#define ASW_INCLUDE_MYENUMS_H

namespace asw{
	enum input_t{KEYBOARD=1,MOUSE,DUALSHOCK4,XBOX1};
	enum axis_t{X=0,Y,Z};
	enum rotation_t{GLOBAL=1,LOCAL};
	enum object_t{CAMERA=1,ENTITY,LIGHT,NODE};
	enum light_t{POINT=1,SPOTLIGHT,DIRECTIONAL};
}

#endif