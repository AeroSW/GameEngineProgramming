#include "Render.h"
#include "PhysicsListener.h"

physicslistener::physicslistener(render * my_renderer):
renderlistener(my_renderer){}

physicslistener::~physicslistener(){
	my_renderer = nullptr;
}

bool physicslistener::frameStarted(const Ogre::FrameEvent &event){
	float curr_time = event.timeSinceLastFrame;
	my_renderer->update_physics(curr_time);
	return status;
}
