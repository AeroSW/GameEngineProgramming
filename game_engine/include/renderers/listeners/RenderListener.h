#ifndef RENDERLISTENER_H
#define RENDERLISTENER_H

#include "Ogre.h"

class render;

class renderlistener : public Ogre::FrameListener{
	private:
		
	protected:
		render * my_renderer;
		bool status;
		
		render * get_renderer();
		
	public:
		renderlistener(render * renderer);
		virtual ~renderlistener();
		
		virtual bool frameStarted(const Ogre::FrameEvent &fe);
		virtual bool frameRenderingQueue(const Ogre::FrameEvent &fe);
		virtual bool frameEnded(const Ogre::FrameEvent &fe);
		
		virtual void start_rendering();
		virtual void stop_rendering();
		virtual bool get_render_status();
		
};

#endif