#ifndef AUDIO_AUDIO_RESOURCE_H
#define AUDIO_AUDIO_RESOURCE_H

#include "UnsignedTypes.h"

#include <string>

class manager;

enum audio_t{
	SAMPLE,
	STREAM
};

class audio_resource{
	protected:
		audio_t my_type;
		std::string my_name;
		std::string my_file;

	public:
		audio_resource(const std::string &name, const std::string &file, audio_t type=SAMPLE);
		audio_resource(const audio_resource &ar);
		virtual ~audio_resource();

		virtual audio_t get_type();
		virtual std::string get_file();
		virtual std::string get_name();

		virtual void load(manager * my_manager);
		virtual void unload(manager * my_manager);
};

#endif
