#ifndef RENDERLISTENER_H
#define RENDERLISTENER_H

#include "Ogre.h"

class render;

class renderlistener : public Ogre::FrameListener{
	private:
		render * my_renderer;
		bool status;
	public:
		renderlistener(render * renderer);
		virtual ~renderlistener();
		
		virtual bool frameStarted(const Ogre::FrameEvent &fe);
		virtual bool frameRenderingQueue(const Ogre::FrameEvent &fe);
		virtual bool frameEnded(const Ogre::FrameEvent &fe);
		
		void stop_rendering();
		bool get_render_status();
		
	protected:
		render * get_renderer();
}

#endif