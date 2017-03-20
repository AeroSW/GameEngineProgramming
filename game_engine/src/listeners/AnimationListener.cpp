#include "Render.h"
#include "AnimationListener.h"

animationlistener::animationlistener(render * r):
renderlistener(r){
//	renderer = r;
//	render_flag = true;
}
animationlistener::~animationlistener(){
//	renderer = nullptr;
}
/*
bool animationlistener::get_render_status(){
	return render_flag;
}
render * animationlistener::get_renderer(){
	return renderer;
}
void animationlistener::stop_rendering(){
	render_flag = false;
}
*/
bool animationlistener::frameStarted(const Ogre::FrameEvent &event){
	float timestep = event.timeSinceLastFrame;
	my_renderer->loop_animations(timestep);
	return status;
}
/*
bool animationlistener::frameRenderingQueued(const Ogre::FrameEvent &event){}
bool animationlistener::frameEnded(const Ogre::FrameEvent &event){}
*/