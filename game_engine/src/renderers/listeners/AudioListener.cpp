#include "Render.h"
#include "AudioListener.h"

audiolistener::audiolistener(render * my_renderer):
renderlistener(my_renderer){}

audiolistener::~audiolistener(){
	my_renderer = nullptr;
}

bool audiolistener::frameStarted(const Ogre::FrameEvent &event){
	float curr_time = event.timeSinceLastFrame;
	my_renderer->update_audio(curr_time);
	return status;
}
