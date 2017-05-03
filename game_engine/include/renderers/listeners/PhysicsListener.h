#ifndef LISTENERS_PHYSICSLISTENER_H
#define LISTENERS_PHYSICSLISTENER_H

#include "RenderListener.h"

class physicslistener : public renderlistener{
	public:
		physicslistener(render * my_renderer);
		virtual ~physicslistener();

		virtual bool frameStarted(const Ogre::FrameEvent &event);
};

#endif
