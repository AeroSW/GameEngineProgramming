#include "Render.h"
#include "RenderListener.h"

renderlistener::renderlistener(render * renderer){
	my_renderer = renderer;
	status = true;
}

renderlistener::~renderlistener(){
	my_renderer = nullptr;
}

bool renderlistener::frameStarted(const Ogre::FrameEvent &fe){
	return status;
}
bool renderlistener::frameRenderingQueue(const Ogre::FrameEvent &fe){
	return status;
}
bool renderlistener::frameEnded(const Ogre::FrameEvent &fe){
	return status;
}
void renderlistener::stop_rendering(){
	status = false;
}
bool renderlistener::get_render_status(){
	return status;
}
render * renderlistener::get_renderer(){
	return my_renderer;
}