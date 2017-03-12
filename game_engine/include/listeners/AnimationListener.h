#ifndef ANIMATIONLISTENER_H
#define ANIMATIONLISTENER_H

#include "Ogre.h"
#include "RenderListener.h"

class render;

class animationlistener : public renderlistener{
	private:
	//	render * renderer;
	//	bool render_flag;
		
	public:
		animationlistener(render * r);
		virtual ~animationlistener();
		
	//	bool get_render_status();
	//	render * get_renderer();
	//	void stop_rendering();
		
		virtual bool frameStarted(const Ogre::FrameEvent &event);
	//	bool frameRenderingQueued(const Ogre::FrameEvent &event);
	//	bool frameEnded(const Ogre::FrameEvent &event);
};

#endif