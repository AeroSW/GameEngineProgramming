#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include "RenderListener.h"

class inputlistener : public renderlistener{
	private:
		
	protected:
		
	public:
		inputlistener(render * my_renderer);
		virtual ~inputlistener();
		
		virtual bool frameStarted(const Ogre::FrameEvene &event);
};

#endif