#ifndef ANIMATIONLISTENER_H
#define ANIMATIONLISTENER_H

#include "Ogre.h"

class render;

class animation_listener : public Ogre::FrameListener{
	private:
		render * renderer;
		bool render_flag;
		
	public:
		animation_listener(render * r);
		virtual ~animation_listener();
		
		bool get_render_status();
		render * get_renderer();
		void stop_rendering();
		
		bool frameStarted(const Ogre::FrameEvent &event);
		bool frameRenderingQueued(const Ogre::FrameEvent &event);
		bool frameEnded(const Ogre::FrameEvent &event);
};

#endif