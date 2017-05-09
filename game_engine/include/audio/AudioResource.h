#ifndef AUDIO_AUDIO_RESOURCE_H
#define AUDIO_AUDIO_RESOURCE_H

#include "UnsignedTypes.h"

#include <string>

class manager;

enum audio_t{
	SAMPLE,
	STREAM
};

class AudioResource{
	protected:
		audio_t my_type;
		std::string my_name;
		std::string my_file;

	public:
		AudioResource(const std::string &name, const std::string &file, audio_t type=SAMPLE);
		AudioResource(const audio_resource &ar);
		virtual ~audioResource();

		virtual audio_t getType();
		virtual std::string getFile();
		virtual std::string getName();

		virtual void load(manager * my_manager);
		virtual void unload(manager * my_manager);
};

#endif
