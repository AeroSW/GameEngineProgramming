#include "inputlistener.h"

inputlistener::inputlistener(render * my_renderer):
renderlistener(my_renderer){}

inputlistener::~inputlistener(){}

bool inputlistener::frameStarted(const Ogre::FrameEvent &event){
	float curr_time = event.timeSinceLastFrame;
	my_renderer->check_input(curr_time);
	return status;
}