#include "Render.h"
#include "AnimationListener.h"

#include <iostream>

animation_listener::animation_listener(render * r){
	renderer = r;
	render_flag = true;
}
animation_listener::~animation_listener(){
	renderer = nullptr;
}

bool animation_listener::get_render_status(){
	return render_flag;
}
render * animation_listener::get_renderer(){
	return renderer;
}
void animation_listener::stop_rendering(){
	render_flag = false;
}

bool animation_listener::frameStarted(const Ogre::FrameEvent &event){
	float timestep = event.timeSinceLastFrame;
	renderer->loop_animations(timestep);
	return render_flag;
}
bool animation_listener::frameRenderingQueued(const Ogre::FrameEvent &event){}
bool animation_listener::frameEnded(const Ogre::FrameEvent &event){}