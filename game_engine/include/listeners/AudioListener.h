#ifndef LISTENERS_AUDIOLISTENER_H
#define LISTENERS_AUDIOLISTENER_H

#include "RenderListener.h"

class audiolistener : public renderlistener{
	public:
		audiolistener(render * my_renderer);
		virtual ~audiolistener();

		virtual bool frameStarted(const Ogre::FrameEvent &event);
};

#endif
